#include "uart.h"

#include <stdint.h>

#include "platform.h"
#include "utils.h"

void uart_init(uart_t* uart) {
  // computing formula : baud_rate = clock_frequency/baud_rate
  const uint32_t clock_frequency = 25000000;
  uint32_t clock_per_bit = (clock_frequency / uart->baud_rate) + 1;

  mem_write32(uart->base_address, UART_CNTRL_REG_OFFSET, clock_per_bit);
}

void uart_send(uart_t* uart, char* str) {
  while (*str != '\0') {
    mem_write32(uart->base_address, UART_WDATA_REG_OFFSET, *str++);
  }

  mem_write32(uart->base_address, UART_TX_FIFO_EN_REG_OFFSET, 1);
  mem_write32(uart->base_address, UART_TX_ENABLE_REG_OFFSET, 1);
}

uint8_t uart_recv_byte_polled(uart_t* uart) {
  uint32_t rcv_status = 0;

  mem_write32(uart->base_address, UART_RX_ENABLE_REG_OFFSET, 1);

  // polling uart status register
  while (rcv_status == 1) {
    rcv_status = mem_read32(uart->base_address, UART_RX_STATUS_REG_OFFSET);
  }
  // read character when status == 1 and clear status
  mem_write32(uart->base_address, UART_RX_SC_REG_OFFSET, 0);
  return mem_read32(uart->base_address, UART_RDATA_REG_OFFSET);
}
