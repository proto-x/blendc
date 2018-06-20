/**
  ******************************************************************************
  * File Name          : I2C.h
  * Description        : This file provides code for the configuration
  *                      of the I2C instances.
  ******************************************************************************
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __i2c_H
#define __i2c_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c2;

/* USER CODE BEGIN Private defines */
/*Common addresses definition for accelereomter MMA8653. */
#define MMA8653_ADDR        (0x1DU >> 1)

#define MMA8653_REG1_CTRL		0x2AU		// Auto-Wake Rate, Output Data Rate, Fast-Read mode, Active mode
#define MMA8653_ODR_800Hz   0x00U		// 0 0 DR2 DR1 DR0 0 F_READ ACTIVE
#define MMA8653_CFG_FS_2G   0x00U
#define MMA8653_XOUT_MSB    0x01U
#define MMA8653_XOUT_LSB    0x02U
#define MMA8653_YOUT_MSB   	0x03U
#define MMA8653_YOUT_LSB   	0x04U
#define MMA8653_ZOUT_MSB    0x05U
#define MMA8653_ZOUT_LSB    0x06U

/* Mode for MMA8653. */
#define STANDBY_MODE 0u
#define ACTIVE_MODE  1u

/*Common addresses definition for humidity and temperature sensor SHT30. */
#define SHT30_ADDR        	(0x44U >> 1)		// ADDR connected to logic LOW

#define SHT30_CLKSTR_H_MSB	0x2C // measurement: clock stretching, high repeatability
#define SHT30_CLKSTR_H_LSB	0x06

/* USER CODE END Private defines */

extern void _Error_Handler(char *, int);

void MX_I2C1_Init(void);
void MX_I2C2_Init(void);

/* USER CODE BEGIN Prototypes */
void I2C1_MMA8653_WRITE(uint8_t addr, uint8_t val);
void I2C1_MMA8653_READ(uint8_t addr);
void I2C1_MMA8653_INIT(void);
void I2C1_MMA8653_DATA(void);

void I2C2_SHT30_WRITE(uint8_t addr, uint8_t val);
void I2C2_SHT30_READ(uint8_t addr);
void I2C2_SHT30_INIT(void);
void I2C2_SHT30_DATA(void);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ i2c_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
