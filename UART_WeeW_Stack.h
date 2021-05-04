/*
Welcome to the WeeW - Electronics
follow us on our Channel : https://www.youtube.com/channel/UCnTWd_4LwCEcAw19Jds0Vjg
The topic of this program is to:
- Simple init setup for UART
- Send a char using UART
- Recieve Char using UART
Related explanatory video : https://youtu.be/TDoHlG0CK-8


*/

#include "stm32f10x.h"    
#include "gp_drive.h" 
//#include "systick_time.h"



void UART_SETUP( void );

void transmit_data( void );
