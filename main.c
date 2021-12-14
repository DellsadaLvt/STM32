#include "stm32f10x.h"                  // Device header
#include "user_define.h"
#include "gpio.h"
#include "timer.h"
#include "dht11.h"

float humid, temperature;

int main(void){
	dht11_gpio_init();
	TIM2_init();
	TIM2_start();
	while(1){
		dht11(&humid, &temperature, 90u);
		for(uint8_t i=0u; i< 100u; i+=1u){
			delay(50000u);
		}
	}
}















