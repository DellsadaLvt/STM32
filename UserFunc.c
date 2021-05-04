#include"UserFunc.h"

void Func_uart( void )
{
	USART_InitTypeDef* USART_InitStruct;
	USART_ClockInitTypeDef* USART_ClockInitStruct;
	
	
	USART_ClockStructInit(USART_ClockInitStruct);
	USART_ClockInit(USART2, USART_ClockInitStruct);
	
	
	USART_StructInit(USART_InitStruct);
	USART_Init(USART2, USART_InitStruct);
	
	while(1)
	{
	uint16_t Data='H';
	USART_SendData(USART2, Data);
		Delay(1000);
	}
	
	
}

