#include"GPIO.h"


struct Rcc *RCC = (struct Rcc*)RccAddress;
struct Gpio *GPIOC = (struct Gpio*)PortCAddress;
struct Gpio *GPIOA = (struct Gpio*)PortAAddress;


void GpioConfig( void )
{
	RCC->APB2ENR |=  0x10;	// enable clk port C
	RCC->APB2ENR |=  0x04;	// enable port A
	
	// Config port A0 is input 
	/* If the value of ODR0 is 0 -> pull down
	   if the value of ODR1 is 1 -> pull up
	*/
	GPIOA->CRL &= 0xFFFFFFF0;
	GPIOA->CRL |= 0x08;	
	GPIOA->ODR |= 0x01;  // set input is pull up
	
	// config pc13 is output push pull
	GPIOC->CRH  |= 0x300000;
	GPIOC->CRH  &= 0xFF3FFFFF; 
}

void buttonAndLed( void )
{
	if(GPIOA->IDR<<31)
		GPIOC->ODR &= ~(0x2000);
	else
		GPIOC->ODR |= 0x2000;
}


	
	

	
	











