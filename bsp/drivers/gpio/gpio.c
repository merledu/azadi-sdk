#include "bsp/include/gpio/dif_gpio.h"
#include "platform.h"


static dif_gpio_t gpio;

void gpio_init(){
    mmio_region_t base_addr = mmio_region_from_addr(GPIO_START);
    if(dif_gpio_init((dif_gpio_params_t){.base_addr=base_addr}, &gpio)){
    }
}

void gpio_reset(){
    dif_gpio_reset(&gpio);
}