#define UART_BASE_ADDRESS 0x40060000
#define UART_CNTRL_REGISTER_OFFSET 0x0
#define UART_WDATA_REGISTER_OFFSET 0x4
#define UART_RDATA_REGISTER_OFFSET 0X8
#define UART_TX_ENABLE_REGISTER_OFFSET 0x12
#define UART_RX_ENABLE_REGISTER_OFFSET 0x16
#define UART_RX_STATUS_REGISTER_OFFSET 0X20


void uart_init(unsigned int baud_rate , unsigned int clock_frequency);
void uart_send_char(char val );
void uart_send_str(char *str);
int uart_polled_data();


