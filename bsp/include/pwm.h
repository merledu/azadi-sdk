#define PWM_BASE_ADDRESS 0x400b0000
#define PWM_DUTY_CYCLE_OFFSET 0xc
#define PWM_DUTY_CYCLE_OFFSET2 0x1c


void PWM_DUTYCYCLE(int channel , int duty_cycle);
