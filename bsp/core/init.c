#include "trap.h"
#include "plic.h"


void main()
{
    mcause_interrupt_table[MACH_EXTERNAL_INTERRUPT]  = mach_plic_handler;
    mcause_trap_table[INSTRUCTION_ADDRESS_MISALIGNED] = default_handler;
}
