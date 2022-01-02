/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "can.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
HAL_StatusTypeDef CAN_Transmit(void);
HAL_StatusTypeDef CAN_Rx(void);
HAL_StatusTypeDef CAN_Filter_Config( void );
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_CAN_Init();
  /* USER CODE BEGIN 2 */
	CAN_Filter_Config();
	HAL_CAN_Start(&hcan); // put can in normal mode
	CAN_Transmit();
	CAN_Rx();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
HAL_StatusTypeDef CAN_Transmit(void){
	uint8_t msg[]= "hello";
	uint32_t mail_box;
	
	CAN_TxHeaderTypeDef Tx_header;
	Tx_header.DLC = 5u; // Transmit 5bytes "hello"
	Tx_header.IDE = CAN_ID_STD;
	Tx_header.StdId = 0x65D;
	Tx_header.RTR = CAN_RTR_DATA;
	
	if( HAL_OK != HAL_CAN_AddTxMessage(&hcan, &Tx_header, msg, &mail_box)){
		Error_Handler();
	}
	
	while(HAL_CAN_IsTxMessagePending(&hcan, mail_box));
	return HAL_OK;
}

HAL_StatusTypeDef CAN_Rx(void){
	CAN_RxHeaderTypeDef Rx_header;
	uint8_t buff[10u];
	
	/* wait until rx_fifo_0 has least one message */
	while( 0u == HAL_CAN_GetRxFifoFillLevel(&hcan, CAN_RX_FIFO0));
	
	/* get message into buff */
	if( HAL_OK != HAL_CAN_GetRxMessage(&hcan, CAN_RX_FIFO0, &Rx_header, buff)){
		Error_Handler();
	}
	
	return HAL_OK;
}

HAL_StatusTypeDef CAN_Filter_Config( void ){
	CAN_FilterTypeDef Rx_filter_init;
	
	Rx_filter_init.FilterActivation = ENABLE;
	Rx_filter_init.FilterBank = 0U;
	Rx_filter_init.FilterFIFOAssignment = CAN_RX_FIFO0;
	Rx_filter_init.FilterIdHigh = 0x0000;
	Rx_filter_init.FilterIdLow = 0x0000;
	Rx_filter_init.FilterMaskIdHigh = 0x0000;
	Rx_filter_init.FilterMaskIdLow = 0x0000;
	Rx_filter_init.FilterMode = CAN_FILTERMODE_IDMASK;
	Rx_filter_init.FilterScale = CAN_FILTERSCALE_32BIT;
	
	HAL_CAN_ConfigFilter(&hcan, &Rx_filter_init);
	
	return HAL_OK;
}
/* after CAN has initied program will jum to this function HAL_CAN_MspInit */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
