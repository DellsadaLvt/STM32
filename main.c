#include "stm32f10x.h"                  // Device header
#include "Filter.h"
#include "ADC.h"
#include <math.h>
#include <stdlib.h>

#define PI 3.141592653589793f
volatile float _sin, _random, random_LPF_HPF, signal_LPF, signal_HPF, random_kalman, signal_kalman;
volatile uint16_t u16ADCValue, u16KalmanADCValue;

void Filter( void );

int main( void ){
	ADC_registerConfig( INT );
	while(1){
		//Filter();
		u16KalmanADCValue = kalman_single(u16ADCValue, 500, 10);
	}
}


void Filter( void ){
	static float x= 0;
	
	_sin = sin(x)*1000;
	x+= 2*PI/1000;
	_random = (float)rand()/1000000;
	
	random_LPF_HPF = _random + _sin;
	signal_LPF = LPF(random_LPF_HPF, 1u, 1000u);
	signal_HPF = HPF(random_LPF_HPF, 10u, 1000u);
	
	random_kalman = (float)rand()/1000000u;
	signal_kalman = kalman_single(random_kalman, 500, 10);
	
}



void ADC1_2_IRQHandler( void ){
	if( ((ADC1->CR1>>5)&0x01) && ((ADC1->SR>>1)&0x01) ){
		u16ADCValue = ADC1->DR;
	}
}

