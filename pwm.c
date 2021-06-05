#include "pwm.h"

void PWM_timer2_singleChannel_config( uint8_t width ){
	/* check parameter */
//	if(width > 100 )
//		width = 0;
	/* enable clock TIM2 */
	RCC->APB1ENR |= 0x01;
	/* set prescale 0.0001spt */
	TIM2->PSC = 7200 -1;
	/* set n ticks */
	TIM2->ARR = 40000 - 1; // 10000 ticks -> 1s
	/* chose mode pwm */
	TIM2->CCMR1 |= 0x60;   // choose 110 mode: pwm 1. activate channel 1, 2
	TIM2->CCMR2 |= 0x60;   // Activate channel 3,4
	/* set width of pulse */
	TIM2->CCR1 = 40000*width/100;  //  0.5s high, 0.5s low: pwm is 50%
	/* config CCER register */
	TIM2->CCER |= 0x01;		// bit CC1E: 1, bit CC1P: 0
	/* enable counter in CR1 register */
	TIM2->CR1 |= 0x01;
	/* update generate */
	TIM2->EGR |= 0x01;
}



void PWM_timer2_multiChannel_config( uint8_t width ){
	/* check parameter */
//	if(width > 100 )
//		width = 0;
	/* enable clock TIM2 */
	RCC->APB1ENR |= 0x01;
	/* set prescale 0.0001spt */
	TIM2->PSC = 7200 -1;
	/* set n ticks */
	TIM2->ARR = 40000 - 1; // 10000 ticks -> 1s
	/* chose mode pwm */
	TIM2->CCMR1 |= 0x6060;   // choose 110 mode: pwm 1. activate channel 1, 2
	TIM2->CCMR2 |= 0x6060;   // Activate channel 3,4
	/* set width of pulse */
	TIM2->CCR1 = 40000*width/100;  // 
	TIM2->CCR2 = 40000*30/100;     // set high with 30%
	TIM2->CCR3 = 40000*60/100;
	TIM2->CCR4 = 40000*80/100;
	/* config CCER register */
	TIM2->CCER |= 0x1111;		// bit CC1E: 1, bit CC1P: 0, capture/compare enable all
	/* enable counter in CR1 register */
	TIM2->CR1 |= 0x01;
	/* update generate */
	TIM2->EGR |= 0x01;
}


void  GPIO_PWM_TIM2_channel0( void ){
	/* enable clock port A */
	RCC->APB2ENR |= 0x04;
	/* Set alternate pin */
	/*
	GPIOA->CRL = 0U;
	GPIOA->CRL|= 0x03;
	GPIOA->CRL |= 0x08; //set pa0 is the alternate function input with pull up/down
	*/
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 ;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
}

void GPIO_PWM_TIM2_4channel( void){
	/* enable clock port A */
	RCC->APB2ENR |= 0x04;
	/* Set alternate pin */
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}


void PWM_TIM2_4channel_stdlib( uint8_t pwm1, uint8_t pwm2, uint8_t pwm3, uint8_t pwm4 ){
	/* enable clock timer2 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	/* setup timer 2 */
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 7200 -1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 40000-1;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct );
	TIM_Cmd( TIM2, ENABLE);
	/* setup pwm */
	// setup channel 1
	TIM_OCInitTypeDef TIM_OCInitStruct;
	TIM_OCInitStruct.TIM_OCMode= TIM_OCMode_PWM1 ;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_OCPolarity= TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_Pulse= 40000*pwm1/100;
	TIM_OC1Init(TIM2,&TIM_OCInitStruct );
	// setup channel 2
	TIM_OCInitStruct.TIM_OCMode= TIM_OCMode_PWM1 ;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_OCPolarity= TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_Pulse= 40000*pwm2/100;
	TIM_OC2Init(TIM2,&TIM_OCInitStruct );
	// setup channel 3
	TIM_OCInitStruct.TIM_OCMode= TIM_OCMode_PWM1 ;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_OCPolarity= TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_Pulse= 40000*pwm3/100;
	TIM_OC3Init(TIM2,&TIM_OCInitStruct );
	// setup channel 4
	TIM_OCInitStruct.TIM_OCMode= TIM_OCMode_PWM1 ;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_OCPolarity= TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_Pulse= 40000*pwm4/100;
	TIM_OC4Init(TIM2,&TIM_OCInitStruct );
}

