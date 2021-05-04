/*===========================================================
*														LIBRARIES
============================================================*/
#include<stdio.h>
#include<stdint.h>


/*===========================================================
*														DEFINE
============================================================*/
#define rcc_address 		0x40021000
#define port_c_address	0x40011000

/*===========================================================
*														STRUCTURE
============================================================*/
struct my_rcc_type
{
	uint32_t	CR;
	uint32_t	CFGR;
	uint32_t	CIR;
	uint32_t	APB2RSTR;
	uint32_t	APB1RSTR;
	uint32_t	AHBENR;
	uint32_t	APB2ENR;
	uint32_t	APB1ENR;
	uint32_t	BDCR;
	uint32_t	CSR;
};

struct my_gpio_type
{
	uint32_t	CRL;
	uint32_t	CRH;
	uint32_t	IDR;
	uint32_t	ODR;
	uint32_t	BSRR;
	uint32_t	BRR;
	uint32_t	LCKR;
};

struct my_rcc_type 	*rcc 	= (struct my_rcc_type *)rcc_address ;
struct my_gpio_type *gpio = (struct my_gpio_type *)port_c_address ;

/*===========================================================
*											DECLARE FUNCRION
============================================================*/
void delay( uint16_t rep);
void gpio_config( void );
void blink( void );
/*===========================================================
*														MAIN
============================================================*/
int main( void )
{
	gpio_config();
	
	while(1)
	{
		blink();
	}
	
}

/*===========================================================
*												  SOUROUTINE
============================================================*/
void delay( uint16_t rep)
{
	for(;(rep)>0; rep--)
	{
		for( int i = 0; i<100000; i++);
	}
}

void gpio_config( void )
{
	rcc->APB2ENR |= 0x10;
	gpio->CRH			&= 0;
	gpio->CRH 		|= 0x00300000;
	gpio->ODR 		&= ~(0x2000);
	//gpio->ODR 		|= (0x2000);
}

void blink( void )
{
	gpio->ODR 		&= ~(0x2000);
	delay(100);
	gpio->ODR 		|= (0x2000);
	delay(100);
}

