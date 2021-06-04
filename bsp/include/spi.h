#define SPI_BASE_ADDRESS 0x40080000
#define SPI_DIVIDER_OFFSET 0x14
#define SPI_RX_OFFSET 0x20
#define SPI_TX_OFFSET 0x0
#define SPI_CNTRL_OFFSET 0x10
#define SPI_SLAVE_SELECT_OFFSET 0x18
//#define Char_Len 0x20

void Set_Speed(int Divider);
void Spi_Write(unsigned char a , int Select_Line, int Char_Len);
void Spi_Read(int Select_Line,  int Char_Len);
void Isr_Tx_Spi();
void Isr_Rx_Spi();
