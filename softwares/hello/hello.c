#include "uart.h"
#include "utils.h"
#include "gpio.h"
int main()
{    
 // char *str = "waleed";
 // uart_send_str(str);
 // uart_send_char('w');
 // uart_init(9600, 9000000);

//uart_init(9600, 16000000);
//Uart_Send_Str(str);
//Set_Baud_Rate(9600);
//Uart_Tx_Rdy('w');

/* 
1- read data from rdata
2- compare data with wdata
3- if both are equal glow led on gpio3
4- else gpio4

*/
//mem_write32(UART_BASE_ADDRESS, UART_CNTRL_REGISTER_OFFSET, 	1 << 1);
//char rx = mem_read32(UART_BASE_ADDRESS, UART_RDATA_REGISTER_OFFSET);
//mem_write32(UART_BASE_ADDRESS, UART_WDATA_REGISTER_OFFSET, 	rx);
//uart_init(9600, 9000000);

/*uint32_t tx = mem_read32(UART_BASE_ADDRESS, UART_WDATA_REGISTER_OFFSET);
unit32_t rx = mem_read32(UART_BASE_ADDRESS, UART_RDATA_REGISTER_OFFSET);

if(tx == rx){
  		gpio_direct_write(3, 1);
}
else{
	gpio_direct_write(4,1)
}

    return 0;
}
*/
while(1)
{
uart_init(9600 , 9000000);
uint32_t rx = uart_polled_data();
if (rx > 1){
  gpio_direct_write(6, 1);
  gpio_direct_write_enable(6);


}
else{
    gpio_direct_write(7, 1);
  gpio_direct_write_enable(7);

}
}
}
