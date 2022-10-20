#include "spi.h"
#define ZERO 0

void Set_Speed(int Divider) {
  // clock divisor frequency
  int* div;
  div = (int*)(SPI_BASE_ADDRESS + SPI_DIVIDER_OFFSET);
  *div = Divider;
}

void Spi_Write(unsigned char a, int Select_Line, int Char_Len) {
  // Write Data
  int* wd;
  wd = (int*)(SPI_BASE_ADDRESS + SPI_TX_OFFSET);
  *wd = a;

  // Select Line
  int* Select;
  Select = (int*)(SPI_BASE_ADDRESS + SPI_SLAVE_SELECT_OFFSET);
  *Select = Select_Line;

  // cntrl register configuration
  int b = 178 << 7;
  int* cntrl;
  switch (Char_Len) {
    case 1:
      cntrl = (int*)(SPI_BASE_ADDRESS + SPI_CNTRL_OFFSET);
      *cntrl = b + 8;
      break;
    case 2:

      cntrl = (int*)(SPI_BASE_ADDRESS + SPI_CNTRL_OFFSET);
      *cntrl = b + 16;
      break;
    case 3:
      cntrl = (int*)(SPI_BASE_ADDRESS + SPI_CNTRL_OFFSET);
      *cntrl = b + 24;
      break;
    default:
      cntrl = (int*)(SPI_BASE_ADDRESS + SPI_CNTRL_OFFSET);
      *cntrl = b + 32;
  }
}

void Spi_Read(int Select_Line, int Char_Len) {
  // cntrl register configuration
  int b = 306 << 7;
  int* cntrl;
  switch (Char_Len) {
    case 1:
      cntrl = (int*)(SPI_BASE_ADDRESS + SPI_CNTRL_OFFSET);
      *cntrl = b + 8;
      break;
    case 2:

      cntrl = (int*)(SPI_BASE_ADDRESS + SPI_CNTRL_OFFSET);
      *cntrl = b + 16;
      break;
    case 3:
      cntrl = (int*)(SPI_BASE_ADDRESS + SPI_CNTRL_OFFSET);
      *cntrl = b + 24;
      break;
    default:
      cntrl = (int*)(SPI_BASE_ADDRESS + SPI_CNTRL_OFFSET);
      *cntrl = b + 32;
  }

  // Select Line
  int* Select;
  Select = (int*)(SPI_BASE_ADDRESS + SPI_SLAVE_SELECT_OFFSET);
  *Select = Select_Line;

  __asm__ __volatile__("WFI;");
}
