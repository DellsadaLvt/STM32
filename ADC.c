#include "ADC.h"



void ADC_std_config( void ){
	/* enable clock */
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE);
	
	/* config ADC pin */
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_4 |
															GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 ;
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	/* config ADC */
	/* setup ADC clock */
	RCC->CFGR |= ((0x01<<14)| (0x01<<15));
	/* init adc init struct */
	ADC_InitTypeDef ADC_InitStruct;
	/* independent mode enable */
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
	/* convert with multi channel */
	ADC_InitStruct.ADC_ScanConvMode = ENABLE;
	/* continous mode enable */
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
	/* select no external triggering */
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	/* data align */
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
	/* specified number of channel */
	ADC_InitStruct.ADC_NbrOfChannel = 8;
	ADC_Init( ADC1, &ADC_InitStruct);
	
	/* config each channel */
	ADC_RegularChannelConfig(ADC1,  ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,  ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,  ADC_Channel_2, 3, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,  ADC_Channel_3, 4, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,  ADC_Channel_4, 5, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,  ADC_Channel_5, 6, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,  ADC_Channel_6, 7, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,  ADC_Channel_7, 8, ADC_SampleTime_55Cycles5);
	
	/* enable adc */
	ADC_Cmd( ADC1, ENABLE);
	/* enable DMA ADC */
	ADC_DMACmd( ADC1, ENABLE);
	/* enable adc reset calibration */
	ADC_ResetCalibration(ADC1);
	/* check end of reset calibration register */
	while( ADC_GetResetCalibrationStatus( ADC1));
	/* start adc calibration */
	ADC_StartCalibration( ADC1);
	/* check end of calibration */
	while(ADC_GetCalibrationStatus(ADC1));
	/* enable conversion adc */
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}



void ADC_registerConfig( mode x  ){
	/* config pin ADC */
	/* enable clock gpio a */
	RCC->APB2ENR |= 0x04;
	/* setup pin a0 is input analog */
	GPIOA->CRL &= ~(0x0f);
	
	/* config adc paremeter */
	/* setup ADC clock */
	/* section 1 */
	RCC->CFGR |= ((0x01<<14)| (0x01<<15));
	/* enable adc1 clock */
	RCC->APB2ENR |= 0x200;
	 
	/* section 2 */
	/* reset ADON */
	ADC1->CR2 &= ~(0x01);
	/* choose independent mode */
	ADC1->CR1 &= ~(0xF0000);
	/* disable scan mode  */
	ADC1->CR1 &= ~(0x100);  // enable when read multi channel
	/* set CONT bit */
	ADC1->CR2 |= 0x02;
	/* select external trigger */
	ADC1->CR2 |= 0xE0000;
	/* set data align */
	ADC1->CR2 &= ~(0x800);
	
	/* section 3 */
	/* number of channel */
	ADC1->SQR1 = 0;
//	ADC1->SQR1 |= (0x01<<20);
	/* choose rank */
	ADC1->SQR3 = 0;       // channel 0
//	ADC1->SQR3 |= 0x20;
	/* set sample time 239.5 cycles */
	ADC1->SMPR2 |= 0x05;	// channel 0
//	ADC1->SMPR2 |= 0x28;  // channel 1
	
	/* section 4 */
	/* enable ADC */
	ADC1->CR2 |= 0x01;
	/* select mode */
	if( (x&INT) == INT  ){
		/* enable EOCIE bit*/
		ADC1->CR1 |= 0x01<<5;
		/* clear flag */
		ADC1->SR &= ~(0x01<<1);
		/* set priority */
		NVIC->IP[ADC1_2_IRQn] = 10u << 4u;
		/* enable int in NVIC */
		NVIC->ISER[ADC1_2_IRQn>>5u] |= (uint32_t)(0x01<< (((uint32_t)ADC1_2_IRQn)& 0x1F));
	}
	if( (x&DMA) == DMA ){
		/* enable DMA */
		ADC1->CR2 |= 0x01<<8;
	}
	/* set reset calibration */
	ADC1->CR2 |= 0x08;
	/* wait reset call */
	while(((ADC1->CR2>>3)&0x01));
	/* start calibration */
	ADC1->CR2 |= 0x04;
	/* wait calibration */
	while(((ADC1->CR2>>2)&0x01));
	/* start conversion */
	ADC1->CR2 |= 0x500000; // enable bit 20 and 22 in ADC-CR2 register.
}

