#include "stm32f4xx.h"                  // Device header

void UART_Init( void );
uint8_t UART_Read( void );


int main ( void )
{
	UART_Init();
	
	uint8_t result;
	while(1)
	{
		result = UART_Read();
	}
}


void UART_Init( void )
{
	/* Enable clock */
	RCC->APB1ENR |= 0x20000;						// Enable clk of UART2
	RCC->AHB1ENR |=  	0X01;							// Enable clk of PORTA
	
	/* CONFIG PIN RX PA3 */
	GPIOA->MODER |=0x80;								// Set PA3 is Alternate Mode
	GPIOA->AFR[0] |= 0x7000;						// Set the PA3 in the AF7
	
	
	/* CONFIG UART */
	USART2->BRR |= 0x008B;								// Set Baurate: 115200 with 16MHz
	USART2->CR1 |= 2000;									// Set UE
	USART2->CR1 |= 0x04;									// Set Re
	
}

uint8_t UART_Read( void )
{
	while(!(USART2->SR & 0x20)){}
	
	return(USART2->DR );
}

