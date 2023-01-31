#include <stdint.h>

// #define TIMER_BASE_ADDRESS 0x40000000
#define TIMER_CMP_OFFSET 0x10c
#define TIMER_CMP_UPPER_OFFSET 0x110
#define TIMER_CONFIG_HART0_OFFSET 0x100
#define TIMER_INTERRUPT_ENABLE_OFFSET 0x114
#define TIMER_CNTRL_REGISTER_OFFSET 0x0

void delay(int a);
void mach_timer_handler(uintptr_t int_id, uintptr_t epc);