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

typedef struct bitfield_field32 {
  /** The field mask. Usually all ones. */
  uint32_t mask;
  /** The field position in the bitfield, counting from the zero-bit. */
  uint32_t index;
} bitfield_field32_t;


void Set_Baud_Rate(int baud_rate);
void Uart_Tx_Rdy(char val);
int Uart_Rx_Rdy();
void Uart_Interrupt_Routine();
void uart_init(unsigned int baud);
void uart_send_char(char c);
void uart_send_str(char *str);
size_t uart_send_buf(void *data, const char *buf, size_t len);
int uart_rcv_char(char *c);
void uart_send_uint(uint32_t n, int bits);
// extern uint32_t mem_read32(uint32_t base, ptrdiff_t offset);
extern uint32_t bitfield_field32_write(uint32_t bitfield,
                                       bitfield_field32_t field,
                                       uint32_t value);
extern uint32_t bitfield_field32_read(uint32_t bitfield,
                                      bitfield_field32_t field);
extern bool bitfield_bit32_read(uint32_t bitfield,
                                uint32_t bit_index);
extern uint32_t bitfield_bit32_write(uint32_t bitfield,
                                     uint32_t bit_index,
                                     bool value);
extern bitfield_field32_t bitfield_bit32_to_field32(
    uint32_t bit_index);

extern void mem_write32(uint32_t base, uint32_t offset,
                                uint32_t value);

