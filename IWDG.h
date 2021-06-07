#include "stm32f10x.h"                  // Device header

typedef enum{
	div4 = 	0,
	div8 = 	1, 
	div16= 	2, 
	div32= 	3,
	div64= 	4,
	div128= 5,
	div256= 6
}prescaler;

typedef enum{
	noError = 0,
	error
}stateIWDG;

stateIWDG IWDG_config( prescaler div , uint32_t timeOut );
