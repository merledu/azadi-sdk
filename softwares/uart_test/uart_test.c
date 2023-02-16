#include "uart.h"

#include "platform.h"

int main() {
  int count = 0;
  char str[6] = "waleed";
  char recv_str[6];
  uart_t uart0, uart1;

  uart0.baud_rate = 9600;
  uart0.base_address = UART0_BASE_ADDRESS;
  uart_t* uart0_ptr = &uart0;

  uart1.baud_rate = 9600;
  uart1.base_address = UART1_BASE_ADDRESS;
  uart_t* uart1_ptr = &uart1;

  uart_init(uart1_ptr);
  uart_send(uart1_ptr, str);

  uart_init(uart0_ptr);

  while (count < 6) {
    recv_str[count++] = uart_recv_byte_polled(uart0_ptr);
  }

  return 0;
}
