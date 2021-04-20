#include "platform.h"
#define TIMER_BASE_ADDRESS  0x40000000
#define TIMER_CMP_OFFSET 0x10c
void delay(int a)
{

int *time_cmp;
time_cmp = (int*) (TIMER_BASE_ADDRESS + TIMER_CMP_OFFSET);
*time_cmp = a;

__asm__ __volatile__(
"li s0 , 0x40000000;"

//timer compare upper 
"sw x0 , 0x110(s0);"

"li x5 , 0x80;"
"li x6 , 8;"

"csrrw x0 , 0x300, x6;"
"csrrw x0 , 0x304, x5;"



"li x11, 0x00020002;"

//configuration for hart 0
"sw x11, 0x100(s0);"
//interrupt enable

"li x5, 1;"
"sw x5 , 0x114(s0);"

//control register
"sw x5 , 0x0(s0);"


);
__asm__ __volatile (

"la t0 , 0x20000500;"
"csrw mtvec, t0;"
);

__asm__ __volatile__(
"WFI;"
);




}
