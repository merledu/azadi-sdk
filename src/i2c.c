#include "i2c.h"

#include <stdint.h>

#include "utils.h"

void I2c_Prescalar() {
  int prescalar = 0x5050;

  // parsing the bytes

  int first_byte = prescalar & 0x0f;
  int Second_byte = (prescalar & 0xf0) >> 4;
  int byte1 = (Second_byte << 4) | first_byte;
  int Third_byte = (prescalar & 0xf00) >> 8;
  int Fourth_byte = (prescalar & 0xf000) >> 12;
  int byte2 = (Fourth_byte << 4) | Third_byte;

  // writing on prescalar lo register
  int* pre;
  pre = (int*)(I2C_BASE_ADDRESS + PRESCALE_L0_REGISTER_OFFSET);
  *pre = byte1;

  // writing on prescalar hi register
  int* pre1;
  pre1 = (int*)(I2C_BASE_ADDRESS + PRESCALE_HI_REGISTER_OFFSET);
  *pre1 = byte2;
}

void I2c_Transmit(unsigned char a, int Slave_Select) {
  // cntrl register configuration

  // enabling i2c
  // int *en;
  // en = (int *)(I2C_BASE_ADDRESS + CONTROL_REGISTER_OFFSET );
  //*en = (1 << 7);

  // Interrupt enable
  int* ie;
  ie = (int*)(I2C_BASE_ADDRESS + CONTROL_REGISTER_OFFSET);
  *ie = (3 << 6);

  // high start bit
  int* start;
  start = (int*)(I2C_BASE_ADDRESS + I2C_COMMAND_REGISTER);
  *start = 1 << 7;

  // slave select
  int* addr;
  addr = (int*)(I2C_BASE_ADDRESS + I2C_TX_REGISTER);
  *addr = Slave_Select << 1;

  // reading acknowledgement

  uint32_t ack_32 = mem_read32(I2C_BASE_ADDRESS, I2C_STATUS_REGISTER);
  uint32_t acknow = ack_32 >> 7;

  if (acknow == 0) {
    // transmission
    int* tx;
    tx = (int*)(I2C_BASE_ADDRESS + I2C_TX_REGISTER);
    *tx = a;

    // stop bit high
    int* stop;
    stop = (int*)(I2C_BASE_ADDRESS + I2C_COMMAND_REGISTER);
    *stop = 1 << 6;

    // Setting WR bit
    int* wr;
    wr = (int*)(I2C_BASE_ADDRESS + I2C_COMMAND_REGISTER);
    *wr = 1 << 4;

    uint32_t ack_32 = mem_read32(I2C_BASE_ADDRESS, I2C_STATUS_REGISTER);
    uint32_t acknow = ack_32 >> 7;
  }

  else {
    // stop bit high
    int* stop;
    stop = (int*)(I2C_BASE_ADDRESS + I2C_COMMAND_REGISTER);
    *stop = 1 << 6;
  }
}

int I2c_Recieve(int Slave_Select) {
  // enabling i2c
  int* en;
  en = (int*)(I2C_BASE_ADDRESS + CONTROL_REGISTER_OFFSET);
  *en = (1 << 7);

  // Interrupt enable
  int* ie;
  ie = (int*)(I2C_BASE_ADDRESS + CONTROL_REGISTER_OFFSET);
  *ie = 1 << 6;

  // Slave_Select
  int* read;
  read = (int*)(I2C_BASE_ADDRESS + I2C_RX_REGISTER);
  *read = 1;

  // for reading
  int* addr;
  addr = (int*)(I2C_BASE_ADDRESS + I2C_TX_REGISTER);
  *addr = Slave_Select << 1;

  // high start bit
  int* start;
  start = (int*)(I2C_BASE_ADDRESS + I2C_COMMAND_REGISTER);
  *start = 1 << 7;

  // Setting WR bit
  int* wr;
  wr = (int*)(I2C_BASE_ADDRESS + I2C_COMMAND_REGISTER);
  *wr = 1 << 4;

  // Setting RD bit
  int* rd;
  rd = (int*)(I2C_BASE_ADDRESS + I2C_COMMAND_REGISTER);
  *rd = 1 << 5;

  // Setting ACK to 1
  int* acknowledgment;
  acknowledgment = (int*)(I2C_BASE_ADDRESS + I2C_COMMAND_REGISTER);
  *acknowledgment = 1 << 3;

  // stop bit high
  int* stop;
  stop = (int*)(I2C_BASE_ADDRESS + I2C_COMMAND_REGISTER);
  *stop = 1 << 6;

  // reading data
  uint32_t data = mem_read32(I2C_BASE_ADDRESS, I2C_RX_REGISTER);
  return data;
}
