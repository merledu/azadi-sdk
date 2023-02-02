#include "tic.h"

#include "platform.h"
#include "timer.h"
#include "utils.h"

void mach_timer_handler(uintptr_t int_id, uintptr_t epc) {
  uint32_t timer_id = mem_read32(TIC_BASE_ADDRESS, TIC_CC_REG_OFFSET);

  if (timer_id == TIC_TIMER0_ID) {
    mem_write32(TIC_BASE_ADDRESS, TIC_CC_REG_OFFSET, 0);
    mem_write32(TIMER0_BASE_ADDRESS, TIMER_INTR_STATE_REG_OFFSET, 1);
    mem_write32(TIMER0_BASE_ADDRESS, TIMER_INTR_ENABLE_REG_OFFSET, 0);
  }
}