#ifndef _GPIO_H_

#define _GPIO_H_

#include "stm32f10x.h"                  // Device header
#include "user_define.h"
	
func_status_t dht11_gpio_init(void);
func_status_t gpio_led_pc13_init(void);


#endif

