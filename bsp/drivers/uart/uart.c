#include "uart.h"
#include "uart_regs.h"
#include "utils.h"

void Set_Baud_Rate(int baud_rate)
{


unsigned int baud_count = 0;
int val = 16;
baud_count = Clock_Frequency/(16*baud_rate);
int *baud;
baud = (int*)(UART_BASE_ADDRESS + Cntrl_Register_Offset);
*baud = (baud_count<<val) ;
}

void Uart_Tx_Rdy(char val) {

uint32_t nco = mem_read32(UART_BASE_ADDRESS, Cntrl_Register_Offset);

//enabling system loop back
//int *uart_loopback;
//uart_loopback = (char*)(UART_BASE_ADDRESS + Cntrl_Register_Offset);
//*uart_loopback = 1 << 4;

//enabling tx
int *tx;
tx = (int *)(UART_BASE_ADDRESS + Cntrl_Register_Offset);
*tx = 17 | nco;


//writing character to tx or write_data register
char *uart_write;
uart_write = (char*)(UART_BASE_ADDRESS + UART_WRITE_DATA);
*uart_write = val;


 __asm__ __volatile (

//tx watermark
"sw x5 , 0x4(s0);"

//tx_empty
"li x5 , 1;"
"li x7 , 2;"
"sll x6 , x5 , x7;"
"sw x6 , 0x4(s0);"

//txilvl
"li x5 , 0;"
"li x7 , 0x5;"
"sll x8 , x5 , x7;"
"sw x5 , 0x1c(s0);"
);


}


int Uart_Rx_Rdy()
{  

    
__asm__ __volatile__( 
    "li x5 , 1;"
    "li s0 , 0x40060000;"
    //rx enable
    "sll x6 ,x5 ,x5;"
    "sw x6 , 0xc(s0);"
    //rx watermark
    "sll x6 , x5, x5;"
    "sw x6 , 0x4(s0); "
    //rx overflow
    "li x7, 3;"
    "sll x6 , x5 , x7;"
    "sw x6 , 0x4(s0);"
    //rx frm err
    "li x7 , 4;"
    "sll x6 , x5 , x7;"
    "sw x6 , 0x4(s0);"
    //rx brk err
    "li x7 , 5;"
    "sll x6 , x5 , x7;"
    "sw x6 , 0x4(s0);"
    //rx timeout
    "li x7 , 6;"
    "sll x6 , x5 , x7;"
    "sw x6 , 0x4(s0);"

    //LLPBK
"li x7 , 5;"
"sll x5 , x5 ,x7;"
"sw x5 , 0xc(s0);"

//RXILVL
"li x5 , 0;"
"li x7 , 0x2;"
"sll x8 , x5 , x7;"
"sw x5 , 0x1c(s0);"
);
}



