#include "stm32f10x.h"


void GPIO_config_PC13( void );
void Delay( uint16_t rep );

int main( void )
{
	
	GPIO_config_PC13();
	
	while(1)
	{
		GPIOC->ODR |= 0x2000;
		Delay( 50);
		GPIOC->ODR &= ~0x2000;
		Delay( 50);
	}

}


void GPIO_config_PC13( void )
{
	RCC->APB2ENR |= 0x10;
	GPIOC->CRH &= 0xFF0FFFFF;
	GPIOC->CRH	|= 0x00300000;
}


void Delay( uint16_t rep )
{
	for(; rep>0; rep--)
		{
			for( int i=0; i<100000; i++)
			{
			}
		}
}
