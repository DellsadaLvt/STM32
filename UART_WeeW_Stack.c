#include"UART_WeeW_Stack.h"

//char chat = 'C';
uint8_t chat = 'C';


void UART_SETUP(void)
{
// Delays function	
//systick_init();

	//-----------Init UART ------------///
	// Enable the Alternate Function for PINs
		RCC->APB2ENR |= 1;
	// Enable UART2
		RCC->APB1ENR |=0x20000;
	// Enable the related PINs
	init_GP(PA,2,OUT50,O_AF_PP);
	init_GP(PA,3,IN,I_PP);
	// Setup the baude rate for 9600 bps
	USART2->BRR = 0xEA6;//0x4E2;//0xEA6; 
	// Enable Uart Transmit
	USART2->CR1 |= 8;
	// Enable Uart Recive
	USART2->CR1 |= 4;
	// Enable Uart
	USART2->CR1 |= 0x2000;


}

void transmit_data( void)
	{

		// Recieve Char
		/*while((USART2->SR & 0x20) == 0x00)
		{};
		chat = USART2->DR;*/
		// Transmit Char
		//DelayMs(100);
		
		while((USART2->SR & (1<<6)) == 0x80)
		{};
		USART2->DR = chat;

	}


