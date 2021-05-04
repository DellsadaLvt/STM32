/*
update 01: 04/05/2021


*/
#include "stm32f10x.h"                  // Device header
#include <stdint.h>
#include<stdio.h>

#define ENA_CLK_USART2	0x20000
#define ENA_CLK_PORTA		0x04
#define ENA_CLK_AFIO 		0x01



void USART_INIT( void );
int8_t USART_Write( uint8_t ch );
uint8_t USART_Read( void );
void Delay( int reg);
void GPIO_Init( void );
void Test_Rx_Led( void );

