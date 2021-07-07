#include "pwm.h"
void PWM_DUTYCYCLE(int channel , int duty_cycle)
{

/* Duty Cycle */
if (channel == 1)
{
int *Duty_Cycle;
Duty_Cycle = (int*)(PWM_BASE_ADDRESS+PWM_DUTY_CYCLE_OFFSET);
*Duty_Cycle = duty_cycle;

__asm__ __volatile__ (
"li s0 , 0x400b0000;"

/* CONTROL REGISTER */
"li x6 , 0x14;"
"sw x6 , 0(s0);"


/*divisor*/

"li x6 , 0x0;"
"sw x6 , 4(s0);"

/* period */

"li x6 , 16000;"
"sw x6 , 8(s0);"
);

}
else
{
int *Duty_Cycle;
Duty_Cycle = (int*)(PWM_BASE_ADDRESS+PWM_DUTY_CYCLE_OFFSET2);
*Duty_Cycle = duty_cycle;

__asm__ __volatile__ (
"li s0 , 0x400b0000;"

/* CONTROL REGISTER */
"li x6 , 0x14;"
"sw x6 , 0x10(s0);"

/*divisor*/

"li x6 , 0x0;"
"sw x6 , 0x14(s0);"

/* period */

"li x6 , 16000;"
"sw x6 , 0x18(s0);"
);
}


}
