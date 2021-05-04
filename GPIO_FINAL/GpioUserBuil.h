#include<stdio.h>
#include<stdint.h>
#include<time.h>
#include<stdbool.h>
/*------------------------------- MANUAL DEFINE --------------------------------*/
#define RccAddress			0x40021000
#define PortC_Address 	0x40011000
#define PortA_Address		0x40010800

//bool adf = 0;

struct Rcc
{
	int32_t	CR;
	int32_t	CFGR;
	int32_t	CIR;
	int32_t APB2RSTR;
	int32_t APB1RSTR;
	int32_t	AHBENR;
	int32_t	APB2ENR;
	int32_t APB1ENR;
	int32_t BDCR;
	int32_t CSR;
	
};




struct Gpio
{
	int32_t	CRL;
	int32_t	CRH;
	int32_t	IDR;
	int32_t	ODR;
	int32_t	BSRR;
	int32_t	BRR;
	int32_t	LCKR;
};



void GpioConfig( void );
void buttonAndLed( void );
void testBRSS( void );

/*------------------------------- MANUAL DEFINE WITH STD LIBRARIES --------------------------------*/

