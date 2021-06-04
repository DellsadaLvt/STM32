#include "sysTick.h"


float fTimeMeasure;


int main( void ){
	/* initial value */
	uint32_t test2 = 2000000;
	fTimeMeasure = 0;
	/* setup gpio */
	configGpio();
	/* setup sysTick */
	sysTickConfig(72000);
	while(test2--);
	fTimeMeasure= getTime();
	/* setup systick again */
	sysTickConfig( 72000);

	while(1){
		GPIO_WriteBit( GPIOC,  GPIO_Pin_13, Bit_RESET);
		delay_ms(1000);
		GPIO_WriteBit( GPIOC,  GPIO_Pin_13, Bit_SET);
		delay_ms(1000);
	}
	
	
}


