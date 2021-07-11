/*======================== includes ==========================*/
#include "SPI.h"
#include "Timer.h"
#include "GPIO.h"
#include "Matrix.h"


/*======================== values ==========================*/

uint8_t value= 16u;
/*======================== declaration subroutine function ==========================*/

										
/*======================== main func ==========================*/
int main ( void ){
	GPIO_SPI2_INIT();
	SPI1_SETUP();
	SPI_DMA_INIT( &value, (uint8_t*)0x4000380C,  1u );
	SPI2_SendData_DMA();
	while(1){
		
	}
}


/*======================== subroutine function ==========================*/

