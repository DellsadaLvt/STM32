#include "header.h"

uint8_t ma7Doan[10]= {0x3F, 0x06, 0x5B, 0x4F}; // 0, 1, 2, 3
uint16_t pin[] = {((uint16_t)0x1000), ((uint16_t)0x2000), ((uint16_t)0x4000), ((uint16_t)0x8000), /*PORTB 12->15*/
									((uint16_t)0x0100), ((uint16_t)0x0200) , ((uint16_t)0x0400) , ((uint16_t)0x0800)/* PORTA 8->11*/};
extern uint16_t __systemTickTimmingDelay;


void Config( void ){
	// Enable clock
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	
	// Setup port C
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( GPIOC, &GPIO_InitStruct);
	
	// Setup port B
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( GPIOB, &GPIO_InitStruct);
	
	// Setup port A
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( GPIOA, &GPIO_InitStruct);
}

void SetAll ( void ){
	GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	GPIO_SetBits(GPIOA, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11  );
}

void ResetAll ( void ){
	GPIO_ResetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	GPIO_ResetBits(GPIOA, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11  );
}


void HienThi( numb so){
	//reset all
	ResetAll();
	// hien thi a,b,c,d segment
	for(int i=0; i< 4; i++ ){
		GPIO_WriteBit( GPIOB, pin[i], ((ma7Doan[so]>>i) & (uint8_t)0x01) );
	}
	// hien thi e, f, g, dp segment
	for(int i=4; i<8; i++){
		GPIO_WriteBit( GPIOA, pin[i], ((ma7Doan[so]>>i) & (uint8_t)0x01) );
	}
	/*GPIO_WriteBit( GPIOA, pin[4], ((ma7Doan[so]>>4) & (uint8_t)0x01) );
	GPIO_WriteBit( GPIOA, pin[5], ((ma7Doan[so]>>5) & (uint8_t)0x01) );
	GPIO_WriteBit( GPIOA, pin[7], ((ma7Doan[so]>>6) & (uint8_t)0x01) );
	GPIO_WriteBit( GPIOA, pin[7], ((ma7Doan[so]>>7) & (uint8_t)0x01) );*/
}

void Delay( uint16_t reg ){
	int i;
	for(; reg>0; reg--){
		for(i=0; i< 0xFFF; i++){}
	}
}

void test_0( void )
{
	HienThi( so0 );
	Delay(1000);
	HienThi( so1 );
	Delay(1000);
	HienThi( so2);
	Delay(1000);
	HienThi( so3 );
	Delay(1000);
}

void BlinkLed13( void ){
	GPIO_SetBits( GPIOC, GPIO_Pin_13);
	Delay(1000);
	GPIO_ResetBits( GPIOC, GPIO_Pin_13);
	Delay(1000);
}

