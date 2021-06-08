#define UART_BASE_ADDRESS 0x40060000
#define UART_CNTRL_REGISTER_OFFSET 0x0
#define UART_WDATA_REGISTER_OFFSET 0x4
#define UART_RDATA_REGISTER_OFFSET 0X8


void uart_init(unsigned int baud_rate , unsigned int clock_frequency);
void uart_send_char(char val );
void uart_send_str(char *str);
int uart_polled_data();


