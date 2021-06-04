#include "EXTI.h"
#include "sysTick.h"

volatile BitAction state=0;

void GPIO_config( void ){
	/* config pin pc13 */
	RCC->APB2ENR |= 0x10;
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin= GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	GPIO_WriteBit(GPIOC, GPIO_Pin_13 , Bit_RESET);
	
	/* config pin b0 */
	RCC->APB2ENR |= 0x08;
	GPIO_InitStruct.GPIO_Pin= GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
}


void EXT0_config( void ){
	/* enable AFIO */
	RCC->APB2ENR |= 0x01;
	/* config pin interrupts */
	AFIO->EXTICR[0]|= 0x01;
	/* reset pending bit */
	EXTI->PR |= 0x01;
	/* select falling edge */
	EXTI->FTSR |= 0x01;
	/* disable rising edge */
	EXTI->RTSR &= ~(0x01);
	/* interrupts mask register */
	EXTI->IMR |= 0x01;
	/* disable event mask register */
	EXTI->EMR = 0x00;
	/* NVIC */
	NVIC->ISER[0] = 0x40;  // the EXT0 is in the 6th so the hex is 0100 0000:  0x40
}


void stdEXTI_config( void ){
	/* enable clock AFIO */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	/* config gpio */
	GPIO_EXTILineConfig( GPIO_PortSourceGPIOB, GPIO_PinSource0);
	/* clear pending bit */
	EXTI_ClearITPendingBit( EXTI_Line0 );
	/* config EXTI */
	EXTI_InitTypeDef EXTI_InitStruct;
	EXTI_InitStruct.EXTI_Line = EXTI_Line0;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStruct);
	/* config interrupts NVIC */
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	//NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);

}

void EXTI0_IRQHandler( void ){
	if(	EXTI->PR&0x01 && EXTI->IMR&0x01){
		state= ~state;
		GPIO_WriteBit(GPIOC, GPIO_Pin_13 , state);
		EXTI->PR |= 0x01;
	}
	
}

void softwareEXTI( void ){
		EXTI->SWIER = 0x01;
		delay_ms(1000);
}



