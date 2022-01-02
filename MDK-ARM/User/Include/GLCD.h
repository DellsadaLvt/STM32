#ifndef _USER_GLCD_H_

#define _USER_GLCD_H_


#include "user_err.h"
#include "gpio.h"
#include <stdio.h>
#include <string.h>

#ifndef LINE_0_BASE_DDRAM
	#define LINE_0_BASE_DDRAM							((uint8_t)0x80)  
#endif

#ifndef LINE_1_BASE_DDRAM
	#define LINE_1_BASE_DDRAM							((uint8_t)0x90)  
#endif

#ifndef LINE_2_BASE_DDRAM
	#define LINE_2_BASE_DDRAM							((uint8_t)0x88)  
#endif

#ifndef LINE_3_BASE_DDRAM
	#define LINE_3_BASE_DDRAM							((uint8_t)0x98)  
#endif



#ifndef HORIZONTAL_ADDRESS_BASE
	#define HORIZONTAL_ADDRESS_BASE			((uint8_t)0x80)  
#endif

#ifndef VERTICAL_ADDRESS_BASE
	#define VERTICAL_ADDRESS_BASE				((uint8_t)0x80)  
#endif

#ifndef GDRAM_LINE
	#define GDRAM_LINE(xx) 		((uint8_t)(VERTICAL_ADDRESS_BASE + 8u*(uint8_t)(xx)))  // xx from 0-> 3
#endif

#ifndef BEGIN_LINE
	#define BEGIN_LINE 		HORIZONTAL_ADDRESS_BASE
#endif


/* General functions */
user_func_status_t glcd_init( void );
user_func_status_t glcd_start(void);
user_func_status_t glcd_stop(void);

/* Basic instructions */
user_func_status_t glcd_entry_basic_mode( void );
user_func_status_t glcd_display_clear(void);
user_func_status_t glcd_basic_print_string(const uint8_t position, const uint8_t *const str, const uint8_t str_len);

/* Graphic functions */
user_func_status_t glcd_entry_graphic_mode( void );
user_func_status_t glcd_clear_graphic(void);
user_func_status_t glcd_print_image(const unsigned char *const image);
user_func_status_t glcd_graphic_print_characters(const uint8_t vertical, const uint8_t horizontal, const uint8_t *str, unsigned char str_len);
user_func_status_t glcd_graphic_print_digit(const uint8_t vertical, const uint8_t horizontal, const uint8_t *str, unsigned char str_len);

/* Test function */
user_func_status_t glcd_test(void);
user_func_status_t glcd_test_CGRAM(void);
user_func_status_t glcd_test_graphic_mode(void);

#endif   /* _USER_GLCD_H_ */














