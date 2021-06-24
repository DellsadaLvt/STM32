/*---------------------- HEADER ---------------------*/
#include "stm32f10x.h"                  // Device header
#include "exti.h"
#include "SysTick.h"
#include "gpio.h"

/*---------------------- VALUE ---------------------*/
volatile float time;


/*---------------------- DECLARE FUNCTION ---------------------*/
void Delay( int16_t grep );
void delay( uint16_t grep );
void multiMode( void );

/*---------------------- MAIN FUNCTION ---------------------*/
int main( void ){
	/* initial config */
	GpioConfig();
	EXT_Init();
	while(1){
		multiMode();
	}
}



/*---------------------- SUBROUTINE ---------------------*/

void SysTick_Handler( void ){
	/* check interrupts and interrupts flag */
	if( ((SysTick->CTRL>>16u)&0x01u) && (SysTick->CTRL&0x01) ){
		time++;
		if(time >10000) 
			time= 10000;
	}
}



void EXTI0_IRQHandler(void){
	if( (EXTI->PR&0x01) && (EXTI->IMR&0x01) ){
		/* checking press button */
		if( !(GPIOB->IDR&0x01) ){
			for( int i=0; i< 100000; i++);
			if( !(GPIOB->IDR&0x01) ){
				SysTickInit( &time );
			}
		}
		/* checking press button */
		if( GPIOB->IDR&0x01 ){
			for( int i=0; i< 100000; i++);
			if( GPIOB->IDR&0x01 ){
				EndSysTick( &time );
			}
		}
		/* clear Pending register */ 
		EXTI->PR= 0x01;
	}
}


void delay( uint16_t grep ){
	while(grep--){
		for( int i=0; i< 100000; i++ );
	}
}


void multiMode( void ){
	if(time == 0){}
	/* mode 0 */
	else if( time < 1000u){
		GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
		delay(5u);
		GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
		delay(5u);
	}
	/* mode 1 */
	else if( time < 2000u){
		GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
		delay(15u);
		GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
		delay(15u);
	}
	/* mode 2 */ 
	else{
		GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
		delay(25u);
		GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
		delay(25u);
	}
}




