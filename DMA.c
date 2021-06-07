#include "DMA.h"

void DMA_ADC( uint32_t *startAdd, uint32_t *endAdd, uint16_t u16NumberOfData){
	/* enable DMA1 clock */
	RCC->AHBENR |= 0x01;
	/* Set the peripheral register address in the DMA_CPARx register. The data will be
	moved from/ to this address to/ from the memory after the peripheral event */
	DMA1_Channel1->CPAR = (uint32_t)startAdd;
	/* Set the memory address in the DMA_CMARx register. The data will be written to or
	read from this memory after the peripheral event */
	DMA1_Channel1->CMAR = (uint32_t)endAdd;
	/* Configure the total number of data to be transferred in the DMA_CNDTRx register.
	After each peripheral event, this value will be decremented */
	DMA1_Channel1->CNDTR = u16NumberOfData;
	/* Configure the channel priority using the PL[1:0] bits in the DMA_CCRx register */
	DMA1_Channel1->CCR |= (0x01<<13);   // set bit 12, 13: 01-> medium priority
	/* Configure data transfer direction, circular mode, peripheral & memory incremented
	mode, peripheral & memory data size, and interrupt after half and/or full transfer in the
	DMA_CCRx register */
	DMA1_Channel1->CCR &= ~(0x01<<4); // set direction read from pripheral
	DMA1_Channel1->CCR |= (0x01<<5);  // set circular mode
	DMA1_Channel1->CCR &= ~(0X01<<6); // disable pripheral increment mode
	DMA1_Channel1->CCR |= (0x01<<7);  // enable memory increment mode
	DMA1_Channel1->CCR |= (0x01<<8);  // set pripheral at 16bit
	DMA1_Channel1->CCR &= ~(0x01<<9);
	DMA1_Channel1->CCR |= (0x01<<10);  // set memory at 16bit
	DMA1_Channel1->CCR &= ~(0x01<<11);
	/* Activate the channel by setting the ENABLE bit in the DMA_CCRx register */
	DMA1_Channel1->CCR |= 0x01;
	
}


