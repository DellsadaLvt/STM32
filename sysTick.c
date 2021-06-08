#include "sysTick.h"

/*================================
note: the systick use AHP clock with frequence max is 72MHz;
================================*/


volatile uint32_t counter= 0, counterTime= 0;

void sysTickConfig( uint32_t tick ){
	/* disable systick */
	SysTick->CTRL = 0;
	/* init the RELOAD value */
	SysTick->LOAD = tick -1u;
	/* set priority  */
	NVIC_SetPriority (SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL);
	/* reset current counter */
	SysTick->VAL = 0;
	/* select clock */
	SysTick->CTRL |= 0x04;
	/* enable systick interrupts */
	SysTick->CTRL |= 0x02;
	/* enable systick */
	SysTick->CTRL |= 0x01;
}



void configGpio( void ){
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC,  &GPIO_InitStruct);
	GPIO_WriteBit( GPIOC,  GPIO_Pin_13, Bit_RESET);
}


void SysTick_Handler( void ){
	/* check flag counter */
	if( (SysTick->CTRL>>16u & 0x01u)  ){
		if( counter > 0)
			counter--;
		counterTime = counterTime + 1;
	}
}

void delay_ms( uint32_t grep){
	counter = grep;
	while(counter);
}

float getTime( void ){
	SysTick->CTRL = 0;
	float time;
	time = counterTime + ((71999 - SysTick->VAL)/71999.0);
	return time;
}


