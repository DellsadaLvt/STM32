#include "pwm.h"                 

int main(void){
	GPIO_PWM_TIM2_4channel();
	PWM_TIM2_4channel_stdlib(30, 50, 60, 80);
	while(1){
	
	}
}
