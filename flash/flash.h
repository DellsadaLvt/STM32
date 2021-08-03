#include "stm32f10x.h"                  // Device header

typedef enum{
	success = 0,
	fault,
}check;


void earseFlash( uint32_t u32address );
check writeFlash( uint32_t u32Address, uint8_t* u8Buffer, uint32_t u32Length);
check readFlash( uint32_t u32AddressStart, uint8_t *u8Buffer, uint32_t u32Length);

