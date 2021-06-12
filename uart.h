	/**************************** 
	* PA9:  Tx pin
	* PA10: Rx pin
	* select baud rate: 9600bps.
	* caculate UART_DIV= 468.75
	* div_faraction: 0.75*16= 12 => C
	* div_mantissa: 468 -> 1D4
	****************************/

#include "stm32f10x.h"                  // Device header

#ifndef enaUart1
	#define enaUart1 						((uint32_t)0x4000)
#endif

#ifndef setUE
	#define setUE		 						((uint32_t)0x2000)
#endif

#ifndef setTE
	#define setTE    						((uint32_t)0x08)
#endif

#ifndef setTC
#define setTC    							((uint32_t)0x40)
#endif

#ifndef setRXNEIE
	#define setRXNEIE   				((uint32_t)0x20)
#endif

#ifndef setRE
	#define setRE      					((uint32_t)0x04)
#endif

#ifndef enaUSART_INT_NIVC 
	#define enaUSART_INT_NIVC   ((uint32_t)0x20)
#endif

#ifndef setPCE
	#define setPCE							((uint32_t)0x400)
#endif

#ifndef setPEIE
	#define setPEIE							((uint32_t)0x100)
#endif

#ifndef addUSART_DR
	#define addUSART_DR 				((uint32_t)0x40013804)
#endif

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


typedef enum{
	even 	= 0,
	old 
}parityOp;


typedef enum{
	Tx = 0x01,
	Rx,
	TRx
}receiveOrTransmit;


typedef enum{
	deActive = 0,
	active
}isActive;

/**************** NORMAL USART USING INTERRUPTS ******************/
void UART1_trasmit( char *data );
void USART1_receive( void );

/**************** USART USING DMA ******************/
void USART_DMA_CONFIG_RX( void );
void USART_DMA_CONFIG_TX( void );
void DMA_RX(uint32_t *startAdd, uint32_t *endAdd, uint16_t u16NumberOfData);
void DMA_TX_INIT(uint32_t *startAdd, uint32_t *endAdd, uint16_t u16NumberOfData);	
void activeDMA_Channel4( isActive x , uint16_t u16reloadNumberOfData );
void activeDMA_Channel5( uint16_t u16NumberOfData );
void USART_DMA_CONFIG(  receiveOrTransmit mode  );
void DMA_MEMTOMEM ( uint32_t *startAdd, uint32_t *endAdd, uint16_t u16NumberOfData );
void sample( void );
void sample2( void );


