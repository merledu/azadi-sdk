
#ifndef PLATFORM_H
#define PLATFORM_H

/*
 *@brief RISCV - SOC Memory mapping
 */

#define CLOCK_FREQUENCY 50000000
#define CLINT_BASE 0x020000000
#define MTIME 0x0200BFF8
#define MTIMECMP 0x02004000

#define MCAUSE_INT 0x80000000
#define MCAUSE_CAUSE 0x7FFFFFFF

#define PINMUX_CONFIGURE_REG 0x40310

/*!Debugger Offset */
#define DBG_MEM_START 0x00000010

/*!Tightly Coupled Memory(TCM) Offset. Size 128kB */
#define TCM_MEM_START 0x80000000 /*! DDR3 Memory Start address */

/*!Tightly Coupled Memory(TCM) Size. Size 128kB */
#define TCM_MEM_SIZE 0x20000 /*! DDR3 Memory Size */

/*!Percentage of Free Memory to be used as stack (0-100). The remaining space
 * will be used by heap */
#define STACK_PERCENTAGE 50 /*! DDR3 Memory Size */

/*!Percentage of Free Memory to be used as stack (0-100). The remaining space
 * will be used by heap */
#define HEAP_PERCENTAGE 50 /*! DDR3 Memory Size */

/*!Pulse Width Modulation Start Offsets */
#define PWM0_START 0x40004000 /*PWM Base address*/
#define PWM1_START 0x40004100 /*PWM Base address*/
#define PWM2_START 0x40004200 /*PWM Base address*/
#define PWM3_START 0x40004300 /*PWM Base address*/

/*!Serial Peripheral Interface Offsets */
#define SPI0_START 0x40003000 /* Serial Peripheral Interface 0 */
#define SPI1_START 0x40003100 /* Serial Peripheral Interface 1 */
#define SPI2_START 0x40003200 /* Serial Peripheral Interface 2 */
#define SPI3_START 0x40003300 /* Serial Peripheral Interface 3 */

/*!Universal Synchronous Receiver Transmitter Interface Offsets */
#define UART0_BASE_ADDRESS 0x40002000 /*! UART 0 */
#define UART1_BASE_ADDRESS 0x40002100
#define UART2_BASE_ADDRESS 0x40002200
#define UART3_BASE_ADDRESS 0x40002300
#define MAX_UART_COUNT 4

#define PINMUX_CONFIGURE_REG 0x40310

/* Timer Interrupt Controller */
#define TIC_BASE_ADDRESS 0x30003000

/* TIMER */
#define TIMER0_BASE_ADDRESS 0x30000000
#define TIMER1_BASE_ADDRESS 0x30001000
#define TIMER2_BASE_ADDRESS 0x30002000

/*! Programmable Logic Interrupt Interface */
#define PLIC_BASE_ADDRESS 0x50000000 /*! PLIC Interface Start */
#define PLIC_INTERRUPT_1 1
#define PLIC_INTERRUPT_2 2
#define PLIC_INTERRUPT_3 3
#define PLIC_INTERRUPT_4 4
#define PLIC_INTERRUPT_5 5
#define PLIC_INTERRUPT_6 6
#define PLIC_INTERRUPT_7 7
#define PLIC_INTERRUPT_8 8
#define PLIC_INTERRUPT_9 9
#define PLIC_INTERRUPT_10 10
#define PLIC_INTERRUPT_11 11
#define PLIC_INTERRUPT_12 12
#define PLIC_INTERRUPT_13 13
#define PLIC_INTERRUPT_14 14
#define PLIC_INTERRUPT_15 15
#define PLIC_INTERRUPT_16 16
#define PLIC_INTERRUPT_25 25  // uart 0
#define PLIC_INTERRUPT_26 26  // uart 1
#define PLIC_INTERRUPT_27 27  // uart 2
#define PLIC_MAX_INTERRUPT_SRC 64

/*!General Purpose Input Output */
#define GPIO_START 0x40001000  // GPIO Start Address
#define GPIO_OFFSET 0x04       /*!Generic offset used to access GPIO registers*/

/*
 * General Purpose IOs supported
 */

#define GPIO0 (1 << 0)
#define GPIO1 (1 << 1)
#define GPIO2 (1 << 2)
#define GPIO3 (1 << 3)
#define GPIO4 (1 << 4)
#define GPIO5 (1 << 5)
#define GPIO6 (1 << 6)
#define GPIO7 (1 << 7)
#define GPIO8 (1 << 8)
#define GPIO9 (1 << 9)
#define GPIO10 (1 << 10)
#define GPIO11 (1 << 11)
#define GPIO12 (1 << 12)
#define GPIO13 (1 << 13)
#define GPIO14 (1 << 14)
#define GPIO15 (1 << 15)
#define GPIO16 (1 << 16)
#define GPIO17 (1 << 17)
#define GPIO18 (1 << 18)
#define GPIO19 (1 << 19)
#define GPIO20 (1 << 20)
#define GPIO21 (1 << 21)
#define GPIO22 (1 << 22)
#define GPIO23 (1 << 23)
#define GPIO24 (1 << 24)
#define GPIO25 (1 << 25)
#define GPIO26 (1 << 26)
#define GPIO27 (1 << 27)
#define GPIO28 (1 << 28)
#define GPIO29 (1 << 29)
#define GPIO30 (1 << 30)
#define GPIO31 (1 << 31)
#define GPIO_COUNT 0x20

#endif
