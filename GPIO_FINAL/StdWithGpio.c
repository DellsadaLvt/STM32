#include"StdWithGpio.h"

void GpioConfig_( void )
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* enable APB2 IN GPIO C AND A */
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA| RCC_APB2Periph_GPIOC, ENABLE);
	
	/* setup pa0 is the input */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	//GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* set pc13 is output */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( GPIOC, &GPIO_InitStructure);
	
	//GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
}

void GpioControl( void )
{
	if(GPIO_ReadInputDataBit(GPIOA,  GPIO_Pin_0))
			GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
		else
			GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
			
}
