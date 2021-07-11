#include "GPIO.h"
#include "I2C.h"
#include "EXTI.h"
#include <math.h>


/* Register MPU */
#define sample_rate		25
#define config				26
#define gyro_config		27
#define acc_config		28
#define activeINT     55
#define interrupts		56
#define	pwr_manager		107
#define acc_x					59
#define acc_y					61
#define acc_z					63




/* init value */
volatile	float ax, ay, az;
volatile	float pitch;

/* Get value Acc */
uint16_t MeasureAcc(uint8_t address );




int main( void ){
	/* init config */
	GPIO_I2C_INIT();
	I2C_init();
	sendData(0x68, sample_rate, 19u);
	sendData(0x68, config, 5u);
	sendData(0x68, gyro_config, 8u);
	sendData(0x68, acc_config, 0x10);
	sendData(0x68, activeINT, 0x80 );
	sendData(0x68, interrupts, 1u );
	sendData(0x68, pwr_manager, 1u );
	GPIO_EXTI_config();
	EXT0_config();
	while(1){
	}
}



/*----------------- subrountine --------------------*/
uint16_t MeasureAcc(uint8_t address ){
	uint8_t value[2];
	uint16_t raw;
	ReceiveOneByte(0x68, address, value);
	ReceiveOneByte(0x68, address+1, value+1);
	raw= (uint16_t)value[0]<<8 | value[1];
	return raw;
}



void EXTI0_IRQHandler( void ){
	if(	EXTI->PR&0x01 && EXTI->IMR&0x01){
		ax = (float)MeasureAcc(59)/4096.0;
		ay = (float)MeasureAcc(61)/4096.0;
		az = (float)MeasureAcc(63)/4096.0;
		pitch = atan2(ax, sqrt(pow(ay,2)+pow(az,2)))*180/3.14;
		EXTI->PR |= 0x01;
	}
	
}



