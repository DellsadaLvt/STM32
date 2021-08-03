#include "stm32f10x.h"                  // Device header

#define ADC1_DR ((uint32_t)0x4001244C)
#define ADC2_DR ((uint32_t)0x4001284C)

void DMA_ADC(  uint32_t *startAdd, uint32_t *endAdd, uint16_t size);
