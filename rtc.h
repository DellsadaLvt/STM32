#include "stm32f10x.h"                  // Device header


void configGpio( void );
uint32_t setBit( uint8_t pos );
void configRTC( void );
void blinkLed( void );
uint16_t  counterSecond( void );
void configIntRTC( void );
