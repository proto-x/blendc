/**
  ******************************************************************************
  * File Name          : ADC.h
  * Description        : This file provides code for the configuration
  *                      of the ADC instances.
  ******************************************************************************
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __adc_H
#define __adc_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern ADC_HandleTypeDef hadc;

/* USER CODE BEGIN Private defines */
#define   R2V_10BIT(x)    (double)(x)/1023.0*3.0
/* USER CODE END Private defines */

extern void _Error_Handler(char *, int);

void MX_ADC_Init(void);

/* USER CODE BEGIN Prototypes */
void READ_ADC_DATA(void);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ adc_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
