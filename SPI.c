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
	//SPI2->CR1 |= (uint32_t)0x01 << 6u;  // enable SPI
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




//void SPI2_Trasmiter( uint16_t temp ){
//	/* Make Busy bit is clear */
//	if( !(SPI2->SR&(0x01<<7u)) || (SPI2->SR&(0x01<<1u))){
//		/* clear PB8 is low */
//		GPIOB->ODR &= ~((uint32_t)0x01 << 8);
//		delay(1);
//		SPI2->DR = temp;
//		delay(1);
//		/* set PB8 high */
//		GPIOB->ODR |= (uint32_t)0x01 << 8;
//	}

//}



void SPI2_Trasmiter( uint16_t temp ){
	SPI2->CR1 |= (uint32_t)0x01 << 6u;  // enable SPI
	/* Make Busy bit is clear */
	while( (SPI2->SR&(0x01<<7u)) ){}
	/* clear PB8 is low */
	GPIOB->ODR &= ~((uint32_t)0x01 << 8);
	/* Check TXE is set */
	while(  !(SPI2->SR&(0x01<<1u)) ){}
	SPI2->DR = temp;
	/* wait TxE is set */
	while(  !(SPI2->SR&(0x01<<1u)) ){}
	/* Make Busy bit is clear */
	while( (SPI2->SR&(0x01<<7u)) ){}
	/* set PB8 high */
	GPIOB->ODR |= (uint32_t)0x01 << 8;
	/* disable SPI */
	SPI2->CR1 &= ~((uint32_t)0x01 << 6u);  
}


void SPI2_Receiver( uint8_t * temp ){
	SPI2->CR1 |= (uint32_t)0x01 << 6u;  // enable SPI
	/* Make Busy bit is clear */
	while( (SPI2->SR&(0x01<<7u)) ){}
	/* clear PB8 is low */
	GPIOB->ODR &= ~((uint32_t)0x01 << 8);
	/* Check RxE is set */
	while(  !(SPI2->SR&0x01) ){}
	*temp = SPI2->DR;
	/* wait RxE is clear */
	while( (SPI2->SR&0x01)  ){}
	/* Make Busy bit is clear */
	while( (SPI2->SR&(0x01<<7u)) ){}
	/* set PB8 high */
	GPIOB->ODR |= (uint32_t)0x01 << 8;
	/* disable SPI */
	SPI2->CR1 &= ~((uint32_t)0x01 << 6u);  
}


/*=========================================================*/
void SPI1_SETUP( void ){
	/* enable clock SPI */
	RCC->APB1ENR |= (uint32_t)0x01 << 13u;
	/* select baud rate */
	SPI1->CR1 |= (uint32_t)0x01 << 5u;
	/* select the CPOL and CPHA bits */
	// CPOL(1) vs CPHA(0): 0
	/* Set the DFF bit to define 16 */
	SPI1->CR1 |= (uint32_t)0x01 << 11u;
	/* Configure the LSBFIRST bit in the SPI_CR1 register */
	//SPI2->CR1 |= (uint32_t)0x01 << 7u;
	/* The MSTR and SPE bits must be set */
	SPI1->CR1 |= (uint32_t)0x01 << 2u;  // master configuration
	SPI1->CR1 |= (uint32_t)0x01 << 6u;  // enable SPI
}




void SPI_DMA_INIT( uint8_t *startAdd, uint8_t *endAdd, uint8_t Nof ){
	/* enable clock DMA */
	RCC->AHBENR |= 0x01;
	/* Init address of memory */
	DMA1_Channel3->CMAR= (uint32_t)startAdd;
	/* Init address of peripheral */
	DMA1_Channel3->CPAR= (uint32_t)endAdd;
	/* Total of Data */
	DMA1_Channel3->CNDTR= 1u;
	/* config DMA */
	DMA1_Channel3->CCR |= 0x590;
}


void SPI2_SendData_DMA( void ){
	/* enable DMA */
	DMA1_Channel1->CCR |= 1u;
	
}


