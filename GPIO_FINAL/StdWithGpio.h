#include "stm32f10x.h"

void GpioConfig_( void ); // this function setup the pa0 is input pull up 
														// and the pc13 is the output push pull

void GpioControl( void );// this function control pc13 when the signal active in pa0
