#include "uart.h"
#include "utils.h"
#include "gpio.h"
#include "timer.h"
int main()
{    
    while(1){
       	gpio_direct_write_enable(7);
		gpio_direct_write(7, 1);
        delay(500);
        gpio_direct_write_enable(6);
        gpio_direct_write(6,1);
        delay(500);
    }

}
