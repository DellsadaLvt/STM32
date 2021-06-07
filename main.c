#include "sysTick.h"
#include "IWDG.h"


int main(void){
	sysTickConfig(72000u);
	configGpio();
	while(1){
		IWDG_config(7u, 2000u);
		GPIO_WriteBit( GPIOC,  GPIO_Pin_13, Bit_SET);
		delay_ms(500u);
		GPIO_WriteBit( GPIOC,  GPIO_Pin_13, Bit_RESET);
		delay_ms(500u);
	}
}

