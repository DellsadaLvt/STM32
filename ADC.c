#include "ADC.h"


void ConfigADC1( void ){
	/* enable clock ADC */
	RCC->APB2ENR|= 0x01 << 9u;
	/* choose clock ADC */
	RCC->CFGR |= 0x03 << 14U;
	/* set sample clk channel 6 */
	ADC1->SMPR2|= 0x07 << 18u;
	/* set channel 6 in first sequence */
	ADC1->SQR3 |= 6u;
	/* setup external trigger */
	ADC1->CR2|= 0x0F << 17u;
	/* set CONT bit */
	ADC1->CR2 |= 0x01 << 1;
	/* set EOCIE bit */
	ADC1->CR1  |= 0x01 << 5u;
	/* enable NVIC */
	NVIC->ISER[0] |= 0x01 << 18u;
	/* Bits 19:16 DUALMOD[3:0]: Dual mode selection */
	ADC1->CR1 |= 0x06 << 16u;
	/* Bit 8 DMA: Direct memory access mode */
	//ADC1->CR2 |= 0x01 << 8u;
	/* set ADON bit */
	ADC1->CR2 |= 0x01;
	/*  reset calib*/
	ADC1->CR2 |= 0x01 <<3u;
	while((ADC1->CR2>>3u)&0x01);
	/* calib ADC */
	ADC1->CR2 |= 0x01 <<2u;
	while((ADC1->CR2>>2u)&0x01);
	/* Bit 22 SWSTART: Start conversion of regular channels */
	ADC1->CR2 |= 0x01 << 22u;
	
}


void ConfigADC2( void ){
	/* enable clock ADC */
	RCC->APB2ENR|= 0x01 << 10u;
	/* set sample clk channel 0 */
	ADC2->SMPR2|= 0x07;
	/* Bits 23:20 L[3:0]: Regular channel sequence length */
	/* set channel 0 in first sequence */
	/* setup external trigger */
	ADC2->CR2|= 0x0F << 17u;
	/* set CONT bit */
	ADC2->CR2 |= 0x01 << 1;
	/* set EOCIE bit */
	ADC2->CR1  |= 0x01 << 5u;
	/* enable NVIC */
	NVIC->ISER[0] |= 0x01 << 18u;
	/* set ADON bit */
	ADC2->CR2 |= 0x01;
	/*  reset calib*/
	ADC2->CR2 |= 0x01 <<3u;
	while((ADC2->CR2>>3u)&0x01);
	/* calib ADC */
	ADC2->CR2 |= 0x01 <<2u;
	while((ADC2->CR2>>2u)&0x01);
	/* Bit 22 SWSTART: Start conversion of regular channels */
	ADC2->CR2 |= 0x01 << 22u;
	
}



void ADCWatchdog( void ){
	/* Bit 23 AWDEN: Analog watchdog enable on regular channels */
	ADC1->CR1 |= 0x01 << 23u;
	/* Bit 6 AWDIE: Analog watchdog interrupt enable */
	ADC1->CR1 |= 0x01 << 6u;
	/* Bit 9 AWDSGL: Enable the watchdog on a single channel in scan mode */
	/* Bits 4:0 AWDCH[4:0]: Analog watchdog channel select bits */
	ADC1->CR1 |= 6U;
	/* set threshold */
	ADC1->HTR= 0x250;
}





void ADC_DualMode( void ){
	
	/*========================== config ADC1 ==========================*/
	/* enable clock ADC */
	RCC->APB2ENR|= 0x01 << 9u;
	/* choose clock ADC */
	RCC->CFGR |= 0x03 << 14U;
	/* set sample clk channel 0 */
	ADC1->SMPR2|= 0x05;    			//101: 55.5 cycles
	/* choose number of conversion */
	/* set channel 0 in first sequence */
	//ADC1->SQR3 |= 6u;
	/* setup external trigger */
	ADC1->CR2|= 0x0F << 17u; 		// internal source
	/* set CONT bit */
	ADC1->CR2 |= 0x01 << 1;  		// countinue conversion
	/* set EOCIE bit */
	ADC1->CR1  |= 0x01 << 5u; 	// enable interrupts
	/* enable NVIC */
	NVIC->ISER[0] |= 0x01 << 18u;
	/* Bits 19:16 DUALMOD[3:0]: Dual mode selection */
	ADC1->CR1 |= 0x03 << 17u; 	//0110: Regular simultaneous mode only
	/* Bit 8 DMA: Direct memory access mode */
	ADC1->CR2 |= 0x01 << 8u;
	
	
	/*========================== config ADC2 ==========================*/
	/* enable clock ADC */
	RCC->APB2ENR|= 0x01 << 10u;
	/* set sample clk channel 1 */
	ADC2->SMPR2|= 0x05 << 3u;    //101: 55.5 cycles
	/* Bits 23:20 L[3:0]: Regular channel sequence length */
	/* set channel 1 in first sequence */
	ADC2->SQR3 |= 1u;
	/* setup external trigger */
	ADC2->CR2|= 0x0F << 17u;     // internal source 
	/* set CONT bit */
	ADC2->CR2 |= 0x01 << 1;			 // continue mode
//	/* set EOCIE bit */
//	//ADC2->CR1  |= 0x01 << 5u;
//	/* enable NVIC */
//	//NVIC->ISER[0] |= 0x01 << 18u;


  /**************************** START CONVERSION *****************************/
	/* set ADON bit */
	ADC2->CR2 |= 0x01;
	/*  reset calib*/
	ADC2->CR2 |= 0x01 <<3u;
	while((ADC2->CR2>>3u)&0x01);
	/* calib ADC */
	ADC2->CR2 |= 0x01 <<2u;
	while((ADC2->CR2>>2u)&0x01);
	/* Bit 22 SWSTART: Start conversion of regular channels */
	ADC2->CR2 |= 0x01 << 22u;
	
	
	/* set ADON bit */
	ADC1->CR2 |= 0x01;
	/*  reset calib*/
	ADC1->CR2 |= 0x01 <<3u;
	while((ADC1->CR2>>3u)&0x01);
	/* calib ADC */
	ADC1->CR2 |= 0x01 <<2u;
	while((ADC1->CR2>>2u)&0x01);
	/* Bit 22 SWSTART: Start conversion of regular channels */
	ADC1->CR2 |= 0x01 << 22u;
	
}


void ADC2_SingleMode( void ){
	/* enable clock ADC */
	RCC->APB2ENR|= 0x01 << 10u;
	/* set sample clk channel 0 */
	ADC2->SMPR2|= 0x07;
	/* Bits 23:20 L[3:0]: Regular channel sequence length */
	/* set channel 0 in first sequence */
	/* setup external trigger */
	ADC2->CR2|= 0x0F << 17u;
	/* set CONT bit */
	//ADC2->CR2 |= 0x01 << 1;
	/* set EOCIE bit */
	ADC2->CR1  |= 0x01 << 5u;
	/* enable NVIC */
	NVIC->ISER[0] |= 0x01 << 18u;
	/* set ADON bit */
	ADC2->CR2 |= 0x01;
	/*  reset calib*/
	ADC2->CR2 |= 0x01 <<3u;
	while((ADC2->CR2>>3u)&0x01);
	/* calib ADC */
	ADC2->CR2 |= 0x01 <<2u;
	while((ADC2->CR2>>2u)&0x01);
	/* Bit 22 SWSTART: Start conversion of regular channels */
	//ADC2->CR2 |= 0x01 << 22u;
	
}


//void ADC1_TIMER_TRIGGER( void ){
//	/* enable clock ADC */
//	RCC->APB2ENR|= 0x01 << 9u;
//	/* choose clock ADC */
//	RCC->CFGR |= 0x03 << 14U;
//	/* set sample clk channel 6 */
//	ADC1->SMPR2|= 0x07 << 18u;
//	/* set channel 6 in first sequence */
//	ADC1->SQR3 |= 6u;
//	/* setup external trigger */
//	ADC1->CR2|= 0x0B << 17u;
//	/* set CONT bit */
//	ADC1->CR2 |= 0x01 << 1;
//	/* set EOCIE bit */
//	ADC1->CR1  |= 0x01 << 5u;
//	/* enable NVIC */
//	NVIC->ISER[0] |= 0x01 << 18u;
//	/* Bit 8 DMA: Direct memory access mode */
//	//ADC1->CR2 |= 0x01 << 8u;
//	/* set ADON bit */
//	ADC1->CR2 |= 0x01;
//	/*  reset calib*/
//	ADC1->CR2 |= 0x01 <<3u;
//	while((ADC1->CR2>>3u)&0x01);
//	/* calib ADC */
//	ADC1->CR2 |= 0x01 <<2u;
//	while((ADC1->CR2>>2u)&0x01);
//	/* Bit 22 SWSTART: Start conversion of regular channels */
//	ADC1->CR2 |= 0x01 << 22u;
//	
//}




//void initADC( void ){
//	
//	/* enable clock ADC */
//	RCC->APB2ENR|= 0x01 << 9u;
//	/* choose clock ADC */
//	RCC->CFGR |= 0x03 << 14U;
//	
//	
//	/* config ADC */
//	// clear scan mode
//	/* Bit 5 EOCIE: Interrupt enable for EOC */
//	ADC1->CR1 |= 0x01 << 5u;
//	
//	
//	// set continue bit
//	ADC1->CR2|= 0x01<<1u;
//	// align right bit 11 CR2
//	// Set channel 6 with 41.5cycles
//	ADC1->SMPR2|= 0x01 << 20u;
//	// set one conversion
//	//  set at sequence one
//	ADC1->SQR3 |= 0x06;
//	
//	
//	
//	/* Enable NVIC */
//	NVIC->ISER[0]= 0x01 << 18u;
//	
//	/* enable external event */
//	ADC1->CR2|= 0x0F << 17u;
//	// enable ADC on
//	ADC1->CR2|= 0x01;
//	/* Bit 22 SWSTART: Start conversion of regular channels */
//	ADC1->CR2|= 0x01<<22u;
////	// start CAL
////	ADC1->CR2|= 0x01 << 2;
////	// Wait for time
////	for( uint8_t i= 0; i<255; i++);
////	// get value adc
////	u16AdcValue= ADC1->DR;
//	
//}


//void ConfigADC2( void ){
//	/* enable clock ADC */
//	RCC->APB2ENR|= 0x01 << 10u;
//	/* choose clock ADC */
//	RCC->CFGR |= 0x03 << 14U;
//	/* set sample clk channel 0 and 1 */
//	ADC2->SMPR2|= 0x07;
//	//ADC2->SMPR2|= 0x07 << 3u;
//	/* Bits 23:20 L[3:0]: Regular channel sequence length */
//	//ADC2->SQR1|= 0x01<< 20u; // 2 conversions
//	/* set channel 0 in first sequence */
//	/* set channel 1 in second sequence */
//	//ADC2->SQR3 |= 0x01 << 5u;
//	/* setup external trigger */
//	ADC2->CR2|= 0x0F << 17u;
//	/* set CONT bit */
//	ADC2->CR2 |= 0x01 << 1;
//	/* Bit 8 SCAN: Scan mode */
//	//ADC2->CR1 |= 0x01 << 8u;
//	/* set EOCIE bit */
//	//ADC2->CR1  |= 0x01 << 5u;
//	/* enable NVIC */
//	//NVIC->ISER[0] |= 0x01 << 18u;
//	/* set ADON bit */
//	ADC2->CR2 |= 0x01;
//	/*  reset calib*/
//	ADC2->CR2 |= 0x01 <<3u;
//	while((ADC2->CR2>>3u)&0x01);
//	/* calib ADC */
//	ADC2->CR2 |= 0x01 <<2u;
//	while((ADC2->CR2>>2u)&0x01);
//	/* Bit 22 SWSTART: Start conversion of regular channels */
//	ADC2->CR2 |= 0x01 << 22u;
//	
//}



