#include "CRC.h"

uint32_t CRC_value, CRC_value1;
volatile uint32_t CRC_value2;
uint8_t str[10]={"hello!"};

int main( void ){
	/* enable clock CRC */
	RCC->AHBENR |= 0x01<<6U;
	/* reset the CRC caculator */
	CRC->CR = 0x01u;
	/* write data */
	for(int i=0; i< 6u; i++)
		CRC->DR = str[i];
	/* get CRC value */
	CRC_value1 = (uint32_t)CRC->DR;
	/* reset CRC clock */
	RCC->AHBENR &= ~(0x01<<6U);
	
	CRC_DMA_init( (uint32_t*)str, 6u );
	while(1){
	}
}

void  DMA1_Channel1_IRQHandler ( void){
	/* get CRC value */
	CRC_value2= CRC->DR;
	/* clear clock */
	RCC->AHBENR &= ~(0x01<<6U);
	/* clear DMA channel 1 */
	DMA1_Channel1->CCR &= ~((uint32_t)0x01);
	/* clear TCIF DMA bit */
	DMA1->IFCR |= (uint32_t)0x01<<1;
}
