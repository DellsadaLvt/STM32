#include "stm32f10x.h"                  // Device header

#define ADC_DR ((uint32_t)0x4001244C)


void DMA_ADC(  uint32_t *startAdd, uint32_t *endAdd, uint16_t size);
