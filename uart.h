	/**************************** 
	* PA9:  Tx pin
	* PA10: Rx pin
	* select baud rate: 9600bps.
	* caculate UART_DIV= 468.75
	* div_faraction: 0.75*16= 12 => C
	* div_mantissa: 468 -> 1D4
	****************************/

#include "stm32f10x.h"                  // Device header


#define enaUart1 						((uint32_t)0x4000)
#define setUE		 						((uint32_t)0x2000)
#define setTE    						((uint32_t)0x08)
#define setTC    						((uint32_t)0x40)
#define setRXNEIE   				((uint32_t)0x20)
#define setRE      					((uint32_t)0x04)
#define enaUSART_INT_NIVC   ((uint32_t)0x20)


typedef enum{
	wl8Bits = 0,
	wl9Bits = 1
}wordLength;


typedef enum{
	oneSTB			= 0, // 1 Stop bit
	haftSTB   	= 1, //: 0.5 Stop bit
	twoSTB 			= 2, //: 2 Stop bits
	haftOneSTB 	= 3, // : 1.5 Stop bit
									//The 0.5 Stop bit and 1.5 Stop bit are not available for UART4 & UART5
}numberStopBit;


void UART1_trasmit( char *data );
void USART1_receive( void );

