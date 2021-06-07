#include "IWDG.h"

stateIWDG 	IWDG_config( prescaler div , uint32_t timeOut ){
	/* check parameter */
	if( (div > 7) || ( timeOut==0 ) ){
		return error;
	}
	/* enable access to the IWDG_PR and IWDG_RLR registers */
	IWDG->KR = 0x5555u;
	/* wait watchdog prescale update */
	while( IWDG->SR & 0x01 );
	/* set prescaler 40Khz/256 */
	IWDG->PR = (uint8_t)div;
	/* wait watchdog counter value update */
	while( IWDG->SR & 0x02 );
	/* write counter value */
	IWDG->RLR = (uint16_t)(timeOut/6.4) ; // after 2s to reset
	/* reload value */
	IWDG->KR = 0xAAAA;
	/* start IWDG */
	IWDG->KR = 0xCCCCu;
	
	return noError;
}

