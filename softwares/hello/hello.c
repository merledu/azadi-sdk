#include "pwm.h"
#include <stdio.h>
int main() 
{ 
/*    
unsigned char w = 0x46; //ascii code of w 119 or 0x77
unsigned char a = 0x4c; //ascii code of a 97 or 0x61
unsigned char d = 0x52; //ascii code of d 100 or 0x64
unsigned char s = 0x42; //ascii code of s 115 or 0x73

int forward = 4, backward = 7, right = 11, left = 15;


while(1)
{
uart_init(9600 , 16000000);
char c = uart_polled_data();
if (c == w)
{
    gpio_direct_write_enable(forward);
    gpio_direct_write(forward, 1);
}
else if (c == a)
{
    gpio_direct_write_enable(left);
	gpio_direct_write(left, 1);
}
else if (c == d)
{
    gpio_direct_write_enable(right);
	gpio_direct_write(right, 1);
}
else if(c == s)
{
    gpio_direct_write_enable(backward);
	gpio_direct_write(backward, 1);
}
}
*/

while(1)
{
    PWM_DUTYCYCLE(2 , 70);
}
}
