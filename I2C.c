#include "I2C.h"

void I2C_init( void ){
	/* enable clock I2C */
	RCC->APB1ENR |= (uint32_t)0x01 << posClockI2C1;
	/* Reset software */
	I2C1->CR1 |=  0x8000;
	I2C1->CR1 &= ~0x8000;
	/* Program the peripheral input clock in I2C_CR2 
	register in order to generate correct timings */
	I2C1->CR2 |= 36u; // freq is 36Mhz
	/* Configure the clock control registers */
	/* (fPCLK1= 36 MHz.,VDD_I2C = 3.3 V)
	RP = External pull-up resistance, fSCL = I2C speed,
	RP = 4.7 kO, Rs: resistor protect bus I2C.*/
	I2C1->CCR = 180u; 
	/* Configure the rise time register */
	I2C1->TRISE = 37u;
	/*Program the I2C_CR1 register to enable the peripheral */
	I2C1->CR1 |= (uint16_t)0x01;
	
	/* SETUP FOR RECEIVE DATA */
	/* Event interrupt enable */
	//I2C1->CR2 |= (uint32_t)0x01 << 9u;
	/* Buffer interrupt enable */
	//I2C1->CR2 |= (uint32_t)0x01 << 10u;
	/* Enable ACK */
	I2C1->CR1 |= (uint32_t)0x01 << 10u;  // use for receive more bytes
	/* enable NVIC */
	//NVIC->ISER[0] |= (uint32_t)0x01 << 31u; 
}




void sendData( uint8_t I2C_Address, uint8_t address, uint8_t value ){
	/* make sure Busy is clear */
	while( (I2C1->SR2)&0x02 ){}
		
		
	/* TRANFER ADDRESS NEED TO READ */	
	/* Set the START bit in the I2C_CR1 register to generate a Start condition */
	I2C1->CR1 |= 0x100;
	/*	EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address. */
	while( !(I2C1->SR1&0x01) ){}
	delay(2u);
	I2C1->DR= I2C_Address << 1u;
		
	/* EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.*/
	while( !( I2C1->SR1&0x02 )){}
	I2C1->SR2;
	
		
	/* EV8_1: TxE=1, shift register empty, data register empty, write Data1 in DR */
	/* Write register address of mpu in DR register */
	while( !(I2C1->SR1&0x80)){}
	I2C1->DR= address;
		/* EV8: TxE=1, shift register not empty, data register empty, cleared by writing DR register . */
	while( !(I2C1->SR1&0x80)){}
	I2C1->DR= value;
  /* EV8_2: TxE=1, BTF = 1, Program Stop request. TxE and BTF are cleared by hardware by the Stop condition */
	while( ! (I2C1->SR1&0x80 && I2C1->SR1&0x04  )){}
	/* set stop bit */
	I2C1->CR1 |= 0x200;

}


void ReceiveOneByte( uint8_t I2C_Address, uint8_t address, uint8_t *data){
	/* make sure Busy is clear */
	while( (I2C1->SR2)&0x02 ){}
		
		
	/* TRANFER ADDRESS NEED TO READ */	
	/* Set the START bit in the I2C_CR1 register to generate a Start condition */
	I2C1->CR1 |= 0x100;
	/*	EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address. */
	while( !(I2C1->SR1&0x01) ){}
	delay(10u);
	I2C1->DR= I2C_Address << 1u;
		
	/* EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.*/
	while( !( I2C1->SR1&0x02 )){}
	I2C1->SR2;
	
		
	/* EV8_1: TxE=1, shift register empty, data register empty, write Data1 in DR */
	/* Write register address of mpu in DR register */
	while( !(I2C1->SR1&0x80)){}
	I2C1->DR= address;
	while( !(I2C1->SR1&0x80)){}
		
	
	/* READ DATA */
	/* Set the START bit in the I2C_CR1 register to generate a Start condition */
	I2C1->CR1 |= 0x100;
	
	/* EV5: SB=1, cleared by reading SR1 register followed by writing the DR register */
	while( !(I2C1->SR1&0x01)){}
	I2C1->DR= (I2C_Address << 1u) | 0x01;
	
	/* EV6_3: ADDR = 1, program ACK = 0, clear ADDR by reading SR1 register 
	followed by reading SR2 register, program STOP =1 just after ADDR is cleared.*/
	while( !(I2C1->SR1&0x02)){}
	I2C1->CR1 &= ~0x400;  // clear ACK bit
	I2C1->SR2;															// Read SR2 to clear ADDR 							
	I2C1->CR1 |= 0x200;								// set stop bit 
	
	
	/* EV7: RxNE =1, cleared by reading DR register. */
	while( !( I2C1->SR1&0x40) ){}
	*data = I2C1->DR;
	/* Set ACK bit */
	//I2C1->CR1 |= (uint32_t)0x01 << 10u;  
}



///* SAMPLE */
//int i2c_readbyte(char saddr,char maddr,uint8_t *data){
//	 while (I2C1->SR2 & 2){}   //  Make sure bus is nit busy
//		
//	 I2C1->CR1 |=  0x100;     //start 
//	 while (!(I2C1->SR1 & 1)){}
//		 delay(2);
//	 I2C1->DR = saddr << 1;

//	 while (!(I2C1->SR1 & 2)){}  
//	 I2C1->SR2; 

//	  while (!(I2C1->SR1 & 0x80)){}
//		 I2C1->DR = maddr; 
//		while (!(I2C1->SR1 & 0x80)){}
//		 
//		I2C1->CR1 |= 0x100; 
//		while (!(I2C1->SR1 & 1)){} 
//		I2C1->DR = saddr << 1 | 1; 
//	
//		while (!(I2C1->SR1 & 2)){}
//		I2C1->CR1 &= ~0x400;  
//		I2C1->SR2;
//		
//		I2C1->CR1 |= 0x200;
//			
//		while (!(I2C1->SR1 & 0x40)){}
//    *data++ = I2C1->DR; 			
//   return 0;				  
//}

