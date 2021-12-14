#include "dht11.h"

static int8_t check_bit(uint8_t u8_timeout){
	/* the state in logic low */
	//delay(50u);
	uint16_t u16_tick_current = get_tick();
	while( 0u == (GPIOA->IDR & (uint16_t)0x01)){
			if(get_tick() - u16_tick_current > u8_timeout)
				return dht11_time_out;
	}
	
	/* state in logic high */
	uint16_t u16_tick_count = get_tick();
	
	u16_tick_current = get_tick();
	while( 1u == (GPIOA->IDR & (uint16_t)0x01)){
			if(get_tick() - u16_tick_current > u8_timeout)
				return dht11_time_out;
	}
	
	uint8_t u8_time = (uint16_t)(get_tick()) - u16_tick_count;
	/* bit 1: state high logic about 26-28us, 
	   bit 0: state high logic about 60-70us*/
	if( u8_time > DHT_TIME_IDENTIFY_1_OR_0 )
		return 1u;
	else
		return 0u;
	
}

func_status_t dht11(float *const f_humid, float *const f_temperature, uint8_t u8_timeout ){
	
	/* step 2: master pull down data line >18ms then free data line */
	GPIOA->BSRR |= ((uint32_t)0x01 << 16u); 
	delay(20000u);
	GPIOA->BSRR |= ((uint32_t)0x01);  

	/* step 3: check response: wait until the sensor pull down data line */
	uint16_t u16_tick_current = get_tick();
	while( 1u == (GPIOA->IDR & (uint16_t)0x01)){
			if(get_tick() - u16_tick_current > u8_timeout)
				return dht11_time_out;
	}
	//delay(80u);
	
	/* wait sensor free data line: about 80us  */
	u16_tick_current = get_tick();
	while(0u == (GPIOA->IDR & (uint16_t)0x01)){
			if(get_tick() - u16_tick_current > u8_timeout)
				return dht11_time_out;
	}
	//delay(80u);
	
	/* wait sensor start send data */
	u16_tick_current = get_tick();
	while( 1u == (GPIOA->IDR & (uint16_t)0x01)){
			if(get_tick() - u16_tick_current > u8_timeout)
				return fail;
	}
	
	/* read bits data */
	uint32_t buff= 0u;
	uint8_t parity= 0u;
	for(uint8_t bit=0u; bit<DHT_NUM_BIT_FRAME; bit+=1u){
		if( bit < DHT_NUM_BIT_DATA){
			buff <<= 1u;
			buff |= (uint32_t)check_bit(90u);
		}
		else{
			parity <<= 1u;
			parity |= (uint32_t)check_bit(90u);
		}
	}
	
	/* store data */
	uint8_t humid_high 	= (buff >> 24u)&0xFF;
	uint8_t humid_low 	= (buff >> 16u)&0xFF;
	uint8_t temp_high 	= (buff >> 8u)&0xFF;
	uint8_t temp_low 		=  buff&0xFF;
	uint8_t u8_compare_parity = humid_high + humid_low + temp_high + temp_low;
	
	/* get data */
	if(0u == (u8_compare_parity - parity)){
		*f_humid = humid_high + humid_low/10.0;
		*f_temperature = temp_high + temp_low/10.0;
		
		/* end of the tranmition */
		delay(50u);
		return oke;
	}
	
	return fail;
}




