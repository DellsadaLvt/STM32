#include "stm32f10x.h"                  // Device header



int main ( void ){
	
  

}


void SysTick_Configuration(void)
{ 
  /* Setup SysTick Timer for 1 msec interrupts */
  if (SysTick_Config(SystemCoreClock / 1000)) //1000000:us 1000:ms
  { 
  /* Capture error */
  NVIC_SystemReset();
 }
}