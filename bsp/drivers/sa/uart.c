// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#include "uart.h"
#include "uart-regs.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "platform.h"

// static dif_uart_t uart0;

// void uart_init(unsigned int baud) {
//   // Note that, due to a GCC bug, we cannot use the standard `(void) expr`
//   // syntax to drop this value on the ground.
//   // See https://gcc.gnu.org/bugzilla/show_bug.cgi?id=25509
//   mmio_region_t base_addr = mmio_region_from_addr(UART0_START);
//   if (dif_uart_init((dif_uart_params_t){.base_addr = base_addr}, &uart0)) {
//   }
//   if (dif_uart_configure(&uart0, (dif_uart_config_t){
//                                      .baudrate = baud,
//                                      .clk_freq_hz = 24 * 1000 * 1000,
//                                      .parity_enable = kDifUartToggleDisabled,
//                                      .parity = kDifUartParityEven,
//                                  })) {
//   }
// }


/************* MEMORY FUNCTIONS START **************/

inline uint32_t bitfield_field32_read(uint32_t bitfield,
                                      bitfield_field32_t field) {
  return (bitfield >> field.index) & field.mask;
}

inline bitfield_field32_t bitfield_bit32_to_field32(
    uint32_t bit_index) {
  return (bitfield_field32_t){
      .mask = 0x1, .index = bit_index,
  };
}

inline uint32_t bitfield_field32_write(uint32_t bitfield,
                                       bitfield_field32_t field,
                                       uint32_t value) {
  bitfield &= ~(field.mask << field.index);
  bitfield |= (value & field.mask) << field.index;
  return bitfield;
}

inline void mem_write32(uint32_t base, uint32_t offset,
                                uint32_t value) {
  ((volatile uint32_t *)base)[offset / sizeof(uint32_t)] = value;
}

inline uint32_t mem_read32(uint32_t base, ptrdiff_t offset) {
  return ((volatile uint32_t *)base)[offset / sizeof(uint32_t)];
}

inline bool bitfield_bit32_read(uint32_t bitfield, uint32_t bit_index) {
  return bitfield_field32_read(bitfield,
                               bitfield_bit32_to_field32(bit_index)) == 0x1u;
}

/************* MEMORY FUNCTIONS END **************/

static bool uart_tx_full() {
  uint32_t reg =
      mem_read32(UART0_START, UART_STATUS_REG_OFFSET);
  return bitfield_bit32_read(reg, UART_STATUS_TXFULL_BIT);
}

static bool uart_tx_idle() {
  uint32_t reg =
      mem_read32(UART0_START, UART_STATUS_REG_OFFSET);
  return bitfield_bit32_read(reg, UART_STATUS_TXIDLE_BIT);
}

static bool uart_rx_empty() {
  uint32_t reg =
      mem_read32(UART0_START, UART_STATUS_REG_OFFSET);
  return bitfield_bit32_read(reg, UART_STATUS_RXEMPTY_BIT);
}


static void uart_tx_fifo_write(uint8_t byte) {
  uint32_t reg = bitfield_field32_write(0, UART_WDATA_WDATA_FIELD, byte);
  mem_write32(UART0_START, UART_WDATA_REG_OFFSET, reg);
}

static size_t uart_bytes_send(const uint8_t *data,
                              size_t bytes_requested) {
  size_t bytes_written = 0;
  while ((bytes_written < bytes_requested) && !uart_tx_full()) {
    uart_tx_fifo_write(data[bytes_written]);
    ++bytes_written;
  }

  return bytes_written;
}



dif_uart_result_t dif_uart_byte_send_polled(uint8_t byte) {

  // Busy wait for the TX FIFO to free up.
  while (uart_tx_full()) {
  }

  (void)uart_bytes_send(&byte, 1);

  // Busy wait for the TX FIFO to be drained and for HW to finish processing
  // the last byte.
  while (!uart_tx_idle()) {
  }

}

void uart_send_char(char c) {
  // Note that, due to a GCC bug, we cannot use the standard `(void) expr`
  // syntax to drop this value on the ground.
  // See https://gcc.gnu.org/bugzilla/show_bug.cgi?id=25509
  if (dif_uart_byte_send_polled((uint8_t)c)) {
  }
}

void uart_send_str(char *str) {
  while (*str != '\0') {
    uart_send_char(*str++);
  }
}

size_t uart_send_buf(void *data, const char *buf, size_t len) {
  for (size_t i = 0; i < len; ++i) {
    uart_send_char(buf[i]);
  }
  return len;
}

// const buffer_sink_t uart_stdout = {
//     .data = NULL, .sink = &uart_send_buf,
// };

#define hexchar(i) (((i & 0xf) > 9) ? (i & 0xf) - 10 + 'A' : (i & 0xf) + '0')

void uart_send_uint(uint32_t n, int bits) {
  for (int i = bits - 4; i >= 0; i -= 4) {
    uart_send_char(hexchar(n >> i));
  }
}


/******************* UART RECIEVE *******************/


static uint8_t uart_rx_fifo_read() {
  uint32_t reg =
      mem_read32(UART0_START, UART_RDATA_REG_OFFSET);

  return bitfield_field32_read(reg, UART_RDATA_RDATA_FIELD);
}

static size_t uart_bytes_receive(size_t bytes_requested,
                                 uint8_t *data) {
  size_t bytes_read = 0;
  while ((bytes_read < bytes_requested) && !uart_rx_empty()) {
    data[bytes_read] = uart_rx_fifo_read();
    ++bytes_read;
  }

  return bytes_read;
}


dif_uart_result_t dif_uart_rx_bytes_available(size_t *num_bytes) {
  if (num_bytes == NULL) {
    return kDifUartBadArg;
  }

  // RX FIFO fill level (in bytes).
  uint32_t reg =
      mem_read32(UART0_START, UART_FIFO_STATUS_REG_OFFSET);
  *num_bytes = (size_t)bitfield_field32_read(reg, UART_FIFO_STATUS_RXLVL_FIELD);

  return kDifUartOk;
}

dif_uart_result_t dif_uart_bytes_receive(size_t bytes_requested, uint8_t *data,
                                         size_t *bytes_read) {
  if (data == NULL) {
    return kDifUartBadArg;
  }

  // `bytes_read` is an optional parameter.
  size_t res = uart_bytes_receive(bytes_requested, data);
  if (bytes_read != NULL) {
    *bytes_read = res;
  }

  return kDifUartOk;
}


int uart_rcv_char(char *c) {
  size_t num_bytes = 0;
  if (dif_uart_rx_bytes_available(&num_bytes) != kDifUartOk) {
    return -1;
  }
  if (num_bytes == 0) {
    return -1;
  }
  // The pointer cast from char* to uint8_t* is dangerous. This needs to be
  // revisited.
  if (dif_uart_bytes_receive(1, (uint8_t *)c, NULL) != kDifUartOk) {
    return -1;
  }

  return 0;
}
