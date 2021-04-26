/***************************************************************************
 * Project           		: shakti devt board
 * Name of the file	     	: interrupt_demo.c
 * Brief Description of file    : A application to demonstrate working of plic
 * Name of Author    	        : Sathya Narayanan N
 * Email ID                     : sathya281@gmail.com

 Copyright (C) 2019  IIT Madras. All rights reserved.

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.

 ***************************************************************************/
/**
  @file interrupt_demo.c
  @brief A application to demonstrate working of plic
  @detail Thsi file contains an application to demonstrate the working of plic.
  The interrupts are enabled for a gpio pin. Once the button connected to the gpio
  pin is pressed. An interrupt is generated and it is handled by the isr.
 */

#include "gpio.h"
#include "trap.h"
#include "platform.h"
#include "plic.h"
#include "plic-regs.h"


void handle_button_press(__attribute__((unused)) uint32_t num);

void handle_button_press(__attribute__((unused)) uint32_t num)
{
	gpio_direct_write(10, 1);
}



int main(void){
	register unsigned int retval;
	int i;

	// uint32_t *gpio_intr; 
	// gpio_intr = (uint32_t *)(GPIO_START + GPIO_INTR_ENABLE_REG_OFFSET);
	// *gpio_intr = 8;

	// uint32_t *lvlhigh;
	// lvlhigh = (uint32_t *)(GPIO_START + GPIO_INTR_CTRL_EN_LVLHIGH_REG_OFFSET);
	// *lvlhigh = 8;

	gpio_intr_enable(3);
	gpio_intr_type(3);
	
	plic_set_threshold(2);
	plic_set_priority(3, 3);
	plic_set_priority(13, 3);
	//1 on third pin
	plic_enable_interrupt(13);
	plic_set_trigger_type(0);
	

	isr_table[13] = handle_button_press;
	isr_table[3] = 0x0110;
	

	// //init plic module
	// plic_init();

	// //configure interrupt id 7
	// configure_interrupt(3);


	//set the corresponding isr for interrupt id 7
	// isr_table[PLIC_INTERRUPT_3] = handle_button_press;

	// Enable Global (PLIC) interrupts.
	asm volatile("li      t0, 8\t\n"
		     "csrrs   zero, mstatus, t0\t\n"
		    );

	// Enable Local (PLIC) interrupts.
	asm volatile("li      t0, 0x800\t\n"
		     "csrrs   zero, mie, t0\t\n"
		    );
	return 0;
}
