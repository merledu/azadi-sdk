#include<stdint.h>

#define TIC_CC_REG_OFFSET 0x8   // claim and complete
#define TIC_TIMER0_ID   0x2     // timer 1 interrupt id
#define TIC_TIMER1_ID   0x4     // timer 2 interrupt id
#define TIC_TIMER2_ID   0x8     // timer 3 interrupt id


void mach_timer_handler(uintptr_t int_id, uintptr_t epc);