/**
  ******************************************************************************
  * File Name          : TIM.h
  * Description        : This file provides code for the configuration
  *                      of the TIM instances.
  ******************************************************************************
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __tim_H
#define __tim_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern TIM_HandleTypeDef htim15;

/* USER CODE BEGIN Private defines */
/* PWM Generation Pulse for Duty ratio. */
#define PULSE_DUTY_30    192
#define PULSE_DUTY_50    319
#define PULSE_DUTY_70    447
/* USER CODE END Private defines */

extern void _Error_Handler(char *, int);

void MX_TIM15_Init(void);
                    
void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);
                

/* USER CODE BEGIN Prototypes */
void TIM15_PWM_FAN(void);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ tim_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
