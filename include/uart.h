#include <stdint.h>

#define UART_CNTRL_REG_OFFSET 0x0
#define UART_WDATA_REG_OFFSET 0x4
#define UART_RDATA_REG_OFFSET 0X8
#define UART_RX_ENABLE_REG_OFFSET 0xc
#define UART_TX_ENABLE_REG_OFFSET 0x10
#define UART_RX_STATUS_REG_OFFSET 0X14
#define UART_RX_SC_REG_OFFSET 0x18
#define UART_TX_FIFO_EN_REG_OFFSET 0x1c
#define UART_TX_FIFO_SIZE 128  // bytes

typedef struct uart_info {
  uint32_t base_address;
  uint32_t baud_rate;
} uart_t;

void uart_init(uart_t* uart);
void uart_send(uart_t* uart, char* str);
uint8_t uart_recv_byte_polled(uart_t* uart);
