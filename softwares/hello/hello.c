#include "uart.h"
int main()
{    
 //   char *str = "waleed";
   // uart_init(9600, 10000000);
   // uart_send_str(str);
//uart_init(9600, 16000000);
//Uart_Send_Str(str);
Set_Baud_Rate(9600);
Uart_Tx_Rdy('w');

    return 0;
}
