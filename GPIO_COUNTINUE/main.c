#include "stm32f10x.h"
#include "GPIO_STM32F10x.h"

void GPIO_config_PC13( void );
void Delay( uint16_t rep );



int main( void )
{
	
	GPIO_config_PC13();
	
	while(1)
	{
//		GPIOC->ODR |= 0x2000;
//		Delay( 50);
//		GPIOC->ODR &= ~0x2000;
//		Delay( 50);
		GPIO_PinWrite (GPIOC, 13, 1);
		Delay(30);
		GPIO_PinWrite (GPIOC, 13, 0);
		Delay(30);
		
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



//void GPIO_Config(void)
//{ 
//   GPIO_InitTypeDef  GPIO_InitStructure; 
//   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
//   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
//   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//   GPIO_Init(GPIOC, &GPIO_InitStructure); 
//}
