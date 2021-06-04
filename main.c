#include "sysTick.h"
#include "EXTI.h"


int main( void ){
	
	GPIO_config();
	stdEXTI_config();
	sysTickConfig(72000);
	
	while(1){
		softwareEXTI();
	}
}





