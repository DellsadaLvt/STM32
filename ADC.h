/*=======================
* In the blue bill
* Vref: 0 -> 3.3V
* ADC 12 bit: 0 -> 4095
========================*/


#include "stm32f10x.h"                  // Device header



typedef enum{
	DMA 		= 0x01,
	INT 		= 0x02,
	DMA_INT = 0x03
}mode;

void ADC_std_config( void );
void ADC_registerConfig( mode x );



