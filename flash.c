#include "flash.h"


void earseFlash( uint32_t u32address ){
	/* check BSY bit */
	while( FLASH->SR & 0x01u);
	/* check unclock sequence in LOCK bit */
	if( FLASH->CR & 0x80u ){
		/* perform unclock sequence */
		FLASH->KEYR = 0x45670123;
		FLASH->KEYR = 0xCDEF89AB;
	}
	/* set PER bit  */
	FLASH->CR |= 0x02u;
	/* write address of the page want to earse */
	FLASH->AR = u32address;
	/* set STRT bit */
	FLASH->CR |= 0x40;
	/* wait busy bit reset */
	while( FLASH->SR & 0x01u);
	/* reset PER bit and  STRT bit */
	FLASH->CR &= ~0x02u;
	FLASH->CR &= ~0x40u;
	
}

check writeFlash( uint32_t u32Address, uint8_t* u8Buffer, uint32_t u32Length){
	uint32_t u32Count;
	if( (u8Buffer == 0x00u) || (u32Length == 0u) || (u32Length%2 != 0u) ){
		return fault;
	}
	/* check BSY bit */
	while( FLASH->SR & 0x01u );
	/* check LOCK bit */
	if( (FLASH->CR >> 7u) & 0x01u ){
		/* perform unclock sequence */
		FLASH->KEYR = 0x45670123;
		FLASH->KEYR = 0xCDEF89AB;
	}
	/* set PG bit*/
	FLASH->CR |= 0x01;
	/* write flash */
	for( u32Count=0u; u32Count< (u32Length/2); u32Count++){
		*(uint16_t*)(u32Address + u32Count*2)= *(uint16_t *)(u8Buffer + u32Count*2);
	}
	/* check BSY bit */
	while( FLASH->SR & 0x01u);
	FLASH->CR &= ~0x01;
	
	return success;
}

check readFlash( uint32_t u32AddressStart, uint8_t *u8Buffer, uint32_t u32Length){
	uint32_t u32Count;
	/* check input */
	if( (u8Buffer == 0u)  || (u32Length== 0u) ){
		return fault;
	}
	/* read flash */
	if( (u32AddressStart%4 == 0u) && ( (uint32_t)u8Buffer%4 == 0u ) && ( u32Length >= 4 ) )
		for( u32Count= 0; u32Count< (u32Length/4+1); u32Count++ ){
			*(uint32_t*)(u8Buffer + u32Count) = *(uint32_t*)( u32AddressStart + u32Count);
	}else{
		for( u32Count= 0; u32Count< u32Length; u32Count++ ){
			*(uint8_t*)(u8Buffer + u32Count) = *(uint8_t*)( u32AddressStart + u32Count);
		}
	}
	
	return success;
}
