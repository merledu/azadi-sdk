#include "uart.h"
void Tx_Empty_Isr()
{
//interrupt disable tx_empty = 0;
int *tx_empty;
tx_empty = (int*)(UART_BASE_ADDRESS + UART_INTR_ENABLE_REG);
*tx_empty = 0<<2;

//tx enable signal = 0;
int *tx_enable;
tx_enable = (int*)(UART_BASE_ADDRESS + Cntrl_Register_Offset);
*tx_enable = 0;
}