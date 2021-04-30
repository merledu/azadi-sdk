#include "gpio.h"
#include "trap.h"
#include "platform.h"
#include "plic.h"
#include "plic-regs.h"


void handle_button_press(__attribute__((unused)) uint32_t num);

void handle_button_press(__attribute__((unused)) uint32_t num)
{
  uint32_t state = gpio_read_all();
   gpio_direct_write_all(state); 
}



int main(void){

	gpio_intr_enable(3);
	gpio_intr_type(3);
	
	plic_set_threshold(2);
	plic_set_priority(3, 3);
	plic_set_priority(13, 3);
	plic_enable_interrupt(13);
	plic_set_trigger_type(0);
	

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
