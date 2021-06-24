#include "exti.h"



void EXT_Init( void ){
	/* enable AFIO clock */
	RCC->APB2ENR |= 0x01;
	/* config external alter pin */
	AFIO->EXTICR[0] |= 0x01;
	/* clear Pending register */
	EXTI->PR= 0x01;
	/* set interrupts falling edge */
	//EXTI->FTSR |= 0x01;
	EXTI->FTSR |= 0x01;
	/* set interrupts rising edge */
	EXTI->RTSR |= 0x01;
	/* disable software interrupts */
	EXTI->SWIER &= ~0x01;
	/* set interrupts mask register */
	EXTI->IMR |= 0x01;
	/* enable NVIC */
	NVIC->ISER[0]= 0x01<<6U;
}


