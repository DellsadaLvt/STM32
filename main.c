#include "stm32f10x.h"                  // Device header
#include "GPIO.h"
#include "timer.h"
#include "ADC.h"

volatile uint16_t u16AdcValue,u16AdcValue2, u16AdcValue1;
volatile uint32_t u32DualADCValues;
float fTemp, fTemp1, fKalTemp, hr, fVel;
volatile uint16_t count= 0, count2, u16prePulse, u16curPulse;

int main( void ){
	/* init config */
  GPIO_ADC_DualMode();
	ADC_DualMode();
	while(1){
		
	}
}


/*=============================== subrountine func ===================================*/


void TIM1_UP_IRQHandler( void ){
	/* 100ms update onetime */
	if( TIM1->DIER&0x01 && TIM1->SR&0x01 ){
		/* clear flag */
		TIM1->SR&= ~0x01; 
		count++;
	}
}

void TIM1_CC_IRQHandler( void ){
	/* compare and capture channel 2 */
	if( (TIM1->SR>>2u)&0x01  && (TIM1->DIER>>2u)&0x01 ){
		/* clear flag */
		TIM1->SR &= ~( 0x01 << 2u);
		/* get value */
		count2= TIM1->CNT;
	}

}




void TIM2_IRQHandler( void ){
	/* update event */
	if( (TIM2->DIER & 0x01)  && (TIM2->SR& 0x01) ){
		/* clear flag */
		TIM2->SR &= ~(0x01);
		/* count up encoder */
		if( !((TIM1->CR1>>4u)&0x01)){
			u16curPulse= TIM1->CNT;
			if ( u16curPulse >= u16prePulse )
				fVel= (u16curPulse - u16prePulse)*6u*3.14/180u;
			else
				fVel= (60u - u16prePulse) + u16curPulse*6u*3.14/180u;
		}
		u16prePulse= u16curPulse;
	}
}





void ADC1_2_IRQHandler( void ){
	/* Interrupts when convertion complete */
	if( (ADC1->SR >> 1U)&1 && (ADC1->CR1>>5U)&1){
		u32DualADCValues= ADC1->DR;
		fTemp= (uint16_t)u32DualADCValues;
		fTemp1= u32DualADCValues >> 16U;
		//u16AdcValue= ADC1->DR;
		//fTemp= (3.3- (4095 - u16AdcValue)*3.3/4095)*100;
		//fKalTemp= kalman_single( fTemp, 500, 10);
	}
	/* interrupts watchdog */
	if( (ADC1->CR1>>6U)&1 && (ADC1->SR)&1){
		hr= 45;
		/* clear flag */
		ADC1->SR &= ~0x01;
	}
	if( (ADC2->SR >> 1U)&1 && (ADC2->CR1>>5U)&1){
		u16AdcValue2= ADC2->DR;
	}
}

/* temp 1 */
	/* init values */
//	uint16_t task0, task1;
//	task0= task1= count;
//	bool stateLed= reset;
//	while(1){
//		/* way one for one task */
//		if( count - task0 >= 10 && stateLed!= set){
//			task0= count;
//			stateLed= set;
//			controlLed(set);
//		}
//		if( count - task0 >= 20  && stateLed!= reset){
//			task0= count;
//			stateLed= reset;
//			controlLed(reset);
//		}
		
//		/* way two for two task difference */
//		if( count - task0 > 10){
//			task0= count;
//			controlLed( set );
//		}
//		else if( count - task1> 20){
//			task1= count;
//			controlLed( reset );
//		}
//	}


//TIM2_config();
//	GPIO_EXT_CLK_MODE2();
//	EXT_CLK_MODE2();
//	delay(2000);
//	while(1){
//		count++;
//		GPIOA->BSRR|= 0x01;
//		delay(1000);
//		GPIOA->BSRR|= 0x01 << 16;
//		delay(1000);
//	}












