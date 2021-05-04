

#include "stm32f10x.h"                  // Device header

/*************************************************************************************************/
void Reserved_IRQHandler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void NMI_Handler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void HardFault_Handler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void SVC_Handler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void PendSV_Handler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void SysTick_Handler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}
/*************************************************************************************************/


void delay(int rep);

int main(void)
{
	RCC->APB2ENR |= 0x10; /// Or  0b10000 --> Anabling Preiph GPIOC
	GPIOC->CRH &= 0xFF0FFFFF;  /// Reset the PORT C PIN 13
	GPIOC->CRH |= 0x00300000;  /// Set Port C PIN 13 as Output 
	GPIOC->ODR  |= 0x2000;     /// Set Port C Pin 13 
	while(1)
	{
		/// Blinking the Port C pin 13 
		GPIOC->ODR  |= 0x2000;
		delay(10);
		GPIOC->ODR  &= ~0x2000;
		delay(10);
		
	}

}


/// Random time delay Function
void delay(int rep)
{
	for(;rep>0;rep--)
	{
	int i;
	for(i=0; i< 100000;i++)
	{}
	}
}


