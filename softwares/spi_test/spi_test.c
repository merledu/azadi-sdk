#include "spi.h"
#include "plic.h"
#define ZERO 0

void Isr_Tx_Spi();

void Isr_Tx_Spi()
{
    //clearing rx register
    int *wd;
    wd = (int *)(SPI_BASE_ADDRESS + SPI_TX_OFFSET);
    *wd = ZERO;

    //clearing divisor
    int *div;
    div = (int *)(SPI_BASE_ADDRESS + SPI_DIVIDER_OFFSET);
    *div = ZERO;

    //clearing control register
    int *cntrl;
    cntrl = (int *)(SPI_BASE_ADDRESS + SPI_CNTRL_OFFSET);
    *cntrl = ZERO;

    //clearing slave select
    int *Select;
    Select = (int *)(SPI_BASE_ADDRESS + SPI_SLAVE_SELECT_OFFSET);
    *Select = ZERO;
}

int main()
{
    // plic_init(33, 1);
    // isr_table[33] = Isr_Tx_Spi;

    Set_Speed(0xFFFF);
    Spi_Write(1, 0, 1);

    return 0;
}
