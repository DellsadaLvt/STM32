#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdint.h>


#ifndef RS
		#define RS 	GPIO_Pin_12
#endif

#ifndef E
		#define E		GPIO_Pin_13
#endif


#ifndef clearDisplay
	#define clearDispay	0x01
	#define functionSet 0x38
#endif


void Port_init( void );
void Lcd_data( uint8_t x);
uint8_t showBit( uint8_t *x, uint8_t p);
void Delay( uint16_t reg);
void Blink( void );
void lcd_data( char x);
void lcd_command( char x);
void Lcd_init( void );
void Hien_thi( void );
void Heart( char add );
void Hien_thi_1( void );


/*

	// Clear display
	// Function set( DL = 1;  N = 1(2lines) ; F = 0 (5x8 dot)  )
	// Display control
	// Entry mode
	// Write data 
	
	*/
	
	


