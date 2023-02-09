#include "uart.h"

int main() {
  //   char *str = "waleed";
  // uart_init(9600, 10000000);
  // uart_send_str(str);
  // uart_init(9600, 16000000);
  // Uart_Send_Str(str);

  uart_init(9600, 16000000);
  uart_send("waleed");
  return 0;
}
