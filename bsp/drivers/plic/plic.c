#include "plic.h"
#include <stddef.h>
#include "platform.h"
#include "plic-regs.h"
#include <stdbool.h>
#include <stdint.h>
#include "utils.h"



plic_fptr_t isr_table[PLIC_MAX_INTERRUPT_SRC];
// interrupt_data_t hart0_interrupt_matrix[PLIC_MAX_INTERRUPT_SRC];

// static uint32_t index_to_mask(uint32_t index) { return 1u << index; }

// inline void mem_write32(uint32_t base, uint32_t offset,
//                                 uint32_t value) {
//   ((volatile uint32_t *)base)[offset / sizeof(uint32_t)] = value;
// }

// inline uint32_t mem_read32(uint32_t base, ptrdiff_t offset) {
//   return ((volatile uint32_t *)base)[offset / sizeof(uint32_t)];
// }

// inline bitfield_field32_t bitfield_bit32_to_field32(
//     uint32_t bit_index) {
//   return (bitfield_field32_t){
//       .mask = 0x1, .index = bit_index,
//   };
// }

// inline uint32_t bitfield_field32_write(uint32_t bitfield,
//                                        bitfield_field32_t field,
//                                        uint32_t value) {
//   bitfield &= ~(field.mask << field.index);
//   bitfield |= (value & field.mask) << field.index;
//   return bitfield;
// }

// inline uint32_t bitfield_bit32_write(uint32_t bitfield,
//                                      uint32_t bit_index,
//                                      bool value) {
//   return bitfield_field32_write(bitfield, bitfield_bit32_to_field32(bit_index),
//                                 value ? 0x1u : 0x0u);
// }

// Helper function to calculate priority register
static ptrdiff_t plic_priority_reg_offset(uint32_t irq) {
  ptrdiff_t offset = irq * sizeof(uint32_t);
  return RV_PLIC_PRIO0_REG_OFFSET + offset;
}

typedef struct plic_reg_info {
  ptrdiff_t offset;
  uint32_t bit_index;
} plic_reg_info_t;

static ptrdiff_t plic_offset_from_reg0(uint32_t irq) {
  uint8_t register_index = irq / RV_PLIC_PARAM_REG_WIDTH;
  return register_index * sizeof(uint32_t);
}

static uint8_t plic_irq_bit_index(uint32_t irq) {
  return irq % RV_PLIC_PARAM_REG_WIDTH;
}

static plic_reg_info_t plic_irq_enable_reg_info(uint32_t irq) {
  ptrdiff_t offset = plic_offset_from_reg0(irq);
  return (plic_reg_info_t){
      .offset = RV_PLIC_IE0_REG_OFFSET + offset,
      .bit_index = plic_irq_bit_index(irq),
  };
}

uint32_t interrupt_claim_request()
{
	uint32_t *interrupt_claim_address = NULL;
	uint32_t interrupt_id;
	interrupt_claim_address = (uint32_t *)(PLIC_BASE_ADDRESS +
					       RV_PLIC_CC0_REG_OFFSET);
	interrupt_id = *interrupt_claim_address;
	return interrupt_id;
}

void mach_plic_handler( __attribute__((unused)) uintptr_t int_id, __attribute__((unused)) uintptr_t epc)
{
	uint32_t interrupt_id;

	interrupt_id =  plic_irq_claim();

	isr_table[interrupt_id](interrupt_id);

	plic_irq_complete(interrupt_id);
}

void plic_set_priority(int irq, uint32_t priority) {

  ptrdiff_t offset = plic_priority_reg_offset(irq);
  mem_write32(PLIC_BASE_ADDRESS, offset, priority);
}

void plic_set_threshold(uint32_t threshold) {
  mem_write32(PLIC_BASE_ADDRESS, RV_PLIC_THRESHOLD0_REG_OFFSET, threshold);

}

void plic_enable_interrupt(uint32_t irq) {
  const uint32_t mask = index_to_mask(irq % 32);
  mem_write32(PLIC_BASE_ADDRESS, RV_PLIC_IE0_REG_OFFSET, mask);

}

void plic_set_trigger_type(uint32_t index) {
  mem_write32(PLIC_BASE_ADDRESS, RV_PLIC_LE_REG_OFFSET, index);
}


// void plic_irq_set_enabled(uint32_t irq, uint8_t value) {

//   plic_reg_info_t reg_info = plic_irq_enable_reg_info(irq);
//   uint32_t reg;

//   // uint32_t reg = mem_read32(PLIC_BASE_ADDRESS, RV_PLIC_IE0_REG_OFFSET);

//   uint8_t bit_index = irq % RV_PLIC_PARAM_REG_WIDTH;
// //   reg = bitfield_bit32_write(reg, reg_info.bit_index, state);
// //   reg = state << irq; //need to fix
//   mem_write32(PLIC_BASE_ADDRESS, RV_PLIC_IE0_REG_OFFSET, value);
// }

uint32_t plic_irq_claim() {

  uint32_t claim_data = mem_read32(PLIC_BASE_ADDRESS, RV_PLIC_CC0_REG_OFFSET);
  return claim_data;

}

void plic_irq_complete(const uint32_t complete_data) {

  // Write back the claimed IRQ ID to the target specific CC register,
  // to notify the PLIC of the IRQ completion.
  mem_write32(PLIC_BASE_ADDRESS, RV_PLIC_CC0_REG_OFFSET,
                      complete_data);

}



void plic_init(int p_id)
{
	plic_set_threshold(2);
	plic_set_priority(p_id, 3);
	plic_enable_interrupt(p_id);
	plic_set_trigger_type(0);
}
