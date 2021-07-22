//PA5
// AHB1 : Advance High_perform Bus: use 1 cycles clock
// RCC->AHB1ENR
//	GPIOx_MODER
// GPIOx_ODR

/* struct Rcc
{
	int32_t	CR;
	int32_t	CFGR;
	int32_t	CIR;
	int32_t APB2RSTR;
	int32_t APB1RSTR;
	int32_t	AHBENR;
	int32_t	APB2ENR;
	int32_t APB1ENR;
	int32_t BDCR;
	int32_t CSR;
	
};

struct Rcc *RCC = (struct Rcc*)RccAddress;


*/




#include "stm32f4xx.h"  

void DelayMs( int reg );

int main(void)
{
	/* ENABLE RCC PORTA */
	RCC->AHB1ENR |= 0x01; 
	/* CONFIG PA0 AS THE OUTPUT */
	GPIOA->MODER |= 0x400;
	
	while(1)
	{
		GPIOA->ODR |= 0x20;
		DelayMs(1000);
		GPIOA->ODR &= ~(0x20);
	}
}

void DelayMs( int reg )
{
	int t;
	for(; reg>=0; reg--)
	{
		for(t=0; t< 100000; t++)
		{}
	}
}

