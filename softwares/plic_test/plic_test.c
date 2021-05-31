#include "gpio.h"
#include "trap.h"
#include "plic.h"
#include "platform.h"


void handle_button_press(__attribute__((unused)) uint32_t num);

void handle_button_press(__attribute__((unused)) uint32_t num)
{
  	uint32_t state = gpio_read_pin(3);
	
	if(state == 3)
		gpio_direct_write(16, 1); 
}



int main(void){

	gpio_intr_enable(3);
	gpio_intr_type(3);
	
	plic_init(13);
	
	isr_table[13] = handle_button_press;


	

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
