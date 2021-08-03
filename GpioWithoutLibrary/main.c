/*=============================================*/
/*====================== LIBRARIES ===============*/
#include"GPIO.h"


/*====================== FUNCTION ================*/
void Delay( int32_t reg);
void BlinkPc13( void);
void ConfigGpio( void );


/*=======================	MAIN ======================*/
int main()
{
	ConfigGpio();
	
	while(1)
	{
		BlinkPc13();
		//float clk = clock();
	}

}



/*==================	SUBROUTINE ======================*/
/*00*/
void ConfigGpio( void )
{
	RCC->APB2ENR 	|= 0x10;
	GPIO->CRH 		|= 0x300000;
	GPIO->ODR			|= 0x2000;
}


/*01*/
void BlinkPc13( void)
{
	GPIO->ODR	&= ~(0x2000);
	Delay(100000);
	GPIO->ODR	|= (0x2000);
	Delay(100000);
}


/*02*/
void Delay( int32_t reg)
{
	for( ;reg>=0;reg--)
	{
	}
}

