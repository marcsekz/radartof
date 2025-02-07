/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdint.h>
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
#define LEDR_Pin GPIO_PIN_5
#define LEDR_GPIO_Port GPIOK
#define RADAR_nRST_Pin GPIO_PIN_9
#define RADAR_nRST_GPIO_Port GPIOG
#define SPI2_NSS_Pin GPIO_PIN_0
#define SPI2_NSS_GPIO_Port GPIOI
#define TOF_RST_Pin GPIO_PIN_3
#define TOF_RST_GPIO_Port GPIOD
#define TOF_LPn_Pin GPIO_PIN_2
#define TOF_LPn_GPIO_Port GPIOI
#define TOF_INT_Pin GPIO_PIN_9
#define TOF_INT_GPIO_Port GPIOB
#define LEDB_Pin GPIO_PIN_7
#define LEDB_GPIO_Port GPIOK
#define RADAR_INT_Pin GPIO_PIN_14
#define RADAR_INT_GPIO_Port GPIOG
#define TOF_PWREN_Pin GPIO_PIN_8
#define TOF_PWREN_GPIO_Port GPIOA
#define SDC_CD_Pin GPIO_PIN_10
#define SDC_CD_GPIO_Port GPIOI
#define CAM_PWDN_Pin GPIO_PIN_14
#define CAM_PWDN_GPIO_Port GPIOI
#define CAM_nRST_Pin GPIO_PIN_15
#define CAM_nRST_GPIO_Port GPIOI

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
