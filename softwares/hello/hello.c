#include <stdio.h>
#include "gpio.h"

int main(){

    gpio_masked_write(5, 1);
    // gpio_masked_write(5, 0);
    return 0;
}