#include "stm32f10x.h"                  // Device header

void PWM_timer2_singleChannel_config( uint8_t width );
void PWM_timer2_multiChannel_config( uint8_t width );
void  GPIO_PWM_TIM2_channel0( void );
void  GPIO_PWM_TIM2_4channel( void );
void PWM_TIM2_4channel_stdlib( uint8_t pwm1, uint8_t pwm2, uint8_t pwm3, uint8_t pwm4 );


