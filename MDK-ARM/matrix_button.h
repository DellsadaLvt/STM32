#ifndef __BUTTON_MATRIX_H_

#define __BUTTON_MATRIX_H_

#include "gpio.h"

#define ROW 					((uint8_t)4U)
#define COL 					((uint8_t)4U)
#define NOT_BUTTON		(0xFF)

typedef enum{
	OKE,
	FAIL
} func_status_t;

uint8_t buttonMatrix_scan(void);
uint8_t buttonMatrix_scan_v2(void);

#endif /* __BUTTON_MATRIX_H_ */








