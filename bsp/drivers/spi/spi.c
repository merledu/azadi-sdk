#define SPI_BASE_ADDRESS 0x40080000
#define SPI_DIVIDER_OFFSET 0x14
#define SPI_RX_OFFSET 0x0
#define SPI_TX_OFFSET 0x0
#define SPI_CNTRL_OFFSET 0x10
#define SPI_SLAVE_SELECT_OFFSET 0x18
#define Char_Len 0x20

#include "spi.h"
void Set_Speed(int Divider)
{
//clock divisor frequency
int *div;
div = (int *)(SPI_BASE_ADDRESS + SPI_DIVIDER_OFFSET );
*div = Divider;
}
void Spi_Write(unsigned char a , int Select_Line)
{
//Write Data
int *wd;
wd = (int *)(SPI_BASE_ADDRESS + SPI_TX_OFFSET);
*wd = a;

//Select Line
int *Select;
Select = (int *)(SPI_BASE_ADDRESS + SPI_SLAVE_SELECT_OFFSET);
*Select = Select_Line;

//cntrl register configuration
int b = 6432;
int *cntrl;
cntrl = (int *)(SPI_BASE_ADDRESS + SPI_CNTRL_OFFSET);
*cntrl = b;
}
void Spi_Read(int Select_Line)
{
//cntrl register configuration
int b = 6432;
int *cntrl;
cntrl = (int *)(SPI_BASE_ADDRESS + SPI_CNTRL_OFFSET);
*cntrl = b;

//Select Line
int *Select;
Select = (int *)(SPI_BASE_ADDRESS + SPI_SLAVE_SELECT_OFFSET);
*Select = Select_Line;

}