#define PWM_BASE_ADDRESS 0x400b0000
#define PWM_DUTY_CYCLE_OFFSET 0xc
#define PWM_DUTY_CYCLE_OFFSET2 0x1c

void PWM_DUTYCYCLE(int channel , int a)
{

/* Duty Cycle */
if (channel == 1)
{
int *Duty_Cycle;
Duty_Cycle = (int*)(PWM_BASE_ADDRESS+PWM_DUTY_CYCLE_OFFSET);
*Duty_Cycle = a;

__asm__ __volatile__ (
"li s0 , 0x400b0000;"

/* CONTROL REGISTER */
"li x6 , 0x14;"
"sw x6 , 0(s0);"

/*divisor*/

"li x6 , 0xFFFF;"
"sw x6 , 4(s0);"

/* period */

"li x6 , 0xa;"
"sw x6 , 8(s0);"
);

}
else
{
int *Duty_Cycle;
Duty_Cycle = (int*)(PWM_BASE_ADDRESS+PWM_DUTY_CYCLE_OFFSET2);
*Duty_Cycle = a;

__asm__ __volatile__ (
"li s0 , 0x400b0000;"

/* CONTROL REGISTER */
"li x6 , 0x14;"
"sw x6 , 0x10(s0);"

/*divisor*/

"li x6 , 0xFFFF;"
"sw x6 , 0x14(s0);"

/* period */

"li x6 , 0x1F4;"
"sw x6 , 0x18(s0);"
);
}


}
