#include "gpio.h"

static func_status_t gpio_ena_clk_portA(void){
	RCC->APB2ENR |= (uint32_t)0x04;
	
	return oke;
}

func_status_t dht11_gpio_init(void){
	/* pa0 in open drain mode */
	gpio_ena_clk_portA();
	GPIOA->CRL &= ~((uint32_t)0x0F);
	GPIOA->CRL |= (uint32_t)0x07;
	
	return oke;
}

func_status_t gpio_led_pc13_init(void){
	RCC->APB2ENR |= (1u << 4u);
	GPIOC->CRH &= ~(uint32_t)(0x0F << 20u);
	GPIOC->CRH |= (uint32_t)(3u << 20u);
	
	GPIOC->BSRR |= 1u << 29u;
	
	return oke;
}

