#include <stdio.h>
#include "uart.h"

int main()
{    
    char *str = "waleed";
    uart_init(9600, 10000000);
    uart_send_str(str);
    return 0;
}
