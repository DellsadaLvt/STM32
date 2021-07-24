#include "I2C.h"
#include "EXTI.h"
#include <math.h>
//#include "uart.h"
#include "Filter.h"
//#include <stdio.h>
#include "GPIO.h"



/* Register MPU */
#define sample_rate		25
#define config				26
#define gyro_config		27
#define acc_config		28
#define Level_INT     55
#define interrupts		56
#define	pwr_manager		107
#define acc_x					59
#define acc_y					61
#define acc_z					63




/* init value */
volatile	float ax, ay, az, pitch, pitchk, pitchLpf,pitchHpf, roll;
//volatile	char u8Send[20], u8Ax[50], u8Ay[20], u8Az[20];  

/* Get value Acc */
int16_t MeasureAcc(uint8_t address );




int main( void ){
	/* init config */
//	UART1_trasmit("Start program\n");
	GPIO_I2C_INIT();
	I2C_init();
	sendData(0x68, sample_rate, 249u);
	sendData(0x68, config, 6u);
	sendData(0x68, gyro_config, 0x10);
	sendData(0x68, acc_config, 0x10);
	sendData(0x68, Level_INT, 0x80 );
	sendData(0x68, interrupts, 1u );
	sendData(0x68, pwr_manager, 1u );
	GPIO_EXTI_config();
	EXT0_config();
	while(1){
	}
}



/*----------------- subrountine --------------------*/
int16_t MeasureAcc(uint8_t address ){
	uint8_t value[2];
	int16_t raw;
	value[0]= ReceiveOneByte(0x68, address);
	value[1]= ReceiveOneByte(0x68, address+1);
	raw= value[0]<<8 | value[1];
//	
//	
//	
//	sprintf((char*)u8Ax, "Axh: %d\n", value[0]);
//	sprintf((char*)u8Ay, "Axl: %d\n", value[1]);
//	sprintf((char*)u8Az, "Ax:  %d\n\n", raw);
//	UART1_trasmit((char*)u8Ax);
//	UART1_trasmit((char*)u8Ay);
//	UART1_trasmit((char*)u8Az);
	return raw;
}



void EXTI0_IRQHandler( void ){
	if(	EXTI->PR&0x01 && EXTI->IMR&0x01){
		//UART1_trasmit("================ Get raw value ===============\n");
		ax = MeasureAcc(59)/4096.0; //   /4096
		ay = MeasureAcc(61)/4096.0;
		az = MeasureAcc(63)/4096.0;
		

//		sprintf((char*)u8Ax, "The result-> Ax: %f, Ay: %f, Az: %f\n", ax, ay, az);
//		UART1_trasmit((char*)u8Ax);
		
		
		
		pitch = atan2(ax, sqrt(pow(ay,2)+pow(az,2)))*180/(atan(1)*4);
		pitchk= kalman_single(pitch, 100, 10);
//		sprintf((char*)u8Send, "Pitch angle: %f\n", pitch);
//		UART1_trasmit((char*)u8Send);
		//roll  = atan2(-ay, az)*180.0/(atan(1)*4);
		EXTI->PR |= 0x01;
	}
}



