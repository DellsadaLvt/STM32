#include "timer.h"

func_status_t TIM2_init(void){
	/* ENABLE TIMER2 CLOCK */
	RCC->APB1ENR |= 0x01;
	/* TIMx prescaler (TIMx_PSC) */
	TIM2->PSC = 72u - 1u; // 1us -> 1 tick
	/* TIMx auto-reload register (TIMx_ARR) */
	TIM2->ARR = 0xFFFF - 1u; 
	/* reset counter */
	TIM2->CNT = 0;
	/* SETUP COUNTER UP */
	TIM2->CR1 &= ~(0x01<< 4U);
	/* Re-initialize the counter and generates an update of the registers */
	TIM2->EGR |= 0x01;
	
	return oke;
}

func_status_t TIM2_start(void){
	TIM2->CNT = 0u;
	/* TIMx control register 1 (TIMx_CR1): ENABLE COUNTER */
	TIM2->CR1 |= 0x01;
	
	return oke;
}

func_status_t TIM2_stop(void){
	/* TIMx control register 1 (TIMx_CR1): ENABLE COUNTER */
	TIM2->CR1 &= ~(uint32_t)0x01;
	
	return oke;
}

func_status_t delay(uint16_t u16_tick){
	uint16_t u16_tick_current = get_tick();
	while( u16_tick > (uint16_t)(get_tick() - u16_tick_current) );
	
	return oke;
}

uint16_t get_tick(void){
	uint16_t u16_tick = (uint16_t)TIM2->CNT;
	
	return u16_tick;
}








