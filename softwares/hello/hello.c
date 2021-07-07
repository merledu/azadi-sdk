#include "timer.h"
#include "pwm.h"
#include <stdio.h>
int main() 
{ 

//  int angle =0;
//  for(angle = 0; angle < 180; angle += 1) 	 // command to move from 0 degrees to 180 degrees 
//  {                                  
    PWM_DUTYCYCLE(2 , 8000);   
    PWM_DUTYCYCLE(1 , 8000);           	 //command to rotate the servo to the specified angle
//    delay(15);                       
//  } 
 
 // delay(1000);
  
//  for(angle = 180; angle>=1; angle-=5)     // command to move from 180 degrees to 0 degrees 
//  {                                
 //   PWM_DUTYCYCLE(2 , angle);
//    delay(5);                       
//  } 

 //   delay(1000);
}
