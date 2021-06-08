#include "uart.h"
#include "gpio.h"
#include "sysTick.h"
#include "string.h"

volatile char readUSART[50];

int main( void ){
	//char str[500]={"An Idle character is interpreted as an entire frame of “1”s followed by the start bit of the next frame which contains data (The number of “1” ‘s will include the number of stop bits). A Break character is interpreted on receiving “0”s for a frame period. At the end of the break frame the transmitter inserts either 1 or 2 stop bits (logic “1” bit) to acknowledge the start bit"};
	//sysTickConfig(72000);
	//for(int i=0; i< strlen(str); i++)
	//UART1_trasmit((str+i));
	USART1_receive();
	while(1){
	}
} 

void USART1_IRQHandler( void ){
	static uint8_t pos= 0;
	if( ((USART1->SR>>5)&0x01) && ((USART1->CR1>>5)&0x01) ){
		readUSART[pos] = USART1->DR;
		UART1_trasmit((char *)(readUSART+pos));
		pos++;
		if(pos>=50)
			pos=0;
	}
}

