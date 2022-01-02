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
#include "tim.h"
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
volatile float g_timer_count = 0u;
volatile uint8_t led_no = 0u;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
HAL_StatusTypeDef CAN_Transmit(void);
HAL_StatusTypeDef CAN_Filter_Config( void );
HAL_StatusTypeDef LED_manage_output( uint8_t led_no );
HAL_StatusTypeDef Send_response( uint32_t SidId );
HAL_StatusTypeDef CAN_Transmit_request(void);
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
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start_IT(&htim4);
	
	CAN_Filter_Config();
	if( HAL_OK != HAL_CAN_ActivateNotification(&hcan, CAN_IT_TX_MAILBOX_EMPTY | CAN_IT_RX_FIFO0_MSG_PENDING | CAN_IT_BUSOFF)){
		Error_Handler();
	}    
	if( HAL_OK != HAL_CAN_Start(&hcan)){ // put can in normal mode
		Error_Handler();
	}
	
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
	
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if( htim == &htim4 ){
		g_timer_count += 1u;
		if( 4u == g_timer_count){
			CAN_Transmit_request();
		}
		else{
			CAN_Transmit();
		}
	}
}

HAL_StatusTypeDef CAN_Transmit_request(void){
	uint8_t msg= 0u; // no meaning for data frame
	uint32_t mail_box;
	
	CAN_TxHeaderTypeDef Tx_header;
	Tx_header.DLC = 2u; // note(sender) request the receiver send 2bytes of reply
	Tx_header.IDE = CAN_ID_STD;
	Tx_header.StdId = 0x651;
	Tx_header.RTR = CAN_RTR_REMOTE;
	
	if( HAL_OK != HAL_CAN_AddTxMessage(&hcan, &Tx_header, &msg, &mail_box)){
		Error_Handler();
	}
	
	return HAL_OK;
}

HAL_StatusTypeDef CAN_Transmit(void){
	uint8_t msg= ++led_no;
	uint32_t mail_box;
	
	CAN_TxHeaderTypeDef Tx_header;
	Tx_header.DLC = 1u; // Transmit one bytes
	Tx_header.IDE = CAN_ID_STD;
	Tx_header.StdId = 0x65D;
	Tx_header.RTR = CAN_RTR_DATA;
	
	if( HAL_OK != HAL_CAN_AddTxMessage(&hcan, &Tx_header, &msg, &mail_box)){
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

void HAL_CAN_TxMailbox0CompleteCallback(CAN_HandleTypeDef *hcan){
  // completed transmition 
}
void HAL_CAN_TxMailbox1CompleteCallback(CAN_HandleTypeDef *hcan){
	// completed transmition 
}
void HAL_CAN_TxMailbox2CompleteCallback(CAN_HandleTypeDef *hcan){
	// completed transmition 
}
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan){
	CAN_RxHeaderTypeDef Rx_header;
	uint8_t buff[10u];
	
	/* get message into buff */
	if( HAL_OK != HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &Rx_header, buff)){
		Error_Handler();
	}
	
	/* Filter message */
	if((Rx_header.StdId == 0x65D) && (Rx_header.RTR == 0u)){
		// data from note 1 to note 2
		LED_manage_output( buff[0] );
	}
	else if((Rx_header.StdId == 0x651) && (Rx_header.RTR == 1u)){
		// remote frame from note 1 to note 2
		Send_response(Rx_header.StdId);
	}
	else if((Rx_header.StdId == 0x651) && (Rx_header.RTR == 0u)){
		// this is the reply (data frame) by note 2 to note 1
	}
	
}
void HAL_CAN_ErrorCallback(CAN_HandleTypeDef *hcan){
	// error happen
}

HAL_StatusTypeDef LED_manage_output( uint8_t led_no ){
	switch(led_no){
		case 0:
			// turn led 0
			break;
		case 1u:
			// turn led 1
			break;
		default:
			break;
	}
	
	return HAL_OK;
}

HAL_StatusTypeDef Send_response( uint32_t SidId ){
	uint8_t msg[] = { 0xAB, 0xCD };
	uint32_t mail_box;
	
	CAN_TxHeaderTypeDef Tx_header;
	Tx_header.DLC = 2u; // Transmit one bytes
	Tx_header.IDE = CAN_ID_STD;
	Tx_header.StdId = SidId;
	Tx_header.RTR = CAN_RTR_DATA;
	
	if( HAL_OK != HAL_CAN_AddTxMessage(&hcan, &Tx_header, msg, &mail_box)){
		Error_Handler();
	}
	
	return HAL_OK;
}
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
