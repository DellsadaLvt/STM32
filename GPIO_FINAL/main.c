#include "stm32f10x.h"
//#include"GpioUserBuil.h"


int main(void)
{
	//GpioConfig();
	
	while(1)
	{
		//buttonAndLed();
		
		//* TEST ACTION OF BSRR */
		//testBRSS();
		
	AFIO->EXTICR[1] = 0;
	}
}
