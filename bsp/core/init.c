#include "plic.h"
#include "trap.h"

static void trap_init() {
  mcause_interrupt_table[MACH_EXTERNAL_INTERRUPT] = mach_plic_handler;
  mcause_trap_table[INSTRUCTION_ADDRESS_MISALIGNED] = default_handler;
}

void init() {
  trap_init();
  main();
}
