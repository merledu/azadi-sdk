/**
@file uart.c
@brief Contains the driver routines for UART interface.
@detail The UART driver .has software functions to configure, transmit 
and receive over UART interface.
*/

#include "uart.h"
#include "utils.h"
#include <math.h>
#include "timer.h"

void uart_init(unsigned int baud_rate , unsigned int clock_frequency){
	//computing formula : baud_rate = clock_frequency/baud_rate
	uint32_t clock_per_bit = (clock_frequency / baud_rate) + 1;
	mem_write32(UART_BASE_ADDRESS, UART_CNTRL_REGISTER_OFFSET, clock_per_bit);
}

void uart_send_char(char val ){
	//transmitting character 
	mem_write32(UART_BASE_ADDRESS, UART_WDATA_REGISTER_OFFSET, 	val);
    mem_write32(UART_BASE_ADDRESS, UART_TX_ENABLE_REGISTER_OFFSET, 1);

}

void uart_send_str(char *str){
	//transmitting string
	while(*str != '\0'){

		uart_send_char(*str++);
		delay(500);
	}
}

int uart_polled_data(){
	//polling uart
    mem_write32(UART_BASE_ADDRESS, UART_RX_ENABLE_REGISTER_OFFSET, 1);
	uint32_t rcv_status = mem_read32(UART_BASE_ADDRESS, UART_RX_STATUS_REGISTER_OFFSET);

	if(rcv_status == 1){
		uint32_t ret;
		return ret = mem_read32(UART_BASE_ADDRESS, UART_RDATA_REGISTER_OFFSET);
	}
	else{
		return -1;
	}
}


