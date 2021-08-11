#include "GPIO.h"

void configGPIO( void ){
	/* enable clock port A */
	RCC->APB2ENR|=  0x01 << 2U;
	/* pin PA6 ADC1_IN6 as analog input for ADC1 */
	GPIOA->CRL &= ~( 0x0F << 24u);
	//GPIOA->CRL |= 0x01 << 27;
	/* pin PA0 ADC2_IN0 as analog input for ADC2 */
	GPIOA->CRL &= ~(0x0F);
	//GPIOA->CRL |= 0x01 << 3u;
	/* pin PA1 ADC2_IN1 as analog input for ADC2 */
	GPIOA->CRL &= ~(0x0F << 4u);
	//GPIOA->CRL |= 0x01 << 3u;
}


void GPIOLedC13( void ){
	/* enable clock port C */
	RCC->APB2ENR|= 0x01 << 4U;
	/* config pc13 as output push/pull */
	GPIOC->CRH |= 0x03 << 20u; // set output mode with max speed 50MHz
	GPIOC->CRH &= ~(0x03 << 22u); // set output in push pull mode
	/* turn on led 13 */
	GPIOC->BRR |= 0x01 << 13u;
}


void controlLed( bool x){
	if( x == set ){
		GPIOC->ODR|= 0x01 << 13u;
	}
  else{
		GPIOC->ODR&= ~( 0x01 << 13u);
	}
}

/*=============================== GPIO ADC MODE =================================*/
void GPIO_ADC_DualMode( void ){
	/* Enable clk port A */
	RCC->APB2ENR|= 0x01 << 2u;
	/* set pin PA0, PA1 as analog mode */
	GPIOA->CRL &= ~(0xFF);
}



void GPIO_ADC2_SingleMode( void ){
	/* Enable clk port A */
	RCC->APB2ENR|= 0x01 << 2u;
	/* set pin PA6 as analog mode */
	GPIOA->CRL &= ~(0xFFFFFFFF);
	/* config led pc13 */
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC,  &GPIO_InitStruct);
	GPIO_WriteBit( GPIOC,  GPIO_Pin_13, Bit_SET);
}


/*=============================== GPIO TIMER MODE =================================*/
void GPIO_EXT_CLK_MODE1( void ){
	/* enable clock port A and */
	RCC->APB2ENR |= (0x01 << 2u );
	/* config pin A9 as input push pull */
	GPIOA->CRH &= ~( 0x01 << 6u);
	GPIOA->CRH |= 0x01 << 7u;
	/* set pin a0 as output */
	GPIOA->CRL &= ~(0x0F);
	GPIOA->CRL |= 0x03;
}




void GPIO_EXT_CLK_MODE2( void ){
	/* enable clock port A */
	RCC->APB2ENR |= (0x01 << 2u );
	/* config pin A12 as input push pull */
	GPIOA->CRH &= ~( 0x01 << 18u);
	GPIOA->CRH |= 0x01 << 19u;
	/* set pin a0 as output */
	GPIOA->CRL &= ~(0x0F);
	GPIOA->CRL |= 0x03;
	
}



void GPIO_TIM1_INP_CAPTURE( void ){
	/* enable clock port A */
	RCC->APB2ENR |= (0x01 << 2u );
	/* config pin A8 as input push pull */
	GPIOA->CRH &= ~( 0x01 << 2u);
	GPIOA->CRH |= 0x01 << 3u;
	/* set pin a0 as output */
	GPIOA->CRL &= ~(0x0F);
	GPIOA->CRL |= 0x03;
}


void GPIO_PWM_INPUT( void ){
	/* enable clock port A */
	RCC->APB2ENR |= (0x01 << 2u );
	/* config pin A8 as input push pull */
	GPIOA->CRH &= ~( 0x01 << 2u);
	GPIOA->CRH |= 0x01 << 3u;
	/* set pin a0 as output */
	//GPIOA->CRL &= ~(0x0F);
	//GPIOA->CRL |= 0x03;
}


void GPIO_PWM_A9( void ){
	/* enable clock port A, port B and AFIO*/
	RCC->APB2ENR |= (0x01 << 2u | 0x01<< 3u | 0x01);
	/* config pin A9 as OUTPUT push pull */
	GPIOA->CRH &= ~( 0x01 << 6u);
	GPIOA->CRH |= 0x0B << 4u;
	/* config pin B14 as OUTPUT push pull */
	GPIOB->CRH &= ~( 0x01 << 26u);
	GPIOB->CRH |= 0x0B << 24u;
}


void GPIO_EncoderInterface( void ){
	/* enable clock port A and */
	RCC->APB2ENR |= (0x01 << 2u );
	/* config pin A9 as input push pull */
	GPIOA->CRH &= ~( 0x01 << 6u);
	GPIOA->CRH |= 0x01 << 7u;
	/* config pin A8 as input push pull */
	GPIOA->CRH &= ~( 0x01 << 2u);
	GPIOA->CRH |= 0x01 << 3u;
}






