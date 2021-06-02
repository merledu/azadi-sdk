#include "spi.h"

int main()
{    
   // char *str = "waleed";
   // uart_init(9600, 10000000);
   // uart_send_str(str);
//Set_Baud_Rate(9600);
//Uart_Tx_Rdy('w');
Set_Speed(0xFFFF);
Spi_Write(1, 0, 1);
    return 0;
}
