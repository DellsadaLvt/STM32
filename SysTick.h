#ifndef __SYSTICK_H
#define __SYSTICK_H

#ifdef __cplusplus
	extern "C"{
#endif

/* includes */
#include "stm32f10x.h"                  // Device header

/* groups function */
void SysTickInit(volatile float *time );
void EndSysTick(volatile float *time );


#ifdef __cplusplus
}
#endif

#endif

