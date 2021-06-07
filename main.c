#include "DMA.h"
#include "ADC.h"

volatile uint16_t u16ReadADC[8u];

int main( void ){
	//DMA_ADC( (uint32_t *)ADC_DR , (uint32_t *)u16ReadADC , 1u);
	ADC_registerConfig( INT );
	while(1){
	}
}


void ADC1_2_IRQHandler( void ){
	if( ((ADC1->CR1>>5)&0x01) && ((ADC1->SR>>1)&0x01) ){
		u16ReadADC[2]= ADC1->DR;
	}
}

