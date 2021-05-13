#include "stm32f10x.h"                  // Device header



typedef  enum{
	so0 = 0,
	so1 = 1,
	so2 = 2,
	so3 = 3
}numb;

void Config( void );
void SetAll( void );
void ResetAll( void );
void HienThi( numb so);
void Delay( uint16_t reg );
void test_0( void );
void BlinkLed13( void );


