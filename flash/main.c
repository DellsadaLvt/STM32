#include "flash.h"

int main( void ){
	//uint8_t arr[] = {6,7,8,9,10,6,11,12,13,14,15,16,17,18};
	uint8_t readFlashArr[20];
	check test;
	
	
	//earseFlash(0x08001000);
	//test = writeFlash( 0x08001000, arr, 6);
	readFlash(0x08001000, readFlashArr, 6);
	
	
	//check readFlash( uint32_t u32AddressStart, uint8_t *u8Buffer, uint32_t u32Length);
	return 0;
}

