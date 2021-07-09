#include "pwm.h"
#include "utils.h"

void PWM_DUTYCYCLE(int channel , int duty_cycle)
{

/* Duty Cycle */
if (channel == 1)
{
int *Duty_Cycle;
Duty_Cycle = (int*)(PWM_BASE_ADDRESS+PWM_DUTY_CYCLE_OFFSET);
*Duty_Cycle = duty_cycle;

/*Control Register */
mem_write32(PWM_BASE_ADDRESS, PWM_CONTROL_REGISTER_OFFSET, 0x14);

/*Divisor*/
mem_write32(PWM_BASE_ADDRESS, PWM_DIVISOR_REGISTER_OFFSET, 0x0);

/*Period*/
mem_write32(PWM_BASE_ADDRESS, PWM_PERIOD_REGISTER_OFFSET, 16000);

}
else
{
int *Duty_Cycle;
Duty_Cycle = (int*)(PWM_BASE_ADDRESS+PWM_DUTY_CYCLE_OFFSET2);
*Duty_Cycle = duty_cycle;

/*Control Register */
mem_write32(PWM_BASE_ADDRESS, PWM_CONTROL_REGISTER_OFFSET2, 0x14);

/*Divisor*/
mem_write32(PWM_BASE_ADDRESS, PWM_DIVISOR_REGISTER_OFFSET2, 0x0);

/*Period*/
mem_write32(PWM_BASE_ADDRESS, PWM_PERIOD_REGISTER_OFFSET2, 16000);

}


}
