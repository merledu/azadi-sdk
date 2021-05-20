#include "gpio.h"
#include "plic.h"
#include "platform.h"
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "utils.h"

// static uint32_t index_to_mask(uint32_t index) { return 1u << index; }

// inline void mem_write32(uint32_t base, uint32_t offset,
//                                 uint32_t value) {
//   ((volatile uint32_t *)base)[offset / sizeof(uint32_t)] = value;
// }

// inline uint32_t mem_read32(uint32_t base, ptrdiff_t offset) {
//   return ((volatile uint32_t *)base)[offset / sizeof(uint32_t)];
// }

void gpio_direct_bit_write(uint32_t offset, uint32_t index, bool val) {
  const uint32_t mask = index_to_mask(index % 32);
  
  mem_write32(GPIO_START, offset, (val ? mask : 0u));

}

// void gpio_masked_bit_write(uint32_t reg_lower_offset,
//                                                uint32_t reg_upper_offset,
//                                                uint32_t index, bool val) {


//   const uint32_t offset = (index < 16) ? reg_lower_offset : reg_upper_offset;
//   const uint32_t mask = index_to_mask(index % 16);
//   mem_write32(GPIO_START, offset, (mask << 16) | (val ? mask : 0u));

// }

void gpio_intr_enable(uint32_t index){
  gpio_direct_bit_write(GPIO_INTR_ENABLE_REG_OFFSET, index, 1 );
}

void gpio_intr_type(uint32_t index){
  gpio_direct_bit_write(GPIO_INTR_CTRL_EN_LVLHIGH_REG_OFFSET, index, 1 );
}

static void gpio_masked_bit_write(uint32_t reg_lower_offset,
                                           uint32_t reg_upper_offset,
                                           uint32_t mask, uint32_t val) {
  
  // const uint32_t mask = index_to_mask(index % 16);
  const uint32_t mask_lower_half = mask & 0x0000FFFFu;
  const uint32_t mask_upper_half = mask & 0xFFFF0000u;
  if (mask_lower_half != 0) {
    mem_write32(GPIO_START, reg_lower_offset,
                        (mask_lower_half << 16) | (val & 0x0000FFFFu));
  }
  if (mask_upper_half != 0) {
    mem_write32(GPIO_START, reg_upper_offset,
                        mask_upper_half | ((val & 0xFFFF0000u) >> 16));
  }
}

void gpio_masked_write(int pin, int val){
  const uint32_t shifted = index_to_mask(pin % 32);
  gpio_masked_bit_write(GPIO_MASKED_OUT_LOWER_REG_OFFSET,
                               GPIO_MASKED_OUT_UPPER_REG_OFFSET, 0x0000FFFFu, shifted);
}

void gpio_direct_write(long pin, int val){
    gpio_direct_bit_write(GPIO_DIRECT_OUT_REG_OFFSET, pin, val);
}

void gpio_direct_write_all(uint32_t state){
  mem_write32(GPIO_START, GPIO_DIRECT_OUT_REG_OFFSET, state);
}


uint32_t gpio_read_all(){
  return mem_read32(GPIO_START, GPIO_DATA_IN_REG_OFFSET);
}

uint32_t gpio_read_pin(int pin){

	// isr_table[13] = gpio_read_interrupt;
  uint32_t state = mem_read32(GPIO_START, GPIO_DATA_IN_REG_OFFSET);

  return state >> pin;
}

void gpio_direct_write_enable(long pin){
    gpio_direct_bit_write(GPIO_DIRECT_OE_REG_OFFSET, pin, 1);
}