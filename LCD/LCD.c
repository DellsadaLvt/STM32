

#include "LCD.h"



// define time delay
uint8_t t= 5;



// delay function
void Delay( uint16_t reg){
	int i;
	for(; reg>0; reg--){
		for(i=0; i< 0xfff; i++){}
	}
}


// config port 
void Port_init( void ){
	// Initial 
	GPIO_InitTypeDef GPIO_InitStruct;
	// Clock enable port B, C
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);
	
	// Config PORT B use for Lcd
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15 | GPIO_Pin_5 | GPIO_Pin_6 | 
															GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 /* Data*/
																| GPIO_Pin_12 | GPIO_Pin_13 /* RS and Ena */;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	// Config PORTC use to blink
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
}


// bink pc13
void Blink( void ){
	GPIO_WriteBit( GPIOC, GPIO_Pin_13, 1);
	Delay(1000);
	GPIO_WriteBit( GPIOC, GPIO_Pin_13, 0);
	Delay(1000);
}


// Lcd data 
void Lcd_data( uint8_t x){
	GPIO_WriteBit( GPIOB, GPIO_Pin_14, showBit( &x, 0 ));		// D0
	GPIO_WriteBit( GPIOB, GPIO_Pin_15, showBit( &x, 1 ));
	GPIO_WriteBit( GPIOB, GPIO_Pin_5, showBit( &x, 2 ));
	GPIO_WriteBit( GPIOB, GPIO_Pin_6, showBit( &x, 3 ));
	GPIO_WriteBit( GPIOB, GPIO_Pin_7, showBit( &x, 4 ));
	GPIO_WriteBit( GPIOB, GPIO_Pin_8, showBit( &x, 5 ));
	GPIO_WriteBit( GPIOB, GPIO_Pin_9, showBit( &x, 6 ));
	GPIO_WriteBit( GPIOB, GPIO_Pin_10, showBit( &x, 7 ));	// D10
}

// export one bit of a byte
uint8_t showBit( uint8_t *x, uint8_t p){

	uint8_t b[8];
	for(int8_t i=0 ; i< 8; i++){
	 	b[i]= (*x >> i) & (uint8_t)0x01; 
	}
	return b[p];
}


// transmit command to lcd
void lcd_command( char x){
	//R/w --> 0 (mass)
	// RS: 0 --> Write command
	GPIO_WriteBit(GPIOB, RS, 0); // config in command mode
	Delay(t);
	
	// Send data
	GPIO_WriteBit(GPIOB, E, 1); // begin transmit
	Delay(t);
	Lcd_data(x);   							//  transmit data
	Delay(t);
	GPIO_WriteBit(GPIOB, E, 0); // close transmit
	Delay(t);
}


// transmit data to lcd
void lcd_data( char x){
	//R/w --> 0 (mass)
	// RS: 1 --> Write data
	GPIO_WriteBit(GPIOB, RS, 1);  // config to data mode
	Delay(t);
	// Send data
	GPIO_WriteBit(GPIOB, E, 1);  // begin transmit 
	Delay(t);
	
	Lcd_data(x);									// transmit data
	Delay(t);
	
	GPIO_WriteBit(GPIOB, E, 0);		// close transmit
	Delay(t);
}


// init setup lcd
void Lcd_init(){
	// reset all pin
	GPIO_WriteBit(GPIOB, E, 0);
	GPIO_WriteBit(GPIOB, RS, 0);
	Lcd_data(0);
	Delay(50);
	// function set
	lcd_command(0x38);
	Delay(50);
	// display on/off control
	lcd_command(0x0c);
	Delay(50);
	// entry mode
	lcd_command(0x06);
	Delay(50);
	
	//clear display
	lcd_command(0x01);
	Delay(50);
}

// test function
void Hien_thi( void ){

		static int i = 0;;
		char str[17] ={"Le Van Tho STM32"};
		char header[] = {"Hello"};
		
		i++;
		if( i>=10000){
			i= 0;
		}
		
		lcd_command(0x01);
		
		lcd_command(0x80);
		for( int i = 0; i< 5; i++)
			lcd_data(header[i]);
		
		lcd_command(0x88);
		lcd_data(i/1000 + 0x30);
		lcd_data(i%1000/100 + 0x30);
		lcd_data(i%100/10 + 0x30);
		lcd_data(i%10 + 0x30);
		
		
		lcd_command(0xc0);
		for( int i = 0; i< 16; i++)
			lcd_data(str[i]);
		
		Delay(1000);
}

// test func 2
void Hien_thi_1( void ){
	lcd_command(0x01);
		for( char i=2; i< 14; i++){
			Heart( 0x80 + i);
			Heart( 0xc0 +16 - i);
		}
		Delay(300);
		lcd_command(0x01);
		Hien_thi();
		Delay(1000);
}


// display heart sybol
void Heart( char add ){
	char str[]= { 
		0x00, /*line 8*/
		0x0a, 
		0x1f,
		0x1f,
		0x0e,
		0x04,
		0x00,
		0x00 /* line 1*/
	};
	
	// write the patern form to CGRAM
	for(int i=0; i<8; i++){
		lcd_command(0x40 + i);
		lcd_data(str[i]);
	}
	
	// display the partern
	lcd_command( add );
	lcd_data(0x00);
}

