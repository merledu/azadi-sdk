#include "spi.h"

void Isr_Rx_Spi()
{
__asm__ __volatile__ (
"li s0 , 0x40080000;"
// reading value from the spi register
"lw x5 , 0x0(s0);"
);

//clearing rx register
int *wd;
wd = (int *)(SPI_BASE_ADDRESS + SPI_RX_OFFSET);
*wd = 0;

//clearing divisor
int *div;
div = (int *)(SPI_BASE_ADDRESS + SPI_DIVIDER_OFFSET );
*div = 0;

//clearing control register
int *cntrl;
cntrl = (int *)(SPI_BASE_ADDRESS + SPI_CNTRL_OFFSET);
*cntrl = 0;

//clearing slave select
int *Select;
Select = (int *)(SPI_BASE_ADDRESS + SPI_SLAVE_SELECT_OFFSET);
*Select = 0;
}
