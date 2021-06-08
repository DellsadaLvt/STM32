#include "uart.h"
#include "gpio.h"

void UART1_trasmit( char *data ){
	/* enable clock UART1, port A, AFIO */
	RCC->APB2ENR |= (enaUart1 | enaPortA | enaAFIO );
	/* setup alternate output pp gpio pinA9 as Tx */
	GPIOA->CRH &= ~((uint32_t)0x0f<<4);
	GPIOA->CRH |= ( (outMaxSpeed50MHz |  (ppAfio << 2)  )<< 4); // 1011 0000
	/* setup alternate output pp gpio pinA9 as Rx */
	
	/* sequence config uart1 page 793 */
	/* set UE bit */
	USART1->CR1 |= setUE;
	/* setup word length 8 bit */
	USART1->CR1 |= ((uint16_t)wl8Bits<<12);
	/* setup stopbit length */
	USART1->CR2 |= oneSTB<< 12;
	/* DMA */
	//xxxxxxxxxx
	/* select baud rate */
	USART1->BRR = 0x1D4C;
	/* set TE: transmit enable */
	USART1->CR1 |= setTE;
	/* wait Transmit data register empty */
	while(!((USART1->SR>>7)&(uint32_t)0x01));
	/*write data */
	USART1->DR = *data;
	/* wait transmit complete */
	while(!((USART1->SR>>6)&0x01));
}

void USART1_receive( void ){
	/* enable clock UART1, port A, AFIO */
	RCC->APB2ENR |= (enaUart1 | enaPortA | enaAFIO );
	/* setup alternate output pp gpio pinA9 as Tx */
	GPIOA->CRH &= ~((uint32_t)0x0f<<8);
	GPIOA->CRH |= ( (input	 |  (floatInput<< 2)  )<< 8); // 0100 
	/* setup alternate output pp gpio pinA9 as Rx */
	
	/* enable usart by set UE bit */
	USART1->CR1 |= setUE;
	/* setup word length 8 bit */
	USART1->CR1 |= ((uint16_t)wl8Bits<<12);
	/* setup stopbit length */
	USART1->CR2 |= oneSTB<< 12;
	/* DMA */
	/* xxxxxxxxxx */
	
	/* RE: Receiver enable */
	USART1->CR1 |= setRE;
	/* select baud rate */
	USART1->BRR = 0x1D4C;
	/* RXNE :  1: Received data is ready to be read */
	/* An interrupt is generated if the RXNEIE bit is set */
	USART1->CR1 |= setRXNEIE;
	
	/* set NVIC */
	NVIC->ISER[1] =  enaUSART_INT_NIVC;
}


