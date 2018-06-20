/**
  ******************************************************************************
  * File Name          : I2C.c
  * Description        : This file provides code for the configuration
  *                      of the I2C instances.
  ******************************************************************************
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "i2c.h"

#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c2;

/* I2C1 init function */
void MX_I2C1_Init(void)
{

  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x2010091A;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure Analogue filter 
    */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure Digital filter 
    */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}
/* I2C2 init function */
void MX_I2C2_Init(void)
{

  hi2c2.Instance = I2C2;
  hi2c2.Init.Timing = 0x2010091A;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure Analogue filter 
    */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c2, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure Digital filter 
    */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c2, 0) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

void HAL_I2C_MspInit(I2C_HandleTypeDef* i2cHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(i2cHandle->Instance==I2C1)
  {
  /* USER CODE BEGIN I2C1_MspInit 0 */

  /* USER CODE END I2C1_MspInit 0 */
  
    /**I2C1 GPIO Configuration    
    PB6     ------> I2C1_SCL
    PB7     ------> I2C1_SDA 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF1_I2C1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* I2C1 clock enable */
    __HAL_RCC_I2C1_CLK_ENABLE();
  /* USER CODE BEGIN I2C1_MspInit 1 */

  /* USER CODE END I2C1_MspInit 1 */
  }
  else if(i2cHandle->Instance==I2C2)
  {
  /* USER CODE BEGIN I2C2_MspInit 0 */

  /* USER CODE END I2C2_MspInit 0 */
  
    /**I2C2 GPIO Configuration    
    PF6     ------> I2C2_SCL
    PF7     ------> I2C2_SDA 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    /* I2C2 clock enable */
    __HAL_RCC_I2C2_CLK_ENABLE();
  /* USER CODE BEGIN I2C2_MspInit 1 */

  /* USER CODE END I2C2_MspInit 1 */
  }
}

void HAL_I2C_MspDeInit(I2C_HandleTypeDef* i2cHandle)
{

  if(i2cHandle->Instance==I2C1)
  {
  /* USER CODE BEGIN I2C1_MspDeInit 0 */

  /* USER CODE END I2C1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_I2C1_CLK_DISABLE();
  
    /**I2C1 GPIO Configuration    
    PB6     ------> I2C1_SCL
    PB7     ------> I2C1_SDA 
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6|GPIO_PIN_7);

  /* USER CODE BEGIN I2C1_MspDeInit 1 */

  /* USER CODE END I2C1_MspDeInit 1 */
  }
  else if(i2cHandle->Instance==I2C2)
  {
  /* USER CODE BEGIN I2C2_MspDeInit 0 */

  /* USER CODE END I2C2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_I2C2_CLK_DISABLE();
  
    /**I2C2 GPIO Configuration    
    PF6     ------> I2C2_SCL
    PF7     ------> I2C2_SDA 
    */
    HAL_GPIO_DeInit(GPIOF, GPIO_PIN_6|GPIO_PIN_7);

  /* USER CODE BEGIN I2C2_MspDeInit 1 */

  /* USER CODE END I2C2_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */

/* MMA8653 CODE BEGIN */

void I2C1_MMA8653_WRITE(uint8_t addr, uint8_t val)
{
	uint8_t i2c_config[] = { addr, val };

	HAL_I2C_Master_Transmit(&hi2c1, MMA8653_ADDR, i2c_config, sizeof(i2c_config), 1000);
	
	HAL_Delay(100);
}

void I2C1_MMA8653_READ(uint8_t addr)
{
	uint8_t i2c_config[] = { addr };

	HAL_I2C_Master_Receive(&hi2c1, MMA8653_ADDR, i2c_config, sizeof(i2c_config), 50);
	
	HAL_Delay(100);
}

void I2C1_MMA8653_INIT(void)
{
	uint8_t MMA7660_MODE[2] = { STANDBY_MODE, ACTIVE_MODE | MMA8653_ODR_800Hz };
	
	HAL_I2C_Mem_Write(&hi2c1, MMA8653_ADDR, MMA8653_REG1_CTRL, 1, &MMA7660_MODE[0], 1, 10000);
	HAL_Delay(100);		
	I2C1_MMA8653_WRITE(MMA8653_REG1_CTRL, MMA8653_CFG_FS_2G);
	HAL_Delay(100);
	HAL_I2C_Mem_Write(&hi2c1, MMA8653_ADDR, MMA8653_REG1_CTRL, 1, &MMA7660_MODE[1], 1, 10000);
	HAL_Delay(100);			
}

void I2C1_MMA8653_DATA(void)
{
	uint8_t MMA8653_XDATA[2] = { 0, };
	uint8_t MMA8653_YDATA[2] = { 0, };
	uint8_t MMA8653_ZDATA[2] = { 0, };
	uint8_t MMA8653_DATA[3] = { 0, };	
	
	HAL_I2C_Mem_Read(&hi2c1, MMA8653_ADDR, MMA8653_XOUT_MSB, 1, &MMA8653_XDATA[0], 1, 1000);
	HAL_Delay(100);	
	HAL_I2C_Mem_Read(&hi2c1, MMA8653_ADDR, MMA8653_XOUT_LSB, 1, &MMA8653_XDATA[1], 1, 1000);
	HAL_Delay(100);	
	
	HAL_I2C_Mem_Read(&hi2c1, MMA8653_ADDR, MMA8653_YOUT_MSB, 1, &MMA8653_YDATA[0], 1, 1000);
	HAL_Delay(100);	
	HAL_I2C_Mem_Read(&hi2c1, MMA8653_ADDR, MMA8653_YOUT_LSB, 1, &MMA8653_YDATA[1], 1, 1000);
	HAL_Delay(100);	
	
	HAL_I2C_Mem_Read(&hi2c1, MMA8653_ADDR, MMA8653_ZOUT_MSB, 1, &MMA8653_ZDATA[0], 1, 1000);
	HAL_Delay(100);	
	HAL_I2C_Mem_Read(&hi2c1, MMA8653_ADDR, MMA8653_ZOUT_LSB, 1, &MMA8653_ZDATA[1], 1, 1000);
	HAL_Delay(100);	
	
	MMA8653_DATA[0] = MMA8653_XDATA[0] << 8 | MMA8653_XDATA[1];
	MMA8653_DATA[1] = MMA8653_YDATA[0] << 8 | MMA8653_YDATA[1];
	MMA8653_DATA[2] = MMA8653_ZDATA[0] << 8 | MMA8653_ZDATA[1];
	
	printf("X : %d, Y : %d, Z : %d \r\n", MMA8653_DATA[0], MMA8653_DATA[1], MMA8653_DATA[2]);
	HAL_Delay(100);
}

/* SHT30 CODE BEGIN */

void I2C2_SHT30_WRITE(uint8_t addr, uint8_t val)
{
	uint8_t i2c_config[] = { addr, val };

	HAL_I2C_Master_Transmit(&hi2c2, SHT30_ADDR, i2c_config, sizeof(i2c_config), 1000);
	
	HAL_Delay(100);
}

void I2C2_SHT30_READ(uint8_t addr)
{
	uint8_t i2c_config[] = { addr };

	HAL_I2C_Master_Receive(&hi2c2, SHT30_ADDR, i2c_config, sizeof(i2c_config), 50);
	
	HAL_Delay(100);
}

void I2C2_SHT30_INIT(void)
{
	uint8_t SHT30_SINGLE_SHOT[2] = { SHT30_CLKSTR_H_MSB, SHT30_CLKSTR_H_LSB }; // Single Shot Data Acquisition Mode
	
	HAL_I2C_Master_Transmit(&hi2c2, SHT30_ADDR, SHT30_SINGLE_SHOT, sizeof(SHT30_SINGLE_SHOT), 1000);
	HAL_Delay(100);
}

void I2C2_SHT30_DATA(void)
{
	uint8_t SHT30_DATA[6] = { 0, };	// TEMP_MSB TEMP_LSB TEMP_CRC HUMD_MSB HUMD_LSB HUMD_CRC
	float 	SHT30_TEMPC 	= 0.0;
	float 	SHT30_HUMD 		= 0.0;
	
	HAL_I2C_Master_Receive(&hi2c2, SHT30_ADDR, SHT30_DATA, sizeof(SHT30_DATA), 1000);
	HAL_Delay(100);	
	
	SHT30_TEMPC = ((((SHT30_DATA[0] * 256.0) + SHT30_DATA[1]) * 175) / 65535.0) - 45;
	SHT30_HUMD = ((((SHT30_DATA[3] * 256.0) + SHT30_DATA[4]) * 100) / 65535.0);
	
	printf("Temp : %lf, Humd : %lf \r\n", SHT30_TEMPC, SHT30_HUMD);
	HAL_Delay(100);
}
/* USER CODE END 1 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
