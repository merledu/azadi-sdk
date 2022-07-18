#include "spi.h"
#define ZERO 0
void Isr_Tx_Spi() {
  // clearing rx register
  int* wd;
  wd = (int*)(SPI_BASE_ADDRESS + SPI_TX_OFFSET);
  *wd = ZERO;

  // clearing divisor
  int* div;
  div = (int*)(SPI_BASE_ADDRESS + SPI_DIVIDER_OFFSET);
  *div = ZERO;

  // clearing control register
  int* cntrl;
  cntrl = (int*)(SPI_BASE_ADDRESS + SPI_CNTRL_OFFSET);
  *cntrl = ZERO;

  // clearing slave select
  int* Select;
  Select = (int*)(SPI_BASE_ADDRESS + SPI_SLAVE_SELECT_OFFSET);
  *Select = ZERO;
}
