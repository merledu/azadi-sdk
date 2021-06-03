#include "uart.h"
#include "utils.h"

void uart_init(uint32_t baud_rate , uint32_t clock_frequency){
	//computing formula : baud_rate = clock_frequency/baud_rate
	uint32_t clock_per_bit = clock_frequency / baud_rate;
	mem_write32(UART_BASE_ADDRESS, UART_CNTRL_REGISTER_OFFSET, clock_per_bit << 3);
}

void uart_send_char(char val ){
	//transmitting character 
	mem_write32(UART_BASE_ADDRESS, UART_WDATA_REGISTER_OFFSET, 	val);
	uint32_t nco = mem_read32(UART_BASE_ADDRESS, UART_CNTRL_REGISTER_OFFSET);
	mem_write32(UART_BASE_ADDRESS, UART_CNTRL_REGISTER_OFFSET, 1 | nco); 
}

void uart_send_str(char *str){
	//transmitting string
	while(*str != '\0'){
		uart_send_char(*str++)
	}
}

void uart_polled_data(){
	uint32_t rcv_status = mem_read32(UART_BASE_ADDRESS, UART_CNTRL_REGISTER_OFFSET);
	uint32_t rcv = rcv_status >> 3;
	mem_write32(UART_BASE_ADDRESS, UART_CNTRL_REGISTER_OFFSET, 	1 << 1);
	if(rcv == 1){
		uint32_t ret = mem_read32(UART_BASE_ADDRESS, UART_RDATA_REGISTER_OFFSET);
	}
	else{
		return -1;
	}
}


