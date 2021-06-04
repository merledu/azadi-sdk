// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#include "uart-sa.h"
#include "utils.h"
#include "uart-regs.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "platform.h"

void uart_init(uint32_t baudrate, uint32_t clk_freq) {


  // Calculation formula: NCO = 16 * 2^nco_width * baud / fclk.

  // Compute NCO register bit width
  uint32_t nco_width = 0;

  for (int i = 0; i < 32; i++) {
    nco_width += (UART_CTRL_NCO_MASK >> i) & 1;
  }

  _Static_assert((UART_CTRL_NCO_MASK >> 28) == 0,
                 "NCO bit width exceeds 28 bits.");

  // NCO creates 16x of baudrate. So, in addition to the nco_width,
  // 2^4 should be multiplied.
  uint64_t nco =
      ((uint64_t)baudrate << (nco_width + 4)) / clk_freq;
  uint32_t nco_masked = nco & UART_CTRL_NCO_MASK;

  // Requested baudrate is too high for the given clock frequency.
  // if (nco != nco_masked) {
  //   return kDifUartConfigBadNco;
  // }

  // Must be called before the first write to any of the UART registers.
  uart_reset();

  // Set baudrate, enable RX and TX, configure parity.
  uint32_t reg = 0;
  reg = bitfield_field32_write(reg, UART_CTRL_NCO_FIELD, nco_masked);
  reg = bitfield_bit32_write(reg, UART_CTRL_TX_BIT, true);
  reg = bitfield_bit32_write(reg, UART_CTRL_RX_BIT, true);
  // if (config.parity_enable == kDifUartToggleEnabled) {
  //   reg = bitfield_bit32_write(reg, UART_CTRL_PARITY_EN_BIT, true);
  // }
  // if (config.parity == kDifUartParityOdd) {
  //   reg = bitfield_bit32_write(reg, UART_CTRL_PARITY_ODD_BIT, true);
  // }
  mem_write32(UART0_START, UART_CTRL_REG_OFFSET, reg);

  // Disable interrupts.
  mem_write32(UART0_START, UART_INTR_ENABLE_REG_OFFSET, 0u);

}

static void uart_reset() {
  mem_write32(UART0_START, UART_CTRL_REG_OFFSET, 0u);

  // Write to the relevant bits clears the FIFOs.
  uint32_t reg = 0;
  reg = bitfield_bit32_write(reg, UART_FIFO_CTRL_RXRST_BIT, true);
  reg = bitfield_bit32_write(reg, UART_FIFO_CTRL_TXRST_BIT, true);
  mem_write32(UART0_START, UART_FIFO_CTRL_REG_OFFSET, reg);

  mem_write32(UART0_START, UART_OVRD_REG_OFFSET, 0u);
  mem_write32(UART0_START, UART_TIMEOUT_CTRL_REG_OFFSET, 0u);
  mem_write32(UART0_START, UART_INTR_ENABLE_REG_OFFSET, 0u);
  // mem_write32(base, UART_INTR_STATE_REG_OFFSET,
  //                     UART_INTR_STATE_MASK);
}


// void uart_init(unsigned int baud) {
//   if (dif_uart_configure(&uart0, (dif_uart_config_t){
//                                      .baudrate = baud,
//                                      .clk_freq_hz = 24 * 1000 * 1000,
//                                      .parity_enable = kDifUartToggleDisabled,
//                                      .parity = kDifUartParityEven,
//                                  })) {
//   }
// }

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
