#include "rtc.h"


uint32_t setBit( uint8_t pos){
	return ((uint32_t)0x01 << pos);
}


void configGpio( void ){
	/* open clock port c */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	/* config GPIO C13 to control led */
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	/* turn off led pc13 */
	GPIO_WriteBit( GPIOC, GPIO_Pin_13, Bit_SET);
}


void configRTC( void ){
	
	/*====== SECTION 1 ======*/
	/* set BKPEN */
	RCC->APB1ENR |= setBit(27u);
	
	/*  set PWREN */
	RCC->APB1ENR |= setBit(28u);
	
	/* set DBP */
	PWR->CR |= setBit(8u);
	
	
	/*=== SECTION 2 ===*/
	/* set LSEON */
	RCC->BDCR |= 0x01U;
	
	/* wait LSEON is stated */
	while( ((RCC->BDCR >> 1U) & (uint32_t)0x01)  != 1u);
	
	/* select RTC clock source */
	RCC->BDCR |= setBit(8u);
	RCC->BDCR &= ~setBit(9u);
	
	/* set RTCEN */
	RCC->BDCR |= setBit(15);
	
	/*=== SECTION 3 ===*/
	/* configuring RTC register */
	/* wait RTOFF */
	while(  ((RTC->CRL >> 5u)& (uint32_t)0x01)  != 0x01 );
	/* set CNF bit */
	RTC->CRL |= setBit( 4u );
	/* write one or more RTC register */
	/* RTC prescaler load register setup */
	RTC->PRLH = 0X0000;
	RTC->PRLL = 0x7fff;
	/* clear CNF  */
	RTC->CRL &= ~setBit( 4u );
	/* wait  RTOFF*/
	while( ((RTC->CRL >> 5U) & 0x01) != 0x01 );
	
}


uint16_t counterSecond( void ){
	static uint16_t counter = 0;
	if( RTC->CRL & 0x0001  ){
		counter++;
		RTC->CRL &= ~setBit(0u);
	}
	return counter;
}


void blinkLed( void ){
	
	if( counterSecond()%2){
			GPIO_WriteBit( GPIOC, GPIO_Pin_13, Bit_SET);
		}else{
			GPIO_WriteBit( GPIOC, GPIO_Pin_13, Bit_RESET);
		}
	
}


void configIntRTC( void ){
	/*====== SECTION 1 ======*/
	/* set BKPEN */
	RCC->APB1ENR |= setBit(27u);
	/*  set PWREN */
	RCC->APB1ENR |= setBit(28u);
	/* set DBP */
	PWR->CR |= setBit(8u);
	
	
	/*=== SECTION 2 ===*/
	/* set LSEON */
	RCC->BDCR |= 0x01U;
	/* wait LSEON is stated */
	while( ((RCC->BDCR >> 1U) & (uint32_t)0x01)  != 1u);
	/* select RTC clock source */
	RCC->BDCR |= setBit(8u);
	RCC->BDCR &= ~setBit(9u);
	/* set RTCEN */
	RCC->BDCR |= setBit(15);
	
	/*=== SECTION 3 ===*/
	/* configuring RTC register */
	/* wait RTOFF */
	while(  ((RTC->CRL >> 5u)& (uint32_t)0x01)  != 0x01 );
	/* set CNF bit */
	RTC->CRL |= setBit( 4u );
	/* write one or more RTC register */
	/* RTC prescaler load register setup */
	RTC->PRLH = 0X0000;
	RTC->PRLL = 0x7fff;
	/* set SECIE */
	RTC->CRH |= 0x01;
	/* reset SECF */
	RTC->CRL &= ~0x01;
	/* clear CNF  */
	RTC->CRL &= ~setBit( 4u );
	/* wait  RTOFF*/
	while( ((RTC->CRL >> 5U) & 0x01) != 0x01 );
	

	/* enable interrupts in core  */
	NVIC->ISER[0] |= 0x08;
}

void RTC_IRQHandler(){
	static uint16_t counter;
	if( (RTC->CRL & 0x01) && ( RTC->CRH & 0x01 ) ){
		counter++;
		RTC->CRL &= ~0x01;
	}
	if( counter % 2){
		GPIO_WriteBit( GPIOC, GPIO_Pin_13, Bit_SET);
	}else{
		GPIO_WriteBit( GPIOC, GPIO_Pin_13, Bit_RESET);
	}
}

