#include"UART.h"


void USART_INIT( void )
{
	/* Enable CLK */
	RCC->APB1ENR |= ENA_CLK_USART2;
	RCC->APB2ENR |= ENA_CLK_PORTA;
	RCC->APB2ENR |= ENA_CLK_AFIO;
	
	/* Config port A in alternate function */
	GPIOA->CRL &= (uint32_t)0;
	GPIOA->CRL |= 0x300; 															// output max 50MHz
	GPIOA->CRL |= 0x800; 															// alternate PP
	GPIOA->CRL |= 0x4000;															// Set PA3 as a Input with Float input mode
	//AFIO->EXTICR[0] = 0;
	//AFIO->EVCR |= 0x80;
	
	/* Config int USART2 */  
	USART2->BRR |= 0xEA6;							// 0xEA6			// Baurate: 9600 and the Freq: 12MHz
	USART2->CR1 |= 0x2000;													// Set UE
	USART2->CR1 |= 0x08;														// Set TE
	USART2->CR1 |= 0x04;											// Set RE
	
}


int8_t USART_Write( uint8_t chat)
{
	/* Wait Tx  data register empty */
	while(!(USART2->SR & (uint32_t)0x80)){};
		
		
	/* Write the data */
	//USART2->DR = (	chat + 48);
	USART2->DR = (chat);
		
	//USART_Write('\r');
	//USART_Write('\n');
		return chat;
}

uint8_t USART_Read( void )
{
	/* Wait the Read data register alreadly */
	while(!( USART2->SR & (uint16_t)0x20)){}
	
	/* Read data */
	return( USART2->DR);
}


void Delay( int reg)
{
	int t;
	for( ; reg>0; reg--)
	{
		for( t= 0; t> 100000; t++){}
	}
}


void GPIO_Init( void )
{
	RCC->APB2ENR |= 0x10;											// Enable clock portC
	
	GPIOC->CRH &= 0xFF0FFFFF;									// Reset Pin Pc13
	GPIOC->CRH |= 0x300000;										// Set PC13 as output pp
	
	GPIOC->ODR &= 0;											// Output High in PC13
}

/*=========== INTERFACE WITH STDIO LIBRARY ===========*/
struct __FILE
{
	int handle;
};

FILE __stdin = {0};
FILE __stdout = {1};
FILE __stderr = {2};

int fgetc(FILE *f)
{
	int c;
	c = USART_Read();
	
	if( c== '\r')
	{
		USART_Write(c);
		c = '\n';
	}
	USART_Write(c);
	return c;
}

int fputc( int c, FILE *f)
{
	return( USART_Write(c));
}

void Test_Rx_Led( void )
{
		uint8_t result, chat;
		result	= USART_Read();
	
		if( result >= 0x60)
		{
			GPIOC->ODR &= ~(0x2000);
			USART_Write(chat);
			//Delay(10000);
		}
		
		else
			GPIOC->ODR |= 0x2000;
	}

	
