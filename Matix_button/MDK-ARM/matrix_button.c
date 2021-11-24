#include "matrix_button.h"

static const uint16_t g_arr_output_pin[]={GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7};
static const uint16_t g_arr_input_pin[]={GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3};

static void scan_output( uint16_t gpio_pin_low ){
	for(uint8_t row=0; row< ROW; row += 1u){
		if( g_arr_output_pin[row] == gpio_pin_low)
			continue;
		HAL_GPIO_WritePin(GPIOA, g_arr_output_pin[row], GPIO_PIN_SET);
	}
	HAL_GPIO_WritePin(GPIOA, gpio_pin_low, GPIO_PIN_RESET);
}

static uint8_t check_col_isPressed(uint16_t inp, uint8_t col){
	if( 0u == (((inp>>col)&1u) | ((inp>>(col+4u))&1u) | ((inp>>(col+8u))&1u) | ((inp>>(col+12u))&1u)) ){
		return 1u;
	}
	return 0u;
}

static void get_row_values( uint16_t *arr_rows ){
	for(uint8_t col= 0u; col< COL; col+= 1u){
		scan_output(g_arr_output_pin[col]);
		
		for(uint8_t row= 0u; row< ROW; row+= 1u){
			arr_rows[row] <<= 1u;
			arr_rows[row] |= HAL_GPIO_ReadPin(GPIOA, g_arr_input_pin[row]);
			//HAL_Delay(1000);
		}
	}
}

static func_status_t get_button_id(const uint16_t *arr_rows, uint8_t *id ){
	for(uint8_t row= 0u; row< ROW; row+= 1u)
			for(uint8_t col= 0u; col< COL; col+= 1u)
				if( check_col_isPressed(arr_rows[row], 3-col)){
					*id = row*ROW + col;
					return OKE;
				}
	return FAIL;
}
/*************** Public function *****************/
uint8_t buttonMatrix_scan(void){
	for(uint8_t row= 0u; row< ROW; row+= 1u){
		scan_output(g_arr_output_pin[row]);
		
		for(uint8_t col= 0u; col< COL; col+= 1u){
			if( 0u == HAL_GPIO_ReadPin(GPIOA, g_arr_input_pin[col])){
				HAL_Delay(10u);
				if( 0u == HAL_GPIO_ReadPin(GPIOA, g_arr_input_pin[col])){
					uint8_t buff = col*COL + row;
					
					return buff;
				}
			}
		}
	}
	return NOT_BUTTON;
}


uint8_t buttonMatrix_scan_v2(void){
	static uint16_t arr_rows[4u] ={0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF};
	static uint8_t ret = 0;
	
	get_row_values(arr_rows);
	if(OKE == get_button_id(arr_rows, &ret))
		return ret;
		
	return NOT_BUTTON;
}


