#include <stdio.h>
#include "spi.h"
int main()
{   
Set_Speed(24);
Spi_Write('w' , 0, 1);


return 0;
}
