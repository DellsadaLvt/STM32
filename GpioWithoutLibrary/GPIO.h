#include<stdio.h>
#include<stdint.h>
#include<time.h>

#define RccAddress		0x40021000
#define PortCAddress 	0x40011000

#ifndef header_h

#define header_h

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

struct Rcc *RCC = (struct Rcc*)RccAddress;


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

struct Gpio *GPIO = (struct Gpio*)PortCAddress;

#endif

