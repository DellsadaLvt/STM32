#ifndef _DHT11_H_

#define _DHT11_H_

#include "stm32f10x.h"                  // Device header
#include "user_define.h"
#include "timer.h"

#ifndef DHT_NUM_BIT_FRAME
	
#define DHT_NUM_BIT_FRAME     		((uint8_t)40U)
#define DHT_NUM_BIT_DATA     			((uint8_t)32U)
#define DHT_NUM_BIT_PARITY     		((uint8_t)8U)
#define DHT_TIME_IDENTIFY_1_OR_0 	((uint8_t)30u)
	
#endif

/*
@brief: u8_timeout is us unit.
*/
func_status_t dht11(float *const humid, float *const temperature, uint8_t u8_timeout );

#endif /* _DHT11_H_ */

