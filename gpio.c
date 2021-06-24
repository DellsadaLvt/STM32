#include "gpio.h"

void GpioConfig( void ){
	/* enable clock */
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE );
	
	/* config pc13 as output */
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin= GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode= GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
	
	/* config pa0 as input button */
	GPIO_InitStruct.GPIO_Pin= GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode= GPIO_Mode_IPU;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
}


