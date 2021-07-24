#include "uart.h"


/*================================ NORMAL USART  ===================================*/
/*extern*/ volatile char readUSART[50];
/*******************************************************
*
*
********************************************************/
void UART1_trasmit( char *data ){
	/* enable clock UART1, port A, AFIO */
	RCC->APB2ENR |= (enaUart1 | enaPortA | enaAFIO );
	/* setup alternate output pp gpio pinA9 as Tx */
	GPIOA->CRH &= ~((uint32_t)0x0f<<4);
	GPIOA->CRH |= ( (outMaxSpeed50MHz |  (ppAfio << 2)  )<< 4); // 1011 0000
	/* setup alternate output pp gpio pinA10 as Rx */
	
	/* sequence config uart1 page 793 */
	/* set UE bit */
	USART1->CR1 |= setUE;
	/* setup word length 8 bit */
	USART1->CR1 |= ((uint16_t)wl8Bits<<12);
	/* setup stopbit length */
	USART1->CR2 |= oneSTB<< 12;
	/* config parity */
//	USART1->CR1 |= setPCE;   								// enable parity
//	USART1->CR1 |= (uint32_t)(even<<9);  		// choose even checking
	//USART1->CR1 |= setPEIE;								// enable interrupts
	
	/* DMA */
	//xxxxxxxxxx
	/* select baud rate */
	USART1->BRR = 0x1D4C;
	/* set TE: transmit enable */
	USART1->CR1 |= setTE;
	/* wait Transmit data register empty */
	while(!((USART1->SR>>7)&(uint32_t)0x01));
	/* start transfer */
	for( uint8_t i=0; i< strlen(data); i++){
		/*write data */
		USART1->DR = *(data + i);
		/* wait transmit complete */
		while(!((USART1->SR>>6)&0x01));
	}
	/* disable UE */
	//USART1->CR1 &= ~setUE;
}



/*================ TRANSTER NUMBER ==================*/
/*******************************************************
*
*
********************************************************/
void USART1_receive( void ){
	/* enable clock UART1, port A, AFIO */
	RCC->APB2ENR |= (enaUart1 | enaPortA | enaAFIO );
	/* setup alternate output pp gpio pinA9 as Tx */
	GPIOA->CRH &= ~((uint32_t)0x0f<<8);
	GPIOA->CRH |= ( (input	 |  (floatInput<< 2)  )<< 8); // 0100 
	/* setup alternate output pp gpio pinA10 as Rx */
	
	/* enable usart by set UE bit */
	USART1->CR1 |= setUE;
	/* setup word length 8 bit */
	USART1->CR1 |= ((uint16_t)wl8Bits<<12);
	/* setup stopbit length */
	USART1->CR2 |= oneSTB<< 12;
	/* config parity */
//	USART1->CR1 |= setPCE;   							// enable parity
//	USART1->CR1 |= (uint32_t)(even<<9);  // choose even checking
	//USART1->CR1 |= setPEIE;								// enable interrupts
	/**/
	/* DMA */
	/* xxxxxxxxxx */
	
	/* RE: Receiver enable */
	USART1->CR1 |= setRE;
	/* select baud rate */
	USART1->BRR = 0x1D4C;
	/* RXNE :  1: Received data is ready to be read */
	/* An interrupt is generated if the RXNEIE bit is set */
	USART1->CR1 |= setRXNEIE;
	
	/* set NVIC */
	NVIC->ISER[1] =  enaUSART_INT_NIVC;
}
/*******************************************************
*
*
********************************************************/
//void USART1_IRQHandler( void ){
////	static uint8_t pos= 0;
//	/* check error: parity, frame, noise, overun detect bit */
//	if( (~(USART1->SR)&0x01u) && (~(USART1->SR>>1u)&0x01u) && (~(USART1->SR>>2u)&0x01u) && (~(USART1->SR>>3u)&0x01u) ){
//		/* check interrupts flag and enable interrupts enable */
//		if( ((USART1->SR>>5u)&0x01u) && ((USART1->CR1>>5u)&0x01u) ){
//			readUSART[0] = USART1->DR;
//			//UART1_trasmit((char *)(readUSART+pos));
////			pos++;
////			if(pos>=50)
////				pos=0;
//		}
//	}
//	/* reset all flag errors */
//	readUSART[49u] = USART1->DR;
//}

/*==============================================================================*/










/*================================ DMA USART  ===================================*/
void USART_DMA_CONFIG_RX( void ){
	/* enable clock UART1, port A, AFIO */
	RCC->APB2ENR |= (enaUart1 | enaPortA | enaAFIO );
	/* setup alternate output pp gpio pinA9 as Rx */
	GPIOA->CRH &= ~((uint32_t)0x0f<<8);
	GPIOA->CRH |= ( (input	 |  (floatInput<< 2)  )<< 8); // 0100 
	
	//
	/* enable usart by set UE bit */
	USART1->CR1 |= setUE;
	/* setup word length 9 bit */
	USART1->CR1 |= ((uint16_t)wl9Bits<<12);
	/* setup stopbit length */
	USART1->CR2 |= oneSTB<< 12;
	/* config parity */
	USART1->CR1 |= setPCE;   								// enable parity
	USART1->CR1 |= (uint32_t)(even<<9);  		// choose even checking
	//USART1->CR1 |= setPEIE;								// enable interrupts
	//
	/* DMA */
	USART1->CR3 |= 0x01<<6;   							// DMA enable receiver 
	//USART1->CR3 |= 0x01<<7;   							// DMA enable transmiter
	/* RE: Receiver enable */
	USART1->CR1 |= setRE;
	/* select baud rate */
	USART1->BRR = 0x1D4C;
	/* RXNE :  1: Received data is ready to be read */
	/* An interrupt is generated if the RXNEIE bit is set */
	//USART1->CR1 |= setRXNEIE;
	/* set NVIC */
	//NVIC->ISER[1] =  enaUSART_INT_NIVC;
	
}
/*******************************************************
*
*
********************************************************/
void DMA_RX(uint32_t *startAdd, uint32_t *endAdd, uint16_t u16NumberOfData){
	/* enable DMA1 clock */
	RCC->AHBENR |= 0x01;
	/* Set the peripheral register address in the DMA_CPARx register. The data will be
	moved from/ to this address to/ from the memory after the peripheral event */
	DMA1_Channel5->CPAR = (uint32_t)startAdd;
	/* Set the memory address in the DMA_CMARx register. The data will be written to or
	read from this memory after the peripheral event */
	DMA1_Channel5->CMAR = (uint32_t)endAdd;
	/* Configure the total number of data to be transferred in the DMA_CNDTRx register.
	After each peripheral event, this value will be decremented */
	DMA1_Channel5->CNDTR = u16NumberOfData;
	/* Configure the channel priority using the PL[1:0] bits in the DMA_CCRx register */
	DMA1_Channel5->CCR |= (0x01<<13);   // set bit 12, 13: 01-> medium priority
	/* Configure data transfer direction, circular mode, peripheral & memory incremented
	mode, peripheral & memory data size, and interrupt after half and/or full transfer in the
	DMA_CCRx register */
	DMA1_Channel5->CCR &= ~(0x01<<4); // set direction read from pripheral
	DMA1_Channel5->CCR |= (0x01<<5);  // set circular mode
	DMA1_Channel5->CCR &= ~(0X01<<6); // disable pripheral increment mode
	DMA1_Channel5->CCR |= (0x01<<7);  // enable memory increment mode
	DMA1_Channel5->CCR &= ~(0x03<<8);  // set pripheral at 8bit
	DMA1_Channel5->CCR &= ~(0x03<<10);  // set memory at 8bit
	/* Activate the channel by setting the ENABLE bit in the DMA_CCRx register */
	//DMA1_Channel5->CCR |= 0x01;
}

void activeDMA_Channel5( uint16_t u16NumberOfData ){
	if( ((USART1->SR)&0x01u) || ((USART1->SR>>1u)&0x01u) || ((USART1->SR>>2u)&0x01u) || ((USART1->SR>>3u)&0x01u) ){
		/* Activate the channel by setting the ENABLE bit in the DMA_CCRx register */
		DMA1_Channel5->CCR &= ~(0x01);
	}else{
		DMA1_Channel5->CNDTR = u16NumberOfData;
		DMA1_Channel5->CCR |= 0x01;
	}
}
/*******************************************************
*
*
********************************************************/
void USART_DMA_CONFIG_TX( void ){
	/* enable clock UART1, port A, AFIO */
	RCC->APB2ENR |= (enaUart1 | enaPortA | enaAFIO );
	/* setup alternate output pp gpio pinA9 as Tx */
	GPIOA->CRH &= ~((uint32_t)0x0f<<4);
	GPIOA->CRH |= ( (outMaxSpeed50MHz |  (ppAfio << 2)  )<< 4); // 1011 0000
	/* setup alternate output pp gpio pinA9 as Rx */
	
	/* sequence config uart1 page 793 */
	/* set UE bit */
	USART1->CR1 |= setUE;
	/* setup word length 8 bit */
	USART1->CR1 |= ((uint16_t)wl9Bits<<12);
	/* setup stopbit length */
	USART1->CR2 |= oneSTB<< 12;
	/* config parity */
	USART1->CR1 |= setPCE;   								// enable parity
	USART1->CR1 |= (uint32_t)(even<<9);  		// choose even checking
	//USART1->CR1 |= setPEIE;								// enable interrupts
	
	/* DMA */
	USART1->CR3 |= 0x01<<7;   							// DMA enable transmiter
	/* select baud rate */
	USART1->BRR = 0x1D4C;
	/* set TE: transmit enable */
	USART1->CR1 |= setTE;
	/* wait Transmit data register empty */
	while(!((USART1->SR>>7)&(uint32_t)0x01));
	/*write data */
	//USART1->DR = *data;
	/* clear TC bit */
	USART1->SR &= ~(0x01<<6u);
	/* wait transmit complete */
	while(!((USART1->SR>>6)&0x01));
	/* disable UE */
	//USART1->CR1 &= ~setUE;
	
}
/*******************************************************
*
*
********************************************************/
void DMA_TX_INIT(uint32_t *startAdd, uint32_t *endAdd, uint16_t u16NumberOfData){
	/* enable DMA1 clock */
	RCC->AHBENR |= 0x01;
	/* Set the peripheral register address in the DMA_CPARx register. The data will be
	moved from/ to this address to/ from the memory after the peripheral event */
	DMA1_Channel4->CMAR = (uint32_t)startAdd;
	/* Set the memory address in the DMA_CMARx register. The data will be written to or
	read from this memory after the peripheral event */
	DMA1_Channel4->CPAR = (uint32_t)endAdd;
	/* Configure the total number of data to be transferred in the DMA_CNDTRx register.
	After each peripheral event, this value will be decremented */
	DMA1_Channel4->CNDTR = u16NumberOfData;
	/* Configure the channel priority using the PL[1:0] bits in the DMA_CCRx register */
	DMA1_Channel4->CCR |= (0x01<<13);   // set bit 12, 13: 01-> medium priority
	/* Configure data transfer direction, circular mode, peripheral & memory incremented
	mode, peripheral & memory data size, and interrupt after half and/or full transfer in the
	DMA_CCRx register */
	DMA1_Channel4->CCR |= (0x01<<4); 		// set direction read from memory
	DMA1_Channel4->CCR &= ~(0x01<<5);  	// set circular mode
	DMA1_Channel4->CCR &= ~(0X01<<6); 	// disable pripheral increment mode
	DMA1_Channel4->CCR |= (0x01<<7);  	// enable memory increment mode
	DMA1_Channel4->CCR &= ~(0x03<<8);  	// set pripheral at 8bit
	DMA1_Channel4->CCR &= ~(0x03<<10);  // set memory at 8bit
	/* Activate the channel by setting the ENABLE bit in the DMA_CCRx register */
	//DMA1_Channel4->CCR |= 0x01;
}
/*******************************************************
*
*
********************************************************/
void activeDMA_Channel4( isActive x, uint16_t u16reloadNumberOfData ){
	if( x == active){
		/* reload number of data */
		DMA1_Channel4->CNDTR = u16reloadNumberOfData;
		/* enable write data */
		DMA1_Channel4->CCR |= 0x01;
	}else{
		/* disable write data */
		DMA1_Channel4->CCR &= ~(0x01);
	}
}
/*******************************************************
*
*
********************************************************/

void USART_DMA_CONFIG(  receiveOrTransmit mode  ){
	if( mode & Tx){
		/* setup alternate output pp gpio pinA9 as Tx */
		GPIOA->CRH &= ~((uint32_t)0x0f<<4);
		GPIOA->CRH |= ( (outMaxSpeed50MHz |  (ppAfio << 2)  )<< 4); // 1011 0000
	}
	if( mode & Rx ){
		/* setup alternate output pp gpio pinA9 as Rx */
		GPIOA->CRH &= ~((uint32_t)0x0f<<8);
		GPIOA->CRH |= ( (input	 |  (floatInput<< 2)  )<< 8); // 0100 
	}
}
/*==============================================================================*/











/*================================ DMA MEMTOMEM  ===================================*/
void DMA_MEMTOMEM ( uint32_t *startAdd, uint32_t *endAdd, uint16_t u16NumberOfData ){
	/* enable DMA1 clock */
	RCC->AHBENR |= 0x01;
	/* Set the peripheral register address in the DMA_CPARx register. The data will be
	moved from/ to this address to/ from the memory after the peripheral event */
	DMA1_Channel5->CMAR = (uint32_t)startAdd;
	/* Set the memory address in the DMA_CMARx register. The data will be written to or
	read from this memory after the peripheral event */
	DMA1_Channel5->CPAR = (uint32_t)endAdd;
	/* Configure the total number of data to be transferred in the DMA_CNDTRx register.
	After each peripheral event, this value will be decremented */
	DMA1_Channel5->CNDTR = u16NumberOfData;
	/* Configure the channel priority using the PL[1:0] bits in the DMA_CCRx register */
	DMA1_Channel5->CCR |= (0x01<<13);   // set bit 12, 13: 01-> medium priority
	/* Configure data transfer direction, circular mode, peripheral & memory incremented
	mode, peripheral & memory data size, and interrupt after half and/or full transfer in the
	DMA_CCRx register */
	DMA1_Channel5->CCR |= (0x01<<4); // set direction read from MEMORY
	DMA1_Channel5->CCR |= (0x01<<5);  // set circular mode
	DMA1_Channel5->CCR |= (0X01<<6); // enable pripheral increment mode
	DMA1_Channel5->CCR |= (0x01<<7);  // enable memory increment mode
	DMA1_Channel5->CCR &= ~(0x03<<8);  // set pripheral at 8bit
	DMA1_Channel5->CCR &= ~(0x03<<10);  // set memory at 8bit
	/* Activate the channel by setting the ENABLE bit in the DMA_CCRx register */
	DMA1_Channel5->CCR |= (0x01<<14);
	DMA1_Channel5->CCR |= 0x01;
}
/*==============================================================================*/


void DMA_MEMTOMEM_02 ( uint32_t *startAdd, uint32_t *endAdd, uint16_t u16NumberOfData ){
	/* enable DMA1 clock */
	RCC->AHBENR |= 0x01;
	/* Set the peripheral register address in the DMA_CPARx register. The data will be
	moved from/ to this address to/ from the memory after the peripheral event */
	DMA1_Channel5->CMAR = (uint32_t)endAdd;
	/* Set the memory address in the DMA_CMARx register. The data will be written to or
	read from this memory after the peripheral event */
	DMA1_Channel5->CPAR = (uint32_t)startAdd;
	/* Configure the total number of data to be transferred in the DMA_CNDTRx register.
	After each peripheral event, this value will be decremented */
	DMA1_Channel5->CNDTR = u16NumberOfData;
	/* Configure the channel priority using the PL[1:0] bits in the DMA_CCRx register */
	DMA1_Channel5->CCR |= (0x01<<13);   // set bit 12, 13: 01-> medium priority
	/* Configure data transfer direction, circular mode, peripheral & memory incremented
	mode, peripheral & memory data size, and interrupt after half and/or full transfer in the
	DMA_CCRx register */
	DMA1_Channel5->CCR &= ~(0x01<<4); // set direction read from peripheral
	DMA1_Channel5->CCR |= (0x01<<5);  // set circular mode
	DMA1_Channel5->CCR |= (0X01<<6); // enable peripheral increment mode
	DMA1_Channel5->CCR |= (0x01<<7);  // enable memory increment mode
	DMA1_Channel5->CCR &= ~(0x03<<8);  // set pripheral at 8bit
	DMA1_Channel5->CCR &= ~(0x03<<10);  // set memory at 8bit
	/* Activate the channel by setting the ENABLE bit in the DMA_CCRx register */
	DMA1_Channel5->CCR |= (0x01<<14);
	DMA1_Channel5->CCR |= 0x01;
}
/*==============================================================================*/












/*================================ Sample code  ===================================*/
void sample( void ){
	volatile char u8bufferRx[10];
	USART_DMA_CONFIG_RX();
	DMA_RX( (uint32_t *)addUSART_DR, (uint32_t *)u8bufferRx, 3u);
	USART_DMA_CONFIG_TX();
	DMA_TX_INIT((uint32_t *)u8bufferRx, (uint32_t *)addUSART_DR, 3u);
	while(1){
		if( u8bufferRx[0u] == '0' ){
			activeDMA_Channel4( deActive , 3u);
			activeDMA_Channel4( active , 3u);
			u8bufferRx[0u] = '1';
		}
		activeDMA_Channel5(3u);
	} 
}



void sample2( void ){
	volatile char str1[20]={"hello world!"};
	volatile char str2[20];
	DMA_MEMTOMEM ( (uint32_t *)str1,(uint32_t *)str2, strlen((char*)str1) );
	while(1){
	}
} 
/*==============================================================================*/


