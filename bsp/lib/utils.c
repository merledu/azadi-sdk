#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "utils.h"


extern uint32_t bitfield_bit32_write(uint32_t bitfield,
                                     uint32_t bit_index,
                                     bool value);

extern uint32_t bitfield_field32_write(uint32_t bitfield,
                                       bitfield_field32_t field,
                                       uint32_t value);
extern bitfield_field32_t bitfield_bit32_to_field32(
    uint32_t bit_index);

extern uint32_t mem_read32(uint32_t base, ptrdiff_t offset);

extern void mem_write32(uint32_t base, uint32_t offset,
                                uint32_t value);