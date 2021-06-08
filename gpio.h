#include "stm32f10x.h"                  // Device header

#define enaPortA ((uint32_t)0x04)
#define enaAFIO  ((uint32_t)0x01)

typedef enum{
	input								= 0x00,
	outMaxSpeed10MHz 		= 0x01,
	outMaxSpeed2MHz  		= 0x02,
	outMaxSpeed50MHz  	= 0x03
}mode_option;

typedef enum{
	analog 			=  0x00,			//: Analog mode
	floatInput 	= 0x01,				//: Floating input (reset state)
	ppInput 		= 0x02				// Input with pull-up / pull-down
}CNF_input;

typedef enum{
	ppOut		= 0x00, 	//General purpose output push-pull
	odOut		= 0x01,   //: General purpose output Open-drain
	ppAfio	= 0x02, 	//: Alternate function output Push-pull
	opAfio	= 0x03   //: Alternate function output Open-drain
}CNF_output;


typedef struct{
	mode_option  mode;
	CNF_input    inp;
	CNF_output   onp;
}gpioInit;




void gpio_config( void );

