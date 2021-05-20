// #define UART_BASE_ADDRESS 0x40060000
// #define Cntrl_Register_Offset 0xc
// #define Clock_Frequency 0x1312D00
// #define UART_WRITE_DATA 0x18
// #define UART_INTR_STATE_REG 0x0
// #define UART_INTR_ENABLE_REG 0x4
// #define UART_INTR_STATE_RX_BREAK_ERR_MASK 0x00000001  

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef enum dif_uart_result {
  /**
   * Indicates that the operation succeeded.
   */
  kDifUartOk = 0,
  /**
   * Indicates some unspecified failure.
   */
  kDifUartError = 1,
  /**
   * Indicates that some parameter passed into a function failed a
   * precondition.
   *
   * When this value is returned, no hardware operations occurred.
   */
  kDifUartBadArg = 2,
} dif_uart_result_t;



void Set_Baud_Rate(int baud_rate);
void Uart_Tx_Rdy(char val);
int Uart_Rx_Rdy();
void Uart_Interrupt_Routine();
void uart_init(uint32_t baudrate, uint32_t clk_freq);
static void uart_reset();
void uart_send_char(char c);
void uart_send_str(char *str);
size_t uart_send_buf(void *data, const char *buf, size_t len);
int uart_rcv_char(char *c);
void uart_send_uint(uint32_t n, int bits);


