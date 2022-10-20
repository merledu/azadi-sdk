#include "plic.h"

#include "gpio.h"
#include "utils.h"

plic_fptr_t isr_table[PLIC_MAX_INTERRUPT_SRC];

typedef struct plic_reg_info {
  ptrdiff_t offset;
  uint32_t bit_index;
} plic_reg_info_t;

// Helper function to calculate priority register
static ptrdiff_t plic_priority_reg_offset(uint32_t irq) {
  ptrdiff_t offset = irq * sizeof(uint32_t);
  return RV_PLIC_PRIO0_REG_OFFSET + offset;
}

static ptrdiff_t plic_irq_enable_base_for_target(uint32_t target) {
  ptrdiff_t range = RV_PLIC_IE0_MULTIREG_COUNT * sizeof(uint32_t);
  return RV_PLIC_IE0_0_REG_OFFSET + (range * target);
}

static ptrdiff_t plic_offset_from_reg0(uint32_t irq) {
  uint8_t register_index = irq / RV_PLIC_PARAM_REG_WIDTH;
  return register_index * sizeof(uint32_t);
}

static uint8_t plic_irq_bit_index(uint32_t irq) {
  return irq % RV_PLIC_PARAM_REG_WIDTH;
}

/**
 * Get a target and an IRQ source specific Interrupt Enable register info.
 */
static plic_reg_info_t plic_irq_enable_reg_info(uint32_t irq, uint32_t target) {
  ptrdiff_t offset = plic_offset_from_reg0(irq);
  return (plic_reg_info_t){
      .offset = plic_irq_enable_base_for_target(target) + offset,
      .bit_index = plic_irq_bit_index(irq),
  };
}

static plic_reg_info_t plic_irq_trigger_type_reg_info(uint32_t irq) {
  ptrdiff_t offset = plic_offset_from_reg0(irq);
  return (plic_reg_info_t){
      .offset = RV_PLIC_LE_0_REG_OFFSET + offset,
      .bit_index = plic_irq_bit_index(irq),
  };
}

uint32_t interrupt_claim_request() {
  uint32_t* interrupt_claim_address = NULL;
  uint32_t interrupt_id;
  interrupt_claim_address =
      (uint32_t*)(PLIC_BASE_ADDRESS + RV_PLIC_CC0_REG_OFFSET);
  interrupt_id = *interrupt_claim_address;
  return interrupt_id;
}

void mach_plic_handler(__attribute__((unused)) uintptr_t int_id,
                       __attribute__((unused)) uintptr_t epc) {
  uint32_t interrupt_id;

  interrupt_id = plic_irq_claim();

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
  const uint32_t mask = index_to_mask(irq % 64);
  mem_write32(PLIC_BASE_ADDRESS, RV_PLIC_IE0_0_REG_OFFSET, mask);
}

void plic_set_trigger_type(uint32_t index) {
  mem_write32(PLIC_BASE_ADDRESS, RV_PLIC_LE_0_REG_OFFSET, index);
}

void plic_irq_set_enabled(uint32_t irq, uint8_t state, uint32_t target) {
  plic_reg_info_t reg_info = plic_irq_enable_reg_info(irq, target);

  uint32_t reg = mem_read32(PLIC_BASE_ADDRESS, reg_info.offset);
  reg = bitfield_bit32_write(reg, reg_info.bit_index, state);
  mem_write32(PLIC_BASE_ADDRESS, reg_info.offset, reg);
}

void plic_irq_set_trigger(uint32_t irq, uint32_t trigger) {
  bool flag = trigger == 0 ? false : true;
  plic_reg_info_t reg_info = plic_irq_trigger_type_reg_info(irq);

  uint32_t reg = mem_read32(PLIC_BASE_ADDRESS, reg_info.offset);
  reg = bitfield_bit32_write(reg, reg_info.bit_index, flag);
  mem_write32(PLIC_BASE_ADDRESS, reg_info.offset, reg);
}

uint32_t plic_irq_claim() {
  uint32_t claim_data = mem_read32(PLIC_BASE_ADDRESS, RV_PLIC_CC0_REG_OFFSET);
  return claim_data;
}

void plic_irq_complete(const uint32_t complete_data) {
  // Write back the claimed IRQ ID to the target specific CC register,
  // to notify the PLIC of the IRQ completion.
  mem_write32(PLIC_BASE_ADDRESS, RV_PLIC_CC0_REG_OFFSET, complete_data);
}

void plic_init(int p_id, uint32_t t_id) {
  plic_set_threshold(2);
  plic_set_priority(p_id, 3);
  plic_irq_set_enabled(p_id, true, 0);
  plic_irq_set_trigger(p_id, t_id);
}

void attach_interrupt(int int_id, void(*isr), int gpio_trigger_id) {
  // gpio_trigger_id = 1 or 2 means plic should be edge triggered, hence
  // value 1.
  int plic_trigger_id = gpio_trigger_id < 2 ? 1 : 0;

  plic_init(int_id, plic_trigger_id);
  gpio_intr_enable(int_id);
  gpio_intr_type(int_id, gpio_trigger_id);

  isr_table[int_id] = isr;

  // Enable Global (PLIC) interrupts.
  asm volatile(
      "li      t0, 8\t\n"
      "csrrs   zero, mstatus, t0\t\n");

  // Enable Local (PLIC) interrupts.
  asm volatile(
      "li      t0, 0x800\t\n"
      "csrrs   zero, mie, t0\t\n");
}