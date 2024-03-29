#include "gpio.h"
#include "trap.h"
#include "plic.h"
#include "platform.h"
#include "uart.h"


void handle_button_press(__attribute__((unused)) uint32_t num);

void handle_button_press(__attribute__((unused)) uint32_t num)
{
  	uint32_t state = gpio_read_pin(1);
	
	if(state == 1){
		gpio_direct_write_enable(5);
		gpio_direct_write(5, 1);
	} else {
		gpio_direct_write_enable(7);
		gpio_direct_write(7, 1);
	}
}



int main(void){
while(1)
{
	gpio_intr_enable(1);
	gpio_intr_type(1, 2);
	// gpio_intr_test(23);

	plic_init(2, 0);

	isr_table[2] = handle_button_press;
	
	// plic_init(33,0);
	// isr_table[33] = handle_button_press;

	// gpio_direct_write_enable(5);
	// gpio_direct_write(5, 1);
		
	// delay(2000);

	// gpio_direct_write_enable(6);
	// gpio_direct_write(6, 1);

	// delay(2000);




	

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
