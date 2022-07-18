#define I2C_BASE_ADDRESS 0x400d0000
#define PRESCALE_L0_REGISTER_OFFSET 0x00
#define PRESCALE_HI_REGISTER_OFFSET 0x04
#define CONTROL_REGISTER_OFFSET 0x08
#define I2C_TX_REGISTER 0x0C
#define I2C_COMMAND_REGISTER 0x10
#define I2C_STATUS_REGISTER 0X10
#define I2C_RX_REGISTER 0x0C

void I2c_Prescalar();
void I2c_Transmit(unsigned char a, int Slave_Select);
int I2c_Recieve(int Slave_Select);