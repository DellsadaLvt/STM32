#include "SPI.h"
#include "Timer.h"

void SPI2_SETUP( void ){
	/* enable clock SPI */
	RCC->APB1ENR |= (uint32_t)0x01 << 14u;
	/* select baud rate */
	SPI2->CR1 |= (uint32_t)0x01 << 5u;
	/* select the CPOL and CPHA bits */
	// CPOL(1) vs CPHA(0): 0
	/* Set the DFF bit to define 16 */
	SPI2->CR1 |= (uint32_t)0x01 << 11u;
	/* Configure the LSBFIRST bit in the SPI_CR1 register */
	//SPI2->CR1 |= (uint32_t)0x01 << 7u;
	/* The MSTR and SPE bits must be set */
	SPI2->CR1 |= (uint32_t)0x01 << 2u;  // master configuration
	SPI2->CR1 |= (uint32_t)0x01 << 6u;  // enable SPI
}



//void SPI2_Trasmiter( uint8_t add, uint8_t value ){
//	/* clear PB8 is low */
//	GPIOB->ODR &= ~((uint32_t)0x01 << 8);
//	delay(100);
//	SPI2->DR = add;
//	SPI2->DR = value;
//	delay(100);
//	/* set PB8 high */
//	GPIOB->ODR |= (uint32_t)0x01 << 8;
//	delay(100);
//}




void SPI2_Trasmiter( uint16_t temp ){
	if( !((SPI2->SR>>7u)&0x01) || ((SPI2->SR>>1u)&0x01)){
		/* clear PB8 is low */
		GPIOB->ODR &= ~((uint32_t)0x01 << 8);
		delay(1);
		SPI2->DR = temp;
		delay(1);
		/* set PB8 high */
		GPIOB->ODR |= (uint32_t)0x01 << 8;
	}

}
