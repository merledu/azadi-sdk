// Generated register defines for uart

// Copyright information found in source file:
// Copyright lowRISC contributors.

// Licensing information found in source file:
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#ifndef _UART_REG_DEFS_
#define _UART_REG_DEFS_

#ifdef __cplusplus
extern "C" {
#endif
// Register width
#define UART_PARAM_REG_WIDTH 32

// Common Interrupt Offsets
#define UART_INTR_COMMON_TX_WATERMARK_BIT 0
#define UART_INTR_COMMON_RX_WATERMARK_BIT 1
#define UART_INTR_COMMON_TX_EMPTY_BIT 2
#define UART_INTR_COMMON_RX_OVERFLOW_BIT 3
#define UART_INTR_COMMON_RX_FRAME_ERR_BIT 4
#define UART_INTR_COMMON_RX_BREAK_ERR_BIT 5
#define UART_INTR_COMMON_RX_TIMEOUT_BIT 6
#define UART_INTR_COMMON_RX_PARITY_ERR_BIT 7

// Interrupt State Register
#define UART_INTR_STATE_REG_OFFSET 0x0
#define UART_INTR_STATE_TX_WATERMARK_BIT 0
#define UART_INTR_STATE_RX_WATERMARK_BIT 1
#define UART_INTR_STATE_TX_EMPTY_BIT 2
#define UART_INTR_STATE_RX_OVERFLOW_BIT 3
#define UART_INTR_STATE_RX_FRAME_ERR_BIT 4
#define UART_INTR_STATE_RX_BREAK_ERR_BIT 5
#define UART_INTR_STATE_RX_TIMEOUT_BIT 6
#define UART_INTR_STATE_RX_PARITY_ERR_BIT 7

// Interrupt Enable Register
#define UART_INTR_ENABLE_REG_OFFSET 0x4
#define UART_INTR_ENABLE_TX_WATERMARK_BIT 0
#define UART_INTR_ENABLE_RX_WATERMARK_BIT 1
#define UART_INTR_ENABLE_TX_EMPTY_BIT 2
#define UART_INTR_ENABLE_RX_OVERFLOW_BIT 3
#define UART_INTR_ENABLE_RX_FRAME_ERR_BIT 4
#define UART_INTR_ENABLE_RX_BREAK_ERR_BIT 5
#define UART_INTR_ENABLE_RX_TIMEOUT_BIT 6
#define UART_INTR_ENABLE_RX_PARITY_ERR_BIT 7

// Interrupt Test Register
#define UART_INTR_TEST_REG_OFFSET 0x8
#define UART_INTR_TEST_TX_WATERMARK_BIT 0
#define UART_INTR_TEST_RX_WATERMARK_BIT 1
#define UART_INTR_TEST_TX_EMPTY_BIT 2
#define UART_INTR_TEST_RX_OVERFLOW_BIT 3
#define UART_INTR_TEST_RX_FRAME_ERR_BIT 4
#define UART_INTR_TEST_RX_BREAK_ERR_BIT 5
#define UART_INTR_TEST_RX_TIMEOUT_BIT 6
#define UART_INTR_TEST_RX_PARITY_ERR_BIT 7

// UART control register
#define UART_CTRL_REG_OFFSET 0xc
#define UART_CTRL_TX_BIT 0
#define UART_CTRL_RX_BIT 1
#define UART_CTRL_NF_BIT 2
#define UART_CTRL_SLPBK_BIT 4
#define UART_CTRL_LLPBK_BIT 5
#define UART_CTRL_PARITY_EN_BIT 6
#define UART_CTRL_PARITY_ODD_BIT 7
#define UART_CTRL_RXBLVL_MASK 0x3
#define UART_CTRL_RXBLVL_OFFSET 8
#define UART_CTRL_RXBLVL_FIELD                         \
  ((bitfield_field32_t){.mask = UART_CTRL_RXBLVL_MASK, \
                        .index = UART_CTRL_RXBLVL_OFFSET})
#define UART_CTRL_RXBLVL_VALUE_BREAK2 0x0
#define UART_CTRL_RXBLVL_VALUE_BREAK4 0x1
#define UART_CTRL_RXBLVL_VALUE_BREAK8 0x2
#define UART_CTRL_RXBLVL_VALUE_BREAK16 0x3
#define UART_CTRL_NCO_MASK 0xffff
#define UART_CTRL_NCO_OFFSET 16
#define UART_CTRL_NCO_FIELD                         \
  ((bitfield_field32_t){.mask = UART_CTRL_NCO_MASK, \
                        .index = UART_CTRL_NCO_OFFSET})

// UART live status register
#define UART_STATUS_REG_OFFSET 0x10
#define UART_STATUS_TXFULL_BIT 0
#define UART_STATUS_RXFULL_BIT 1
#define UART_STATUS_TXEMPTY_BIT 2
#define UART_STATUS_TXIDLE_BIT 3
#define UART_STATUS_RXIDLE_BIT 4
#define UART_STATUS_RXEMPTY_BIT 5

// UART read data
#define UART_RDATA_REG_OFFSET 0x14
#define UART_RDATA_RDATA_MASK 0xff
#define UART_RDATA_RDATA_OFFSET 0
#define UART_RDATA_RDATA_FIELD                         \
  ((bitfield_field32_t){.mask = UART_RDATA_RDATA_MASK, \
                        .index = UART_RDATA_RDATA_OFFSET})

// UART write data
#define UART_WDATA_REG_OFFSET 0x18
#define UART_WDATA_WDATA_MASK 0xff
#define UART_WDATA_WDATA_OFFSET 0
#define UART_WDATA_WDATA_FIELD                         \
  ((bitfield_field32_t){.mask = UART_WDATA_WDATA_MASK, \
                        .index = UART_WDATA_WDATA_OFFSET})

// UART FIFO control register
#define UART_FIFO_CTRL_REG_OFFSET 0x1c
#define UART_FIFO_CTRL_RXRST_BIT 0
#define UART_FIFO_CTRL_TXRST_BIT 1
#define UART_FIFO_CTRL_RXILVL_MASK 0x7
#define UART_FIFO_CTRL_RXILVL_OFFSET 2
#define UART_FIFO_CTRL_RXILVL_FIELD                         \
  ((bitfield_field32_t){.mask = UART_FIFO_CTRL_RXILVL_MASK, \
                        .index = UART_FIFO_CTRL_RXILVL_OFFSET})
#define UART_FIFO_CTRL_RXILVL_VALUE_RXLVL1 0x0
#define UART_FIFO_CTRL_RXILVL_VALUE_RXLVL4 0x1
#define UART_FIFO_CTRL_RXILVL_VALUE_RXLVL8 0x2
#define UART_FIFO_CTRL_RXILVL_VALUE_RXLVL16 0x3
#define UART_FIFO_CTRL_RXILVL_VALUE_RXLVL30 0x4
#define UART_FIFO_CTRL_TXILVL_MASK 0x3
#define UART_FIFO_CTRL_TXILVL_OFFSET 5
#define UART_FIFO_CTRL_TXILVL_FIELD                         \
  ((bitfield_field32_t){.mask = UART_FIFO_CTRL_TXILVL_MASK, \
                        .index = UART_FIFO_CTRL_TXILVL_OFFSET})
#define UART_FIFO_CTRL_TXILVL_VALUE_TXLVL1 0x0
#define UART_FIFO_CTRL_TXILVL_VALUE_TXLVL4 0x1
#define UART_FIFO_CTRL_TXILVL_VALUE_TXLVL8 0x2
#define UART_FIFO_CTRL_TXILVL_VALUE_TXLVL16 0x3

// UART FIFO status register
#define UART_FIFO_STATUS_REG_OFFSET 0x20
#define UART_FIFO_STATUS_TXLVL_MASK 0x3f
#define UART_FIFO_STATUS_TXLVL_OFFSET 0
#define UART_FIFO_STATUS_TXLVL_FIELD                         \
  ((bitfield_field32_t){.mask = UART_FIFO_STATUS_TXLVL_MASK, \
                        .index = UART_FIFO_STATUS_TXLVL_OFFSET})
#define UART_FIFO_STATUS_RXLVL_MASK 0x3f
#define UART_FIFO_STATUS_RXLVL_OFFSET 16
#define UART_FIFO_STATUS_RXLVL_FIELD                         \
  ((bitfield_field32_t){.mask = UART_FIFO_STATUS_RXLVL_MASK, \
                        .index = UART_FIFO_STATUS_RXLVL_OFFSET})

// TX pin override control. Gives direct SW control over TX pin state
#define UART_OVRD_REG_OFFSET 0x24
#define UART_OVRD_TXEN_BIT 0
#define UART_OVRD_TXVAL_BIT 1

// UART oversampled values
#define UART_VAL_REG_OFFSET 0x28
#define UART_VAL_RX_MASK 0xffff
#define UART_VAL_RX_OFFSET 0
#define UART_VAL_RX_FIELD \
  ((bitfield_field32_t){.mask = UART_VAL_RX_MASK, .index = UART_VAL_RX_OFFSET})

// UART RX timeout control
#define UART_TIMEOUT_CTRL_REG_OFFSET 0x2c
#define UART_TIMEOUT_CTRL_VAL_MASK 0xffffff
#define UART_TIMEOUT_CTRL_VAL_OFFSET 0
#define UART_TIMEOUT_CTRL_VAL_FIELD                         \
  ((bitfield_field32_t){.mask = UART_TIMEOUT_CTRL_VAL_MASK, \
                        .index = UART_TIMEOUT_CTRL_VAL_OFFSET})
#define UART_TIMEOUT_CTRL_EN_BIT 31

#ifdef __cplusplus
}  // extern "C"
#endif
#endif  // _UART_REG_DEFS_
        // End generated register defines for uart