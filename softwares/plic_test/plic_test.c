#include "gpio.h"
#include "trap.h"
#include "plic.h"
#include "platform.h"
#include "uart.h"

 void handle_button_press(__attribute__((unused)) uint32_t num);

 void handle_button_press(__attribute__((unused)) uint32_t num)
 {
  int a = 0;
    	mem_write32(UART_BASE_ADDRESS, UART_TX_ENABLE_REGISTER_OFFSET, a);
        mem_write32(UART_BASE_ADDRESS, UART_WDATA_REGISTER_OFFSET, a);
 }


int main(void){
while(1)
{
	gpio_intr_enable(25);
	gpio_intr_type(25, 2);
	// gpio_intr_test(23);

	//plic_init(26, 0);

	//isr_table[26] = handle_button_press;
	
	plic_init(33,0);
	isr_table[33] = handle_button_press;

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
}
	return 0;
}
