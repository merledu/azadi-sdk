
#ifndef PLIC_DRIVER_H
#define PLIC_DRIVER_H
#include "trap.h"
#include "platform.h"
#include <stdbool.h>
#include <stddef.h>

/* Macros */

/* Offsets for different registers in plic */

// #define PLIC_PENDING_OFFSET             0x0UL
// #define PLIC_PRIORITY_OFFSET            0x0000UL
// #define PLIC_ENABLE_OFFSET              0x2000UL
// #define PLIC_THRESHOLD_OFFSET           0x10000UL
// #define PLIC_CLAIM_OFFSET               0x10010UL


#define PLIC_PRIORITY_SHIFT_PER_INT  2


#define PLIC_PRIORITY_1 0X30
#define PLIC_PRIORITY_2 0X34
#define PLIC_PRIORITY_3 0X38
#define PLIC_PRIORITY_4 0X3c
#define PLIC_PRIORITY_5 0X40
#define PLIC_PRIORITY_6 0X44
#define PLIC_PRIORITY_7 0X48

#define PLIC_PENDING_SHIFT_PER_SOURCE   0

/* Enumerators */

typedef enum
{
	INACTIVE = 0,
	ACTIVE   = 1,
	SERVICED = 2,
	MASKED
}interrupt_status_e;

/* Structures and Unions */

typedef struct
{
	uint32_t id; /*id of the interrupt target source*/
	uint32_t priority; /*priority assigned to it*/
	interrupt_status_e state; /*state of the interrupt*/
	uint32_t count; /*number of times this interrupt occured*/
} interrupt_data_t;


typedef void (*plic_fptr_t) (uint32_t);
extern plic_fptr_t isr_table[PLIC_MAX_INTERRUPT_SRC];

/* Function prototypes */

void interrupt_complete(uint32_t interrupt_id);
uint32_t interrupt_claim_request(void);
void isr_default(uint32_t interrupt_id);
void interrupt_enable(uint32_t interrupt_id);
void mach_plic_handler(uintptr_t int_id, uintptr_t epc);
void interrupt_disable(uint32_t interrupt_id);
void set_interrupt_threshold(uint32_t priority_value);
void set_interrupt_priority(uint32_t priority_value, uint32_t int_id, int priority);
void configure_interrupt_pin(uint32_t pin);
void plic_init(int p_id);
void configure_interrupt(uint32_t int_id);
void plic_set_trigger_type(uint32_t index);
void plic_set_threshold(uint32_t threshold);
void plic_set_priority(int irq, uint32_t priority);
void plic_enable_interrupt(uint32_t irq);
uint32_t plic_irq_claim();
void plic_irq_complete(const uint32_t complete_data);
// void plic_irq_set_enabled(uint32_t irq, bool state);
void plic_irq_set_enabled(uint32_t irq, uint8_t state);

// typedef struct bitfield_field32 {
//   /** The field mask. Usually all ones. */
//   uint32_t mask;
//   /** The field position in the bitfield, counting from the zero-bit. */
//   uint32_t index;
// } bitfield_field32_t;


// extern uint32_t bitfield_bit32_write(uint32_t bitfield,
//                                      uint32_t bit_index,
//                                      bool value);

// extern uint32_t bitfield_field32_write(uint32_t bitfield,
//                                        bitfield_field32_t field,
//                                        uint32_t value);
// extern bitfield_field32_t bitfield_bit32_to_field32(
//     uint32_t bit_index);

// extern uint32_t mem_read32(uint32_t base, ptrdiff_t offset);

#endif