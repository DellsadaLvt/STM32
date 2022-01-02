#include "Menu_list.h"

#define MAIN	  		((uint8_t)0U)
#define SENSOR	  	((uint8_t)1U)
#define ACTUATOR 		((uint8_t)2U)
#define SETTING	  	((uint8_t)3U)
#define FONT	  		((uint8_t)4U)

#pragma pack(1)
typedef struct menu_list  {
	const uint8_t id;
	const struct menu_list *ptr_pre_menu;
	unsigned char title[20];
	
	unsigned char menu_list_0[20];
	const struct menu_list *ptr_menu_list_0;
	void (*ptr_func_list_0)(const uint8_t,const uint8_t*);
	
	unsigned char menu_list_1[20];
	const struct menu_list *ptr_menu_list_1;
	void (*ptr_func_list_1)(const uint8_t,const uint8_t*);
	
	unsigned char menu_list_2[20];
	const struct menu_list *ptr_menu_list_2;
	void (*ptr_func_list_2)(const uint8_t,const uint8_t*);
	
	unsigned char menu_list_3[20];
	void *ptr_menu_list_3;
} menu_list_t;
#pragma pack()

const static menu_list_t main_menu;
const static menu_list_t sensor_menu;
const static menu_list_t actuator_menu;
const static menu_list_t setting_menu;
const static menu_list_t font_menu;

static void display_temp(const uint8_t menu_id, const uint8_t *string){
	switch( menu_id ){
		case SENSOR:
			glcd_graphic_print_characters(GDRAM_LINE(2u), BEGIN_LINE + 8u, (const uint8_t*)string, strlen((char*)string));
			glcd_graphic_print_characters(GDRAM_LINE(1u), BEGIN_LINE + 8u, (const uint8_t*)"Sensor", 6u);
			break;
		
		case ACTUATOR:
			glcd_graphic_print_characters(GDRAM_LINE(2u), BEGIN_LINE + 8u, (const uint8_t*)string, strlen((char*)string));
			glcd_graphic_print_characters(GDRAM_LINE(1u), BEGIN_LINE + 8u, (const uint8_t*)"Actuator", 8u);
			break;
		
		case SETTING:
			glcd_graphic_print_characters(GDRAM_LINE(2u), BEGIN_LINE + 8u, (const uint8_t*)string, strlen((char*)string));
			glcd_graphic_print_characters(GDRAM_LINE(1u), BEGIN_LINE + 8u, (const uint8_t*)"Setting", 7u);
			break;
		
		case FONT:
			glcd_graphic_print_characters(GDRAM_LINE(2u), BEGIN_LINE + 8u, (const uint8_t*)string, strlen((char*)string));
			glcd_graphic_print_characters(GDRAM_LINE(1u), BEGIN_LINE + 8u, (const uint8_t*)"Font", 4u);
			break;
	
		default:
			break;
	}
	
	
}

/*-------- Main menu --------*/
const static menu_list_t main_menu = {
	MAIN, NULL,
	"     Main Menu",
	"   Sensor", &sensor_menu, NULL,
	"   Actuator", &actuator_menu, NULL,
	"   Setting", &setting_menu, NULL,
	"   Line3", NULL
};

/*-------- Sensor menu ---------*/
const static menu_list_t sensor_menu = {
	SENSOR, &main_menu,
	"     Sensor Menu",
	"   Temperature", NULL, &display_temp,
	"   Humidity"   , NULL, &display_temp,
	"   Encoder"    , NULL, &display_temp,
	"   Line 3", NULL
};

/*-------- Actuator menu ---------*/
const static menu_list_t actuator_menu = {
	ACTUATOR, &main_menu,
	"     Actuator Menu",
	"   Motor"					, NULL, &display_temp,
	"   Led"   					, NULL, &display_temp,
	"   Cylinder"    		, NULL, &display_temp,
	"   Line 3", NULL
};

/*-------- Setting menu ---------*/
const static menu_list_t setting_menu = {
	SETTING, &main_menu,
	"     Setting Menu",
	"   Font"					, &font_menu, NULL,
	"   Color"   			, NULL, NULL,
	"   Speed"    		, NULL, NULL,
	"   Line 3", NULL
};

const static menu_list_t font_menu = {
	FONT, &setting_menu,
	"     Font Menu",
	"   Font_Character"	, NULL, &display_temp,
	"   Font_digit"   	, NULL, &display_temp,
	"   "    						, NULL, &display_temp,
	"   Line 3", NULL
};

/*
*
* Mask functions
*
*/

static user_func_status_t user_delay( uint16_t u16_time_delay){
	if( 0u == u16_time_delay )
		return fail;
	
	HAL_Delay(u16_time_delay);
	
	return oke;
}

/*
*
* Local functions
*
*/
static user_func_status_t display_menu_list(const menu_list_t *const ptr_menu, const uint8_t u8_select ){
	if( NULL == ptr_menu)
			return oke;
	
	glcd_graphic_print_characters(GDRAM_LINE(0u), BEGIN_LINE, ptr_menu->title, strlen((char*)ptr_menu->title));
	glcd_graphic_print_characters(GDRAM_LINE(1u), BEGIN_LINE, ptr_menu->menu_list_0, strlen((char*)ptr_menu->menu_list_0));
	glcd_graphic_print_characters(GDRAM_LINE(2u), BEGIN_LINE, ptr_menu->menu_list_1, strlen((char*)ptr_menu->menu_list_1));
	glcd_graphic_print_characters(GDRAM_LINE(3u), BEGIN_LINE, ptr_menu->menu_list_2, strlen((char*)ptr_menu->menu_list_2));
	glcd_graphic_print_characters(GDRAM_LINE(0u), BEGIN_LINE + 8u, ptr_menu->menu_list_3, strlen((char*)ptr_menu->menu_list_3));
	glcd_graphic_print_characters(GDRAM_LINE(u8_select%4), BEGIN_LINE + 8u*(u8_select/4u), (const uint8_t*)">", 1u);


	return oke;
}


/*
*
* Public functions
*
*/
user_func_status_t display_main_list(const menu_handler_t *const menu){
	const static menu_list_t *ptr_menu = &main_menu;
	
	switch(menu->event){
		case NEXT_EVENT:
			switch ( menu->selection ){
				case 1u:
					if(NULL != ptr_menu->ptr_menu_list_0){
						ptr_menu = ptr_menu->ptr_menu_list_0;
						glcd_clear_graphic();
					}
					break;
				
					case 2u:
					if(NULL != ptr_menu->ptr_menu_list_1){
						ptr_menu = ptr_menu->ptr_menu_list_1;
						glcd_clear_graphic();
					}
					break;
					
					case 3u:
					if(NULL != ptr_menu->ptr_menu_list_2){
						ptr_menu = ptr_menu->ptr_menu_list_2;
						glcd_clear_graphic();
					}
					break;
				
				default:
					break;
			}
				break;
	
		case UNDO_EVENT:
			if( ptr_menu->ptr_pre_menu != NULL ){
				ptr_menu = ptr_menu->ptr_pre_menu;
				glcd_clear_graphic();
			}
			break;
			
		case CONFIRM_EVENT:
			switch ( menu->selection ){
					case 1u:
						if(NULL != ptr_menu->ptr_func_list_0){
							ptr_menu->ptr_func_list_0(ptr_menu->id, (const uint8_t*)"line 1");
						}
						break;
					
						case 2u:
							if(NULL != ptr_menu->ptr_func_list_1){
								ptr_menu->ptr_func_list_1(ptr_menu->id, (const uint8_t*)"line 2");
						}
						break;
						
						case 3u:
							if(NULL != ptr_menu->ptr_func_list_2){
								ptr_menu->ptr_func_list_2(ptr_menu->id, (const uint8_t*)"line 3");
							}
							break;
					
					default:
						break;
				}
					break;
			
		default:
			break;
	}
	
	display_menu_list(ptr_menu, menu->selection);	
	
	return oke;
}








