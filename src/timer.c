#include "timer.h"

#include <stdbool.h>
#include <stdint.h>

#include "platform.h"
#include "tic.h"
#include "utils.h"

void delay(int a) {
  // enable tic interrupt
  tic_intr_enable();

  // timer compare offset
  mem_write32(TIMER0_BASE_ADDRESS, TIMER_CMP_LOWER_REG_OFFSET, (a * 4));

  // timer compare upper
  mem_write32(TIMER0_BASE_ADDRESS, TIMER_CMP_UPPER_REG_OFFSET, 0);

  __asm__ __volatile__(
      "li x5 , 0x80;"
      "li x6 , 8;"

      "csrrs x0 , 0x300, x6;"
      "csrrs x0 , 0x304, x5;");

  // prescale in upper 16 bits, step in lower 16 bits
  int config = 1 << 16 | 4000;
  mem_write32(TIMER0_BASE_ADDRESS, TIMER_CONFIG_REG_OFFSET, config);
  // interrupt enable
  mem_write32(TIMER0_BASE_ADDRESS, TIMER_INTR_ENABLE_REG_OFFSET, 1);
  // control register
  mem_write32(TIMER0_BASE_ADDRESS, TIMER_CNTRL_REG_OFFSET, 1);

  __asm__ __volatile__("wfi;");
}
