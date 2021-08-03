#include "GPIO_STM32F10x.h"


void gpio_config( void );
void control_pc13( void );
void delay( uint16_t rep);


int main( void)
{
	RCC->APB2ENR = 0x10;
	gpio_config();
	while(1)
		control_pc13();
	
	
	return 0;
}


void gpio_config( void )
{
	GPIOC->CRH &= 0;
	GPIOC->CRH |= 0x00300000;
}

void control_pc13( void )
{
	GPIOC->ODR |= 0x2000;
	delay(1000);
	GPIOC->ODR &= ~0x2000;
	delay(1000);
}

void delay( uint16_t rep)
{
	for( ; rep >0; rep --)
	{
		for( int i=0; i< 10000; i++)
		{
		}
	}
}