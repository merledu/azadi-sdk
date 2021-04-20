#include "gpio.h"
#include "platform.h"

void write_gpio(long pin, int val){
    uint32_t *output_enable;
    output_enable = (uint32_t*) (GPIO_START + GPIO_DIRECT_OE_REG_OFFSET);
    *output_enable = GPIO3;

    uint32_t *direct_write;
    direct_write = (uint32_t*) (GPIO_START + GPIO_DIRECT_OUT_REG_OFFSET);
    *direct_write = GPIO3;

    // uint32_t *gpio_intr; 
	// gpio_intr = (uint32_t *)(GPIO_START + GPIO_INTR_ENABLE_REG_OFFSET);
	// *gpio_intr = (1 << 3);

	// uint32_t *lvlhigh;
	// lvlhigh = (uint32_t *)(GPIO_START + GPIO_INTR_CTRL_EN_LVLHIGH_REG_OFFSET);
	// *lvlhigh = (1 << 3);
}

