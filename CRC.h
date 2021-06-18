#include "stm32f10x.h"                  // Device header
#include "string.h"


int CRC_init( uint32_t* str, uint8_t u8Count );
int CRC_8bit_software( uint8_t str, uint8_t u8CountByte, uint8_t CRC_POLY );
void CRC_DMA_init( uint32_t *u32StrAdd , uint16_t u16Len);

