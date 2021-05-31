#include "timer.h"
#include <stdbool.h>
#include <stdint.h>

void mach_timer_handler(__attribute__((unused)) uintptr_t int_id, __attribute__((unused)) uintptr_t epc){
    __asm__ __volatile__(
        "li s0 , 0x40000000;"
        "li x6 , 0xffffffff;"
        "li x7 , 0x1;"
        
        "sw x6 , 0x10C(s0);"
        "sw x6 , 0x110(s0);"
        "sw x0 , 0x104(s0);"
        "sw x0 , 0x108(s0);"
        "sw x11, 0x100(s0);"
        "sw x0 , 0x114(s0);"
        "sw x7 , 0x118(s0);"
        "sw x0 , 0x0(s0);"
    );
}


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

"csrrs x0 , 0x300, x6;"
"csrrs x0 , 0x304, x5;"



"li x11, 0x00020002;"

//configuration for hart 0
"sw x11, 0x100(s0);"
//interrupt enable

"li x5, 1;"
"sw x5 , 0x114(s0);"

//control register
"sw x5 , 0x0(s0);"


);

__asm__ __volatile__(
    "wfi;"
);
}
