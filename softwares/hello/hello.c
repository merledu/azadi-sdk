#include <stdio.h>
#include "gpio.h"

int main(){
    int a = 1;
    int b = 5;

    int c = a + b;

    // turn ON gpio pin 3
    if (c>5)
        write_gpio(3, 1);
    else 
    // turn OFF gpio pin 3
        write_gpio(3, 0);
    
    return 0;
}