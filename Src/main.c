/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f0xx_hal.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
uint16_t set_mode;
uint16_t set_humidity;
uint32_t time_press;
uint32_t time_press_limit;
HAL_StatusTypeDef uart_status = HAL_ERROR;
uint8_t uart_data[10] = {0, };
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE  
{
    /* Place your implementation of fputc here */
    /* e.g. write a character to the USART */
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 100);


    return ch;
}
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	static int pressed = -1;  // -1 means not pressed
	set_humidity = 40;
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

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
  MX_USART1_UART_Init();
  MX_I2C1_Init();
  MX_I2C2_Init();
  MX_TIM15_Init();
  MX_ADC_Init();
  /* USER CODE BEGIN 2 */
	//I2C_MMA8653_INIT();
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9 | GPIO_PIN_8, GPIO_PIN_SET);
	HAL_Delay(500);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9 | GPIO_PIN_8, GPIO_PIN_RESET);
	HAL_Delay(500);
	
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		//uart_status = HAL_UART_Receive(&huart1, uart_data, 10, 1000);
			
		if (uart_status == HAL_OK && uart_data[0] != 0)
		{
			HAL_UART_Transmit_IT(&huart1, uart_data, 1);
			//printf("Fail it!\r\n");
			HAL_Delay(500);
			uart_data[0] = 0;
		}
		else
		{
			printf("Fail it!\r\n");
		}
		
		//READ_ADC_DATA();
		HAL_Delay(100);

		//I2C1_MMA8653_DATA();
		//HAL_Delay(100);
		
		TIM15_PWM_FAN();
		
		if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0) == GPIO_PIN_RESET)
   {
		 __HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_1, PULSE_DUTY_30);
		 TIM15_PWM_FAN();
   }
		
		if (set_mode == 1) 
		{
			if (set_mode == 1 && pressed == -1)
			{
				time_press = HAL_GetTick();
				time_press_limit = time_press + 5000;
				pressed = 0;
			}
			else if (pressed == 0 && HAL_GetTick() < time_press_limit)
			{
				if (set_mode == 1 && set_humidity <= 70){
					set_humidity += 10;
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);
					HAL_Delay(100);
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);
					HAL_Delay(100);
				}
			}
			printf("Button %d	 set %d	time = %d\r\n", set_mode, set_humidity, HAL_GetTick());
		HAL_Delay(100);
			set_mode = 0;
		}

		if (pressed == 0 && time_press_limit != 0 && HAL_GetTick() > time_press_limit) 
		{
			time_press = 0;
			time_press_limit = 0;
			pressed = -1;
			set_mode = 0;
			set_humidity = 40;
		}
		
		
		
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

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI14|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSI14State = RCC_HSI14_ON;
  RCC_OscInitStruct.HSI14CalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_I2C1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_SYSCLK;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_SYSCLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */
/**
  * @brief  EXTI line detection callback.
  * @param  GPIO_Pin Specifies the port pin connected to corresponding EXTI line.
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  switch (GPIO_Pin)
	{
		case GPIO_PIN_0: set_mode = 1;
										 HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
										 HAL_Delay(100);
										 //HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);
										 //HAL_Delay(100);
										 break;
		case GPIO_PIN_2: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);
										 HAL_Delay(100);
										 HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
										 HAL_Delay(100);
										 break;
	}
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
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
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
