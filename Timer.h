/*
* update even occur when the counter is overflow or UG is set.
*/

#include "stm32f10x.h"                  // Device header

typedef enum{
	enable = 0,
	disable
}state;


void Timer2_init( void );
void enableTimer2( state stateTimer2, state stateClockTimer2 );
void delay( uint16_t grep );
