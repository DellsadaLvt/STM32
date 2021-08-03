#include "LCD.h"



int main( void ){
	
	// setup init
	Port_init();
	Lcd_init();
	
	// loop
	while(1){
		//Hien_thi_1();
		Blink();
	}
	
}



