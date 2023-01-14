/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "nrf24l01p.h"
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

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t tx_data[NRF24L01P_PAYLOAD_LENGTH] = {0};
uint32_t jStick[2] = {50000, 50000};

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
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
  MX_DMA_Init();
  MX_SPI2_Init();
  MX_ADC1_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
  nrf24l01p_tx_init(2500, _1Mbps);

  HAL_ADC_Start_DMA(&hadc1, jStick, (uint32_t) 2);
  HAL_TIM_OC_Start(&htim1, TIM_CHANNEL_2);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if (jStick[0] > 1250 && jStick[1] > 1250 && jStick[0] < 2750 && jStick[1] < 2750)
	  {
		  tx_data[0] = 0;
	  }
	  else if (jStick[1] < 1250 && jStick[0] > 1250 && jStick[0] < 2750)
	  {
		  tx_data[0] = 1;
	  }
	  else if (jStick[0] > 2750 && jStick[1] > 1250 && jStick[1] < 2750)
	  {
		  tx_data[0] = 2;
	  }
	  else if (jStick[0] < 1250 && jStick[1] > 1250 && jStick[1] < 2750)
	  {
		  tx_data[0] = 4;
	  }
	  else if (jStick[1] > 2750 && jStick[0] > 1250 && jStick[0] < 2750)
	  {
		  tx_data[0] = 6;
	  }
	  else if (jStick[0] > 2750 && jStick[1] < 1250)
	  {
		  tx_data[0] = 3;
	  }
	  else if (jStick[0] < 1250 && jStick[1] < 1250)
	  {
		  tx_data[0] = 5;
	  }
	  else if (jStick[0] > 2750 && jStick[1] > 2750)
	  {
		  tx_data[0] = 7;
	  }
	  else if (jStick[0] < 1250 && jStick[1] > 2750)
	  {
		  tx_data[0] = 8;
	  }
	  else
	  {
		  tx_data[0] = 0;
	  }

//	  HAL_GPIO_WritePin(GPIOB, lin1_Pin, SET);
//
//	  if(HAL_GPIO_ReadPin(GPIOA, kol2_Pin) == 1)
//		  tx_data[0] = 1;
//
//	  HAL_GPIO_WritePin(GPIOB, lin1_Pin, RESET);
//	  HAL_GPIO_WritePin(GPIOB, lin2_Pin, SET);
//
//	  if (HAL_GPIO_ReadPin(GPIOA, kol3_Pin) == 1)
//	  {
//		  if(tx_data[0] == 0)
//			  tx_data[0] = 2;
//		  else if (tx_data[0] == 1)
//			  tx_data[0] = 3;
//	  }
//	  if (HAL_GPIO_ReadPin(GPIOA, kol1_Pin) == 1)
//	  {
//		  if(tx_data[0] == 0)
//			  tx_data[0] = 4;
//		  else if(tx_data[0] == 1)
//			  tx_data[0] = 5;
//	  }
//	  if (HAL_GPIO_ReadPin(GPIOA, kol2_Pin) == 1)
//	  {
//		  if (tx_data[0] == 2)
//			  tx_data[0] = 7;
//		  else if (tx_data[0] == 4)
//			  tx_data[0] = 8;
//		  else if(tx_data[0] == 0)
//			  tx_data[0] = 6;
//	  }
//
//	  HAL_GPIO_WritePin(GPIOB, lin2_Pin, RESET);


	  nrf24l01p_tx_transmit(tx_data);
	  HAL_Delay(100);
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

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
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == NRF24L01P_IRQ_PIN_NUMBER)
		nrf24l01p_tx_irq(); // clear interrupt flag
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
