#include "Timer.h"

void Timer2_init( void ){
	/* enable clock timer 2 */
	RCC->APB1ENR |= 0x01;
	/* disable counter */
	TIM2->CR1 &= ~0x01;
	/* Bit 4 DIR: Direction
	0: Counter used as upcounter */
	//TIM2->CR1 |= 0x01;
	/* Bit 3 OPM: One-pulse mode
  0: Counter is not stopped at update event */
	/* Bit 2 URS: Update request source: 0 */
	/* Bit 1 UDIS: Update disable: 0 */
	/* set prescaler */
	TIM2->PSC = 72u - 1u;
	/* auto reload register */
	TIM2->ARR = 0xFFFF;
	/* set UG bit */
	TIM2->EGR |= 0x01;
	/* Bit 0 UIE: Update interrupt enable */
	TIM2->DIER |= 0x01;
	/* enable interrupts */
//	NVIC->ISER[0] = 0x01 << 28u;
	/* reset counter */
	TIM2->CNT = 0;
	/* enable counter */
	TIM2->CR1 |= 0x01;
}


void enableTimer2( state stateTimer2, state stateClockTimer2 ){
	if( stateClockTimer2 == enable ){
		/* enable clock timer 2 */
		RCC->APB1ENR |= 0x01;
	}
	else{
		/* disable clock timer 2 */
		RCC->APB1ENR &= ~0x01;
	}
	
	
	if( stateTimer2 == enable ){
		/* enable counter */
		TIM2->CR1 |= 0x01;
	}
	else{
		/* disable counter timer 2 */
		TIM2->CR1 &= ~0x01;
	}
	
}

void delay( uint16_t grep ){
	Timer2_init();
	while( grep ){
		TIM2->CNT = 0u;
		while( TIM2->CNT < 1000 );
		grep--;
	}
	enableTimer2( disable, disable );
}
