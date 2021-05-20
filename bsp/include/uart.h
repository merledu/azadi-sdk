#define UART_BASE_ADDRESS 0x40060000
#define Cntrl_Register_Offset 0xc
#define Clock_Frequency 0x1312D00
#define UART_WRITE_DATA 0x18
#define UART_INTR_STATE_REG 0x0
#define UART_INTR_ENABLE_REG 0x4
#define UART_INTR_STATE_RX_BREAK_ERR_MASK 0x00000001  
void Set_Baud_Rate(int baud_rate);
void Uart_Tx_Rdy(char val);
int Uart_Rx_Rdy();

