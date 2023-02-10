#include "uart.h"

#include "platform.h"

int main() {
  uart_t uart0 = {9600, UART0_BASE_ADDRESS};
  uart_t uart1 = {9600, UART1_BASE_ADDRESS};
  char str[6] = "waleed";
  char recv_str[6];
  uart_init(&uart0);
  uart_send(&uart0, str);

  uart_init(&uart1);
  int count = 0;
  while (count < 6) {
    recv_str[count++] = uart_recv_byte_polled(&uart1);
  }

  return 0;
}
