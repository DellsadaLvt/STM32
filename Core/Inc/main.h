/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define inp_matrix_button_Pin GPIO_PIN_0
#define inp_matrix_button_GPIO_Port GPIOA
#define inp_matrix_buttonA1_Pin GPIO_PIN_1
#define inp_matrix_buttonA1_GPIO_Port GPIOA
#define inp_matrix_buttonA2_Pin GPIO_PIN_2
#define inp_matrix_buttonA2_GPIO_Port GPIOA
#define inp_matrix_buttonA3_Pin GPIO_PIN_3
#define inp_matrix_buttonA3_GPIO_Port GPIOA
#define output_matrix_button_Pin GPIO_PIN_4
#define output_matrix_button_GPIO_Port GPIOA
#define output_matrix_buttonA5_Pin GPIO_PIN_5
#define output_matrix_buttonA5_GPIO_Port GPIOA
#define output_matrix_buttonA6_Pin GPIO_PIN_6
#define output_matrix_buttonA6_GPIO_Port GPIOA
#define output_matrix_buttonA7_Pin GPIO_PIN_7
#define output_matrix_buttonA7_GPIO_Port GPIOA
#define glcd_clk_Pin GPIO_PIN_0
#define glcd_clk_GPIO_Port GPIOB
#define glcd_data_Pin GPIO_PIN_1
#define glcd_data_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
