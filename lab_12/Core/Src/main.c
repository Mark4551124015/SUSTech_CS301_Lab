/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
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
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd.h"
#include "myiic.h"
#include "24cxx.h"
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
extern UART_HandleTypeDef huart1;
extern uint8_t rxBuffer[20];
extern uint8_t data[30];

//要写入到24c02的字符串数组
  const uint8_t TEXT_Buffer[]={"CS301 IIC TEST DEMO"};
//    uint8_t TEXT_Buffer[]={"CS301 IIC TEST DEMO"};
//  #define SIZE sizeof(TEXT_Buffer)
	#define SIZE 30


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
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT(&huart1,(uint8_t*)rxBuffer,1);

  uint16_t i=0;
  uint8_t datatemp[SIZE];
  LCD_Init();
  AT24CXX_Init();			//IIC初始�??

   	POINT_COLOR=RED;//设置字体为红�???
  	LCD_ShowString(40,50,200,16,16,"CS301");
  	LCD_ShowString(40,70,200,16,16,"IIC TEST");
  	LCD_ShowString(40,90,200,16,16,"KEY1:Write  KEY0:Read");	//显示提示信息
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  	while(AT24CXX_Check())
  	{
  		LCD_ShowString(40,120,200,16,16,"24C02 Check Failed!");
  		HAL_Delay(500);
  		LCD_ShowString(40,120,200,16,16,"Please Check!      ");
  		HAL_Delay(500);
  		HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);//LED0闪烁
  	}

  	LCD_ShowString(40,120,200,16,16,"24C02 Ready!");
  	POINT_COLOR=BLUE;//设置字体为蓝�??

  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
//	  LCD_ShowString(40,240,200,16,16,data);


	  		if(HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == GPIO_PIN_RESET)//KEY1按下,写入24C02
	  		{
	  			LCD_Fill(0,170,239,319,WHITE);//清除半屏
	   			LCD_ShowString(40,170,200,16,16,"Start Writing 24C02....");
//	  			AT24CXX_Write(0,(uint8_t*)TEXT_Buffer,SIZE);
	   			AT24CXX_Write(0,(uint8_t*)data,SIZE);
	  			LCD_Fill(0,170,239,319,WHITE);
	  			LCD_ShowString(40,170,200,16,16,"24C02 Write Finished!");//提示传�?�完�???
	  		}
	  		if(HAL_GPIO_ReadPin(KEY0_GPIO_Port, KEY0_Pin) == GPIO_PIN_RESET)//KEY0按下,读取字符串并显示
	  		{
	  			LCD_Fill(0,170,239,319,WHITE);
	  			LCD_ShowString(40,170,200,16,16,"Start Reading 24C02.... ");
	  			AT24CXX_Read(0,datatemp,SIZE);
	  			LCD_Fill(0,170,239,319,WHITE);
	  			LCD_ShowString(40,170,200,16,16,"The Data Read Is:  ");//提示传�?�完�???
	  			LCD_ShowString(40,190,200,16,16,datatemp);//显示读到的字符串
	  			HAL_UART_Transmit(&huart1, "The read Data is\n", 17, 0xffff);
	  			HAL_UART_Transmit(&huart1, datatemp, 30, 0xffff);
	  		}
	  		i++;
	  		HAL_Delay(10);
	  		if(i==20)
	  		{
	  			HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);//提示系统正在运行
	  			i=0;
	  		}
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
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

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
