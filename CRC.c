#include "CRC.h"

int CRC_init( uint32_t* str, uint8_t u8Count ){
	/* init return value */
	uint32_t CRC_value;
	/* enable clock CRC */
	RCC->AHBENR |= 0x01<<6U;
	/* reset the CRC caculator */
	CRC->CR = 0x01u;
	/* write data */
	for( uint8_t i=0U; i< u8Count; i++)
		CRC->DR = (uint32_t)*((uint8_t*)str + i);
	/* get CRC value */
	CRC_value = (uint32_t)CRC->DR;
	/* reset CRC clock */
	RCC->AHBENR &= ~(0x01<<6U);
	/* return value */
	return CRC_value;
}


int CRC_8bit_software( uint8_t str, uint8_t u8CountByte, uint8_t CRC_POLY ){
	/* init value */
	uint8_t CRC_init;
	static uint8_t CRC_value;
	/* initial CRC */
	CRC_init = 0xff;
	/* alogithm CRC */
	CRC_value = CRC_init^(str);
	for(uint8_t i=0 ; i< (u8CountByte*8); i++){
		if( (CRC_value>>7U)&0x01 ){
			CRC_value = (CRC_value<<1)^CRC_POLY;
		}else{
			CRC_value = CRC_value<<1;
		}
	}
	return CRC_value;
}



void CRC_DMA_init( uint32_t *u32StrAdd , uint16_t u16Len){
	/* enable DMA clock */
	RCC->AHBENR |= 0x01u;
	/* enable clock CRC */
	RCC->AHBENR |= 0x01<<6U;
	/* Configure the DMA channel */
	/* Peripheral address is flash base pointer */
	DMA1_Channel1->CPAR = (uint32_t)u32StrAdd;
	/* memory address is the CRC data register */
	DMA1_Channel1->CMAR = 0x40023000u; //0x4002 3000
	/* config length of data */
	DMA1_Channel1->CNDTR |= u16Len;
	/* config control DMA register */
	DMA1_Channel1->CCR |= (uint32_t)0x01<<14u;  // enable Memory to memory mode
	DMA1_Channel1->CCR |= (uint32_t)0x01<<13u;  // choose priority is high
																							// MSIZE and PSIZE : 00 -> 8bits
																							// disable memory increment mode: 0
	DMA1_Channel1->CCR |= (uint32_t)0x01<<6u;  	// enable peripheral incrememt mode
																							// disable circular mode
																							// read from periphal
	//DMA1_Channel1->CCR |= (uint32_t)0x10;				// enable DMA channel
	
	
	
	/* config CRC  */
	/* init return value */
	//uint32_t CRC_value;
	/* enable clock CRC */
	RCC->AHBENR |= 0x01<<6U;
	/* reset the CRC caculator */
	CRC->CR = 0x01u;
	/* write data */
	/* get CRC value */
	//CRC_value = (uint32_t)CRC->DR;
	/* reset CRC clock */
	//RCC->AHBENR &= ~(0x01<<6U);
	
	/* Enable the DMA transfer complete interrupt */
	DMA1_Channel1->CCR |= (uint32_t)0x01<<1u;
	/* Configure the DMA NVIC IRQ */
	NVIC->ISER[0] |= (uint32_t)0x01<<11u;
	/* enable DMA channel */
	DMA1_Channel1->CCR |= (uint32_t)0x01;
}


