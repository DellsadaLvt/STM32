#include "SysTick.h"

void SysTickInit(volatile float *time ){
	/* reset time */
	*time= 0;
	/* choose clock */
	SysTick->CTRL |= 0x01u << 2U;
	/* reset Load value */
	SysTick->LOAD = 0;
	/* reset var value */
	SysTick->VAL = 0;
	/* enable interrupts */
	SysTick->CTRL |= 0x01u << 1u;
	/* config RELOAD value */
	SysTick->LOAD = (72000u-1u);
	/* start count */
	SysTick->CTRL |= 0x01u;
}

void EndSysTick(volatile float *time ){
	/* end of SysTick */
	SysTick->CTRL &= ~0x01u;
	/* caculate total time */
	uint16_t temp = SysTick->VAL;
	*time= *time + (float)temp/(720000.0 - 1.0);
}


/*
void Delay( int16_t grep ){
	float time;
	SysTickInit( time );
	while( grep - time );
	SysTick->CTRL &= ~0x01u;
}
*/

