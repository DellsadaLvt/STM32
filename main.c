/*======================== includes ==========================*/
#include "SPI.h"
#include "Timer.h"
#include "GPIO.h"
#include "SysTick.h"

/*======================== values ==========================*/
uint16_t column[8]= {0x0100, 0x0200, 0x0300, 0x0400, 0x0500, 0x0600, 0x0700, 0x0800};
uint8_t text[][8]= { {0xC3,0xC3,0xC3,0xFF,0xFF,0xC3,0xC3,0xC3},
										 {0xFF,0xC0,0xC0,0xFF,0xFF,0xC0,0xFF,0xFF},
										 {0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xFF,0xFF},
										 {0x7E,0x81,0xA5,0x81,0xA5,0x99,0x42,0x3C},
										 {0x18,0x18,0x18,0x18,0xFF,0x7E,0x3C,0x18}};
/*======================== declaration subroutine function ==========================*/
void LedMatrixInit( void );
void demo0( void );
void demo02( void );
										
/*======================== main func ==========================*/
int main ( void ){
	setupPC13();
	delay(1000);
	GPIO_SPI2_INIT();
	SPI2_SETUP();
	LedMatrixInit();
	GPIOC->ODR &= ~((uint32_t)0x01 << 13u);
	while(1){
//		GPIOC->ODR |= (uint32_t)0X01 << 13U;
//		delay(1000);
//		GPIOC->ODR &= ~((uint32_t)0x01 << 13U);
//		delay(1000);
		demo0();
		demo02();
	}
}


/*======================== subroutine function ==========================*/
void LedMatrixInit( void ){
	/**/
	SPI2_Trasmiter( 0x0C01 );
	/**/
	SPI2_Trasmiter( 0x0F00 );
	/**/
	SPI2_Trasmiter( 0x0900 );
	/**/
	SPI2_Trasmiter( 0x0B07 );
	/* intensity */
	SPI2_Trasmiter( 0x0A00 );
	for( int i=0; i< 8; i++){
		SPI2_Trasmiter( column[i]);
	}
	SPI2_Trasmiter( 0x01F0 );
	SPI2_Trasmiter( 0x080F );
	delay(500);
	SPI2_Trasmiter( 0x0100 );
	SPI2_Trasmiter( 0x0800);
}

void demo0( void ){
	for(uint8_t i=0; i< 255; i++){
		for( uint8_t j=0; j< 8; j++){
			SPI2_Trasmiter( column[j] + i);
			delay(50);
		}
		if( i%30 == 0){
			for(uint8_t k1=0; k1< 10; k1++){
				for( uint8_t k=0; k< 8; k++){
					SPI2_Trasmiter( column[k]+ 0xFF);
					delay(30);
				}
				for( uint8_t k=0; k< 8; k++){
					SPI2_Trasmiter( column[k]);
					delay(30);
				}
			}
		}
		//delay(500);
	}
}

void demo02( void ){
	for( int i=0; i<5; i++){
		for(int j =0; j< 8; j++){
			SPI2_Trasmiter( column[j] | text[i][j]);
		}
		delay(800);
	}
}



