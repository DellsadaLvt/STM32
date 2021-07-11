#include "stm32f10x.h"                  // Device header

void SPI2_SETUP( void );
//void SPI2_Trasmiter( uint8_t add, uint8_t value );
void SPI2_Trasmiter( uint16_t temp );
void SPI2_Receiver( uint8_t * temp );

/*  DMA  */
void SPI_DMA_INIT( uint8_t *startAdd, uint8_t *endAdd, uint8_t Nof );
void SPI2_SendData_DMA( void );
void SPI1_SETUP( void );


