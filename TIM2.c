/*===========================================
************** NOTE **************
* The AHB1 clock time2 is 72MHz
* So that we caculate the CK_CNT freg is: 72MHz / (72 -1) = 1 MHz
* It mean: 1 Tich coresspondig 10^-6 s
* So with 1000 ticks coressponding 1ms
==============================================*/



#include "TIM2.h"



volatile uint32_t u32TimeCount= 0;
volatile BitAction stateLed= 0;

/*-------------------------- REGISTER SECTION -------------------------------*/
void TIM2_config( void ){
	/* ENABLE TIMER2 CLOCK */
	RCC->APB1ENR |= 0x01;
	/* TIMx auto-reload register (TIMx_ARR) */
	TIM2->ARR = 0xFFFF;
	/* TIMx prescaler (TIMx_PSC) */
	TIM2->PSC = 72 - 1;
	/* TIMx control register 1 (TIMx_CR1): ENABLE COUNTER */
	TIM2->CR1 |= 0x01;
	/* SETUP COUNTER UP */
	TIM2->CR1 &= ~(0x01<< 4U);
	/* Re-initialize the counter and generates an update of the registers */
	TIM2->EGR |= 0x01;
}

void configGpio( void ){
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC,  &GPIO_InitStruct);
	GPIO_WriteBit( GPIOC,  GPIO_Pin_13, Bit_SET);
}

void delay( uint32_t grep ){
	while(grep){
		TIM2->CNT= 0u;
		while( TIM2->CNT < 1000u);
		grep--;
	}
}

void blinkLed( void ){
	GPIO_WriteBit( GPIOC,  GPIO_Pin_13, Bit_RESET);
	delay(1000);
	GPIO_WriteBit( GPIOC,  GPIO_Pin_13, Bit_SET);
	delay(1000);
}

/*---------------------------------- STANDARD REGISTER ------------------------------*/
void TIM2_StandardConfig( void ){
	/* Enable clock tim2 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	/* setup tim2 */
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72 -1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 0xFFFF;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct );
	TIM_Cmd(TIM2, ENABLE);
}


void delayMsStandard( uint32_t grep){
	while( grep ){
		TIM_SetCounter(TIM2, 0);
		while(TIM_GetCounter(TIM2)<1000u);
		grep--;
	}
}

void blinkLed1( void ){
	GPIO_WriteBit( GPIOC,  GPIO_Pin_13, Bit_RESET);
	delayMsStandard(1000);
	GPIO_WriteBit( GPIOC,  GPIO_Pin_13, Bit_SET);
	delayMsStandard(1000);
}

/*================================= INTERRUPTS ==============================*/
void TIM2_interruptsConfig( void ){
	/* ENABLE TIMER2 CLOCK */
	RCC->APB1ENR |= 0x01;
	/* TIMx prescaler (TIMx_PSC) */
	TIM2->PSC = 7200 - 1; // 0.1s -> 1 tick
	/* TIMx auto-reload register (TIMx_ARR) */
	TIM2->ARR = 10000 -1; 
	/* TIMx control register 1 (TIMx_CR1): ENABLE COUNTER */
	TIM2->CR1 |= 0x01;
	/* reset counter */
	TIM2->CNT = 0;
	/* clear interrupt flag */
	TIM2->SR &= ~(0x01);
	/* SETUP COUNTER UP */
	TIM2->CR1 &= ~(0x01<< 4U);
	/* Re-initialize the counter and generates an update of the registers */
	TIM2->EGR |= 0x01;
	/* set update interrupts enable */
	TIM2->DIER |= 0x01;
	/* enable interrupts */
	NVIC->ISER[0] = 0x01<<28;
}

void TIM2_IRQHandler( void ){
	if( (TIM2->DIER & 0x01)  && (TIM2->SR& 0x01) ){
		TIM2->SR &= ~(0x01);
		stateLed = ~stateLed;
		GPIO_WriteBit( GPIOC,  GPIO_Pin_13, stateLed);
	}
}

