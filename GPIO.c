#include "GPIO.h"

void GPIO_SPI2_INIT( void ){
	/* enble clock port B */
	RCC->APB2ENR |= (uint32_t)0x01 << 3u;
	/* enable AFIO clock */
	RCC->APB2ENR |= (uint32_t)0x01;
	/* config PB13 as SCK: output Alternate push pull */
	GPIOB->CRH &= ~((uint32_t)0x0F<<20U);
	GPIOB->CRH |= (uint32_t)0x03 << 20U;
	GPIOB->CRH |= (uint32_t)0x02 << 22U;
	/* config PB15( MOSI ) as ouput alternate push pull */
	GPIOB->CRH &= ~((uint32_t)0x0F<<28U);
	GPIOB->CRH |= (uint32_t)0x03 << 28U;
	GPIOB->CRH |= (uint32_t)0x02 << 30U;
	/* config Pb8 as CS: ouput push pull */
	GPIOB->CRH &= ~((uint32_t)0x0F);
	GPIOB->CRH |= (uint32_t)0x03 ;
	//GPIOB->CRH |= 0x00;
	/* set pin PB8 is high */
	GPIOB->ODR |= (uint32_t)0x01 << 8u;
}

void setupPC13( void ){
	/* enable clock port C */
	RCC->APB2ENR |= (uint32_t)0x01 <<4u;
	/* config mode in pc13 */
	GPIOC->CRH &= ~((uint32_t)0x0F<< 20u);
	GPIOC->CRH |= (uint32_t)0x03 << 20u;
	/* turn on led  */
	GPIOC->ODR |= ((uint32_t)0x01 << 13u);
}


