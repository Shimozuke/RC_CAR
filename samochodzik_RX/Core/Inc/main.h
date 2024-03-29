/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

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
#define WallDet_Pin GPIO_PIN_14
#define WallDet_GPIO_Port GPIOC
#define WallDet_EXTI_IRQn EXTI15_10_IRQn
#define CE_Pin GPIO_PIN_12
#define CE_GPIO_Port GPIOB
#define IRQ_Pin GPIO_PIN_8
#define IRQ_GPIO_Port GPIOA
#define IRQ_EXTI_IRQn EXTI9_5_IRQn
#define SPI2_CSN_Pin GPIO_PIN_9
#define SPI2_CSN_GPIO_Port GPIOA
#define en12_Pin GPIO_PIN_15
#define en12_GPIO_Port GPIOA
#define en34_Pin GPIO_PIN_4
#define en34_GPIO_Port GPIOB
#define in2_Pin GPIO_PIN_6
#define in2_GPIO_Port GPIOB
#define in1_Pin GPIO_PIN_7
#define in1_GPIO_Port GPIOB
#define in4_Pin GPIO_PIN_8
#define in4_GPIO_Port GPIOB
#define in3_Pin GPIO_PIN_9
#define in3_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
