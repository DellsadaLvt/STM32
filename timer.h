#ifndef _TIMER_H_

#define _TIMER_H_

#include "stm32f10x.h"                  // Device header
#include "user_define.h"
	
func_status_t TIM2_init(void);
func_status_t TIM2_start(void);
func_status_t TIM2_stop(void);
func_status_t delay(uint16_t u16_tick);
inline uint16_t get_tick(void);


#endif

