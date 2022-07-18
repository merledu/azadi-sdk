#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct bitfield_field32 {
  /** The field mask. Usually all ones. */
  uint32_t mask;
  /** The field position in the bitfield, counting from the zero-bit. */
  uint32_t index;
} bitfield_field32_t;

static uint32_t index_to_mask(uint32_t index) { return 1u << index; }

inline void mem_write32(uint32_t base, uint32_t offset, uint32_t value) {
  ((volatile uint32_t*)base)[offset / sizeof(uint32_t)] = value;
}

inline uint32_t mem_read32(uint32_t base, ptrdiff_t offset) {
  return ((volatile uint32_t*)base)[offset / sizeof(uint32_t)];
}

inline bitfield_field32_t bitfield_bit32_to_field32(uint32_t bit_index) {
  return (bitfield_field32_t){
      .mask = 0x1,
      .index = bit_index,
  };
}

inline uint32_t bitfield_field32_write(uint32_t bitfield,
                                       bitfield_field32_t field,
                                       uint32_t value) {
  bitfield &= ~(field.mask << field.index);
  bitfield |= (value & field.mask) << field.index;
  return bitfield;
}

inline uint32_t bitfield_bit32_write(uint32_t bitfield, uint32_t bit_index,
                                     bool value) {
  return bitfield_field32_write(bitfield, bitfield_bit32_to_field32(bit_index),
                                value ? 0x1u : 0x0u);
}

inline uint32_t bitfield_field32_read(uint32_t bitfield,
                                      bitfield_field32_t field) {
  return (bitfield >> field.index) & field.mask;
}

inline bool bitfield_bit32_read(uint32_t bitfield, uint32_t bit_index) {
  return bitfield_field32_read(bitfield,
                               bitfield_bit32_to_field32(bit_index)) == 0x1u;
}