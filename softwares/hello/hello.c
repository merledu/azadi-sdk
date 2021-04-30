#include <stdio.h>
#include "spi.h"
int main()
{   
Set_Speed(4);
Spi_Write('w', 1);
Isr_Tx_Spi();

return 0;
}
