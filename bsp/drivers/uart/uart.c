// #include "uart.h"

// void Set_Baud_Rate(int baud_rate)
// {
//   unsigned int baud_count = 0;
//   int val = 16;
//   baud_count = Clock_Frequency/(16*baud_rate);
//   int *baud;
//   baud = (int*)(UART_BASE_ADDRESS + Cntrl_Register_Offset);
//   *baud = (baud_count<<val);
// }

// void Uart_Tx_Rdy(char val) {

// char *uart_write;
// uart_write = (char*)(UART_BASE_ADDRESS + UART_WRITE_DATA);
// *uart_write = val;
//  __asm__ __volatile (

// //writing value of tx to control register
// "li s0 , 0x40060000;" //uart_base_address
// "li x5 , 1;" 
// "sw x5 , 0xc(s0);" //storing value of x5

// //tx watermark
// "sw x5 , 0x4(s0);"

// //tx_empty
// "li x5 , 1;"
// "li x7 , 2;"
// "sll x6 , x5 , x7;"
// "sw x6 , 0x4(s0);"

// //txilvl
// "li x5 , 0;"
// "li x7 , 0x5;"
// "sll x8 , x5 , x7;"
// "sw x5 , 0x1c(s0);"

// //SLPBK
// "li x7 , 4;"
// "sll x5 , x5 ,x7;"
// "sw x5 , 0xc(s0);"
// );
// }

// int Uart_Rx_Rdy()
// {  
// __asm__ __volatile__( 
//     "li x5 , 1;"
//     "li s0 , 0x40060000;"
//     //rx enable
//     "sll x6 ,x5 ,x5;"
//     "sw x6 , 0xc(s0);"
//     //rx watermark
//     "sll x6 , x5, x5;"
//     "sw x6 , 0x4(s0); "
//     //rx overflow
//     "li x7, 3;"
//     "sll x6 , x5 , x7;"
//     "sw x6 , 0x4(s0);"
//     //rx frm err
//     "li x7 , 4;"
//     "sll x6 , x5 , x7;"
//     "sw x6 , 0x4(s0);"
//     //rx brk err
//     "li x7 , 5;"
//     "sll x6 , x5 , x7;"
//     "sw x6 , 0x4(s0);"
//     //rx timeout
//     "li x7 , 6;"
//     "sll x6 , x5 , x7;"
//     "sw x6 , 0x4(s0);"

//     //LLPBK
// "li x7 , 5;"
// "sll x5 , x5 ,x7;"
// "sw x5 , 0xc(s0);"
// );




// }

// void Uart_Interrupt_Routine()
// {
// int *intr_state;
// intr_state = (int*)(UART_BASE_ADDRESS + UART_INTR_STATE_REG);
// int intr_state_mask = 0;
// char uart_ch;
// int *intr_enable_reg;

//   // Turn off Interrupt Enable
//   intr_enable_reg = (int*)(UART_BASE_ADDRESS + UART_INTR_ENABLE_REG);
//   //(int*)(UART_BASE_ADDRESS +UART_INTR_ENABLE_REG) = (UART_BASE_ADDRESS + UART_INTR_ENABLE_REG) & 0xFFFFFF00; 
// *intr_enable_reg = 0x40060004 & 0xFFFFFF00;

// if (*intr_state & UART_INTR_STATE_RX_BREAK_ERR_MASK) {
//     // Do something ...

//   __asm__  __volatile__(

//      "li s0 , 0x40060000;"
//       "li x5 , 0;"
//       "sw x5 , 0x4(s0);"
//   );
//   }
// }
