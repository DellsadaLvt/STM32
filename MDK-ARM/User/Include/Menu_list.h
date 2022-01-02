#ifndef _MENU_LIST_H_

#define _MENU_LIST_H_

#include "user_err.h"
#include "GLCD.h"
#include <string.h>

#ifndef FIRST_SUBTITLE 
	#define FIRST_SUBTITLE   		((uint8_t)1u)
	#define LAST_SUBTITLE    		((uint8_t)4u)
#endif

#ifndef UP_BUTTON
	#define UP_BUTTON				 		((uint8_t)3u)
	#define DOWN_BUTTON			 		((uint8_t)7u)
	#define OKE_BUTTON			 		((uint8_t)14u)
	#define LEFT_BUTTON			 		((uint8_t)11u)
	#define RIGHT_BUTTON			 	((uint8_t)15u)
	#define STEP_SUBTITLE    		((uint8_t)1u)
#endif

#ifndef EVENT_BUTTON
	#define NONE_EVENT			((uint8_t)0u)
	#define UNDO_EVENT			((uint8_t)1u)
	#define NEXT_EVENT			((uint8_t)2u)
	#define CONFIRM_EVENT 	((uint8_t)3u)
#endif

typedef struct {
	uint8_t selection:3;
	uint8_t event:2;
} menu_handler_t;

user_func_status_t display_main_list(const menu_handler_t *const menu);



#endif   /* _MENU_LIST_H_ */





