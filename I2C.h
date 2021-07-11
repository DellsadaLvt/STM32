#include "stm32f10x.h"                  // Device header
#include "Timer.h"


#define posClockI2C1  21u 

void I2C_init( void );
void sendData( uint8_t I2C_Address, uint8_t address, uint8_t value );
void ReceiveOneByte( uint8_t I2C_Address, uint8_t address, uint8_t *data );
int i2c_readbyte(char saddr,char maddr,uint8_t *data);
