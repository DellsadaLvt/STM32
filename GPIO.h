#include "stm32f10x.h"                  // Device header


typedef enum{
	reset= 0,
	set= 1
}bool;

void configGPIO( void );
void controlLed( bool x);
void GPIOLedC13( void );
void GPIO_ADC_DualMode( void );
//void GPIO_ADC_DualMode( void );
void GPIO_ADC1_TIMER_TRIGGER( void );
void GPIO_ADC2_SingleMode( void );
	

void GPIO_EXT_CLK_MODE1( void );
void GPIO_EXT_CLK_MODE2( void );
void GPIO_TIM1_INP_CAPTURE( void );
void GPIO_PWM_INPUT( void );
void GPIO_PWM_A9( void );
void GPIO_EncoderInterface( void );



















