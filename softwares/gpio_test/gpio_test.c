#include "gpio.h"

#include "timer.h"

int main() {
  digital_write(5, 1);
  delay(100);
  digital_write(7, 1);
  return 0;
}