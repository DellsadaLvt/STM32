/***************************************************

APB1: ENABLE UART2
*/

#include "stm32f4xx.h"                  // Device header


void UART_Init( void );
void USART_write( int ch );


int main( void )
{
	UART_Init();
	while(1)
	{	
		USART_write('H');
	}
}


void UART_Init( void )
{
	RCC->APB1ENR |= 0x20000;					/* ENABLE CLOCK IN UART */
	RCC->AHB1ENR |= 0x01;							/* ENABLE CLOCK IN PORT REGARD WITH PA2 AND UART2 TX*/
	GPIOA->MODER |= 0x20;							/* ENABLE ALTERNATE FUNCTION IN GPIOA0 */
	GPIOA->AFR[0] = 0x0700;  					/* set the value in AFRL reg( PA0 ), in the AFRL2 because
																			we work uart in PA2 and AF7*/ 
	USART2->BRR = 0x0683;							/* UART2 with 9600bps and freq = 16MHz*/
	USART2->CR1 = 0x08;								/* enable Tx */
	USART2->CR1 |= 0x2000;						/* enable UART */
}

void USART_write( int ch )
{
	/* wait while Tx buffer is empty*/
	while( !(USART2->SR & 0x80)){}
	USART2->DR = ( ch & 0xFF);
}
