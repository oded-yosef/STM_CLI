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
#include "stm32f7xx_hal.h"

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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LTC2984_INT_Pin GPIO_PIN_3
#define LTC2984_INT_GPIO_Port GPIOE
#define SPI4_CS_Pin GPIO_PIN_4
#define SPI4_CS_GPIO_Port GPIOE
#define USER_Btn_Pin GPIO_PIN_13
#define USER_Btn_GPIO_Port GPIOC
#define USER_Btn_EXTI_IRQn EXTI15_10_IRQn
#define K_HEAT_EN_Pin GPIO_PIN_1
#define K_HEAT_EN_GPIO_Port GPIOF
#define RELAY_CONTACT_IND_Pin GPIO_PIN_2
#define RELAY_CONTACT_IND_GPIO_Port GPIOF
#define GANTRY_LED_R_EN_Pin GPIO_PIN_3
#define GANTRY_LED_R_EN_GPIO_Port GPIOF
#define GANTRY_LED_G_EN_Pin GPIO_PIN_4
#define GANTRY_LED_G_EN_GPIO_Port GPIOF
#define GANTRY_LED_B_EN_Pin GPIO_PIN_5
#define GANTRY_LED_B_EN_GPIO_Port GPIOF
#define MICRO_CLUTCH_R_EN_Pin GPIO_PIN_6
#define MICRO_CLUTCH_R_EN_GPIO_Port GPIOF
#define TIM11_CH1_FAN1_YS_Pin GPIO_PIN_7
#define TIM11_CH1_FAN1_YS_GPIO_Port GPIOF
#define TIM13_CH1_FAN2_Pin GPIO_PIN_8
#define TIM13_CH1_FAN2_GPIO_Port GPIOF
#define MICRO_CLUTCH_G_EN_Pin GPIO_PIN_9
#define MICRO_CLUTCH_G_EN_GPIO_Port GPIOF
#define MICRO_CLUTCH_B_EN_Pin GPIO_PIN_10
#define MICRO_CLUTCH_B_EN_GPIO_Port GPIOF
#define MCO_Pin GPIO_PIN_0
#define MCO_GPIO_Port GPIOH
#define FEEDER1_R_EN_Pin GPIO_PIN_0
#define FEEDER1_R_EN_GPIO_Port GPIOC
#define RMII_MDC_Pin GPIO_PIN_1
#define RMII_MDC_GPIO_Port GPIOC
#define FEEDER1_G_EN_Pin GPIO_PIN_2
#define FEEDER1_G_EN_GPIO_Port GPIOC
#define FEEDER1_B_EN_Pin GPIO_PIN_3
#define FEEDER1_B_EN_GPIO_Port GPIOC
#define ADC1_IN0_ROT_POT_PWR_Pin GPIO_PIN_0
#define ADC1_IN0_ROT_POT_PWR_GPIO_Port GPIOA
#define RMII_REF_CLK_Pin GPIO_PIN_1
#define RMII_REF_CLK_GPIO_Port GPIOA
#define RMII_MDIO_Pin GPIO_PIN_2
#define RMII_MDIO_GPIO_Port GPIOA
#define ADC1_IN3_LIN_POT_LP1_Pin GPIO_PIN_3
#define ADC1_IN3_LIN_POT_LP1_GPIO_Port GPIOA
#define ADC1_IN4_LIN_POT_LP2_Pin GPIO_PIN_4
#define ADC1_IN4_LIN_POT_LP2_GPIO_Port GPIOA
#define ADC1_IN5_LIN_POT_LP3_Pin GPIO_PIN_5
#define ADC1_IN5_LIN_POT_LP3_GPIO_Port GPIOA
#define ADC1_IN6_LIN_POT_LP4_Pin GPIO_PIN_6
#define ADC1_IN6_LIN_POT_LP4_GPIO_Port GPIOA
#define RMII_CRS_DV_Pin GPIO_PIN_7
#define RMII_CRS_DV_GPIO_Port GPIOA
#define RMII_RXD0_Pin GPIO_PIN_4
#define RMII_RXD0_GPIO_Port GPIOC
#define RMII_RXD1_Pin GPIO_PIN_5
#define RMII_RXD1_GPIO_Port GPIOC
#define LED_R1_EN_Pin GPIO_PIN_0
#define LED_R1_EN_GPIO_Port GPIOB
#define LED_G1_EN_Pin GPIO_PIN_1
#define LED_G1_EN_GPIO_Port GPIOB
#define LED_B1_EN_Pin GPIO_PIN_2
#define LED_B1_EN_GPIO_Port GPIOB
#define LMO2T_Pin GPIO_PIN_11
#define LMO2T_GPIO_Port GPIOF
#define LMO1T_Pin GPIO_PIN_15
#define LMO1T_GPIO_Port GPIOF
#define FEEDER4_G_EN_Pin GPIO_PIN_0
#define FEEDER4_G_EN_GPIO_Port GPIOG
#define FEEDER4_B_EN_Pin GPIO_PIN_1
#define FEEDER4_B_EN_GPIO_Port GPIOG
#define BRAKE_IND_Pin GPIO_PIN_9
#define BRAKE_IND_GPIO_Port GPIOE
#define K_POWER_IND_Pin GPIO_PIN_10
#define K_POWER_IND_GPIO_Port GPIOE
#define K_POWER_EN_Pin GPIO_PIN_11
#define K_POWER_EN_GPIO_Port GPIOE
#define OVEN_DOOR_CLOSE_IND_Pin GPIO_PIN_12
#define OVEN_DOOR_CLOSE_IND_GPIO_Port GPIOE
#define OVEN_DOOR_OPEN_IND_Pin GPIO_PIN_13
#define OVEN_DOOR_OPEN_IND_GPIO_Port GPIOE
#define REF_DOOR_OPEN_IND_Pin GPIO_PIN_14
#define REF_DOOR_OPEN_IND_GPIO_Port GPIOE
#define REF_DOOR_CLOSE_IND_Pin GPIO_PIN_15
#define REF_DOOR_CLOSE_IND_GPIO_Port GPIOE
#define LED_B3_EN_Pin GPIO_PIN_10
#define LED_B3_EN_GPIO_Port GPIOB
#define LED_R4_EN_Pin GPIO_PIN_11
#define LED_R4_EN_GPIO_Port GPIOB
#define LED_B4_EN_Pin GPIO_PIN_12
#define LED_B4_EN_GPIO_Port GPIOB
#define RMII_TXD1_Pin GPIO_PIN_13
#define RMII_TXD1_GPIO_Port GPIOB
#define LD3_Pin GPIO_PIN_14
#define LD3_GPIO_Port GPIOB
#define LED_G4_EN_Pin GPIO_PIN_15
#define LED_G4_EN_GPIO_Port GPIOB
#define STLK_RX_Pin GPIO_PIN_8
#define STLK_RX_GPIO_Port GPIOD
#define STLK_TX_Pin GPIO_PIN_9
#define STLK_TX_GPIO_Port GPIOD
#define FEEDER5_R_EN_Pin GPIO_PIN_2
#define FEEDER5_R_EN_GPIO_Port GPIOG
#define FEEDER5_G_EN_Pin GPIO_PIN_3
#define FEEDER5_G_EN_GPIO_Port GPIOG
#define FEEDER5_B_EN_Pin GPIO_PIN_4
#define FEEDER5_B_EN_GPIO_Port GPIOG
#define FEEDER6_R_EN_Pin GPIO_PIN_5
#define FEEDER6_R_EN_GPIO_Port GPIOG
#define USB_PowerSwitchOn_Pin GPIO_PIN_6
#define USB_PowerSwitchOn_GPIO_Port GPIOG
#define USB_OverCurrent_Pin GPIO_PIN_7
#define USB_OverCurrent_GPIO_Port GPIOG
#define FEEDER6_G_EN_Pin GPIO_PIN_8
#define FEEDER6_G_EN_GPIO_Port GPIOG
#define FEEDER2_R_EN_Pin GPIO_PIN_6
#define FEEDER2_R_EN_GPIO_Port GPIOC
#define FEEDER2_G_EN_Pin GPIO_PIN_7
#define FEEDER2_G_EN_GPIO_Port GPIOC
#define FEEDER2_B_EN_Pin GPIO_PIN_8
#define FEEDER2_B_EN_GPIO_Port GPIOC
#define FEEDER3_R_EN_Pin GPIO_PIN_9
#define FEEDER3_R_EN_GPIO_Port GPIOC
#define USB_SOF_Pin GPIO_PIN_8
#define USB_SOF_GPIO_Port GPIOA
#define USB_VBUS_Pin GPIO_PIN_9
#define USB_VBUS_GPIO_Port GPIOA
#define USB_ID_Pin GPIO_PIN_10
#define USB_ID_GPIO_Port GPIOA
#define USB_DM_Pin GPIO_PIN_11
#define USB_DM_GPIO_Port GPIOA
#define USB_DP_Pin GPIO_PIN_12
#define USB_DP_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define FEEDER3_G_EN_Pin GPIO_PIN_10
#define FEEDER3_G_EN_GPIO_Port GPIOC
#define FEEDER3_B_EN_Pin GPIO_PIN_11
#define FEEDER3_B_EN_GPIO_Port GPIOC
#define FEEDER4_R_EN_Pin GPIO_PIN_12
#define FEEDER4_R_EN_GPIO_Port GPIOC
#define LM_D1_Pin GPIO_PIN_0
#define LM_D1_GPIO_Port GPIOD
#define LM_D2_Pin GPIO_PIN_1
#define LM_D2_GPIO_Port GPIOD
#define LM_D3_Pin GPIO_PIN_2
#define LM_D3_GPIO_Port GPIOD
#define LM_D4_Pin GPIO_PIN_3
#define LM_D4_GPIO_Port GPIOD
#define LM_OT_Pin GPIO_PIN_4
#define LM_OT_GPIO_Port GPIOD
#define FEEDER6_B_EN_Pin GPIO_PIN_9
#define FEEDER6_B_EN_GPIO_Port GPIOG
#define RMII_TX_EN_Pin GPIO_PIN_11
#define RMII_TX_EN_GPIO_Port GPIOG
#define RMII_TXD0_Pin GPIO_PIN_13
#define RMII_TXD0_GPIO_Port GPIOG
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define LED_R2_EN_Pin GPIO_PIN_4
#define LED_R2_EN_GPIO_Port GPIOB
#define LED_G2_EN_Pin GPIO_PIN_5
#define LED_G2_EN_GPIO_Port GPIOB
#define LED_B2_EN_Pin GPIO_PIN_6
#define LED_B2_EN_GPIO_Port GPIOB
#define LED_R3_EN_Pin GPIO_PIN_8
#define LED_R3_EN_GPIO_Port GPIOB
#define LED_G3_EN_Pin GPIO_PIN_9
#define LED_G3_EN_GPIO_Port GPIOB
#define RELAY_AVAPOR_IND_Pin GPIO_PIN_0
#define RELAY_AVAPOR_IND_GPIO_Port GPIOE
#define LTC2984_RST_Pin GPIO_PIN_1
#define LTC2984_RST_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
