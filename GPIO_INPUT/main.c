#include"GPIO.h"
//#include"UseGpioSTD.h"


int main( void )
{
	GpioConfig();
	
	while(1)
	{
		buttonAndLed();
		//GpioControl();
	}	
	
}




