#include "uart.h"

int main() {
  //   char *str = "waleed";
  // uart_init(9600, 10000000);
  // uart_send_str(str);
  // uart_init(9600, 16000000);
  // Uart_Send_Str(str);

  char str[6] = "waleed";
  uart_init(9600);
  uart_send(str);
  return 0;
}
