/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    stm32f1xx_it.c
 * @brief   Interrupt Service Routines.
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

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_it.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
extern uint8_t rxBuffer[20];
extern unsigned char Rx_Data[1024];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart1_tx;
extern UART_HandleTypeDef huart1;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M3 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
 * @brief This function handles Non maskable interrupt.
 */
void NMI_Handler(void) {
    /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

    /* USER CODE END NonMaskableInt_IRQn 0 */
    /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
    while (1) {
    }
    /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
 * @brief This function handles Hard fault interrupt.
 */
void HardFault_Handler(void) {
    /* USER CODE BEGIN HardFault_IRQn 0 */

    /* USER CODE END HardFault_IRQn 0 */
    while (1) {
        /* USER CODE BEGIN W1_HardFault_IRQn 0 */
        /* USER CODE END W1_HardFault_IRQn 0 */
    }
}

/**
 * @brief This function handles Memory management fault.
 */
void MemManage_Handler(void) {
    /* USER CODE BEGIN MemoryManagement_IRQn 0 */

    /* USER CODE END MemoryManagement_IRQn 0 */
    while (1) {
        /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
        /* USER CODE END W1_MemoryManagement_IRQn 0 */
    }
}

/**
 * @brief This function handles Prefetch fault, memory access fault.
 */
void BusFault_Handler(void) {
    /* USER CODE BEGIN BusFault_IRQn 0 */

    /* USER CODE END BusFault_IRQn 0 */
    while (1) {
        /* USER CODE BEGIN W1_BusFault_IRQn 0 */
        /* USER CODE END W1_BusFault_IRQn 0 */
    }
}

/**
 * @brief This function handles Undefined instruction or illegal state.
 */
void UsageFault_Handler(void) {
    /* USER CODE BEGIN UsageFault_IRQn 0 */

    /* USER CODE END UsageFault_IRQn 0 */
    while (1) {
        /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
        /* USER CODE END W1_UsageFault_IRQn 0 */
    }
}

/**
 * @brief This function handles System service call via SWI instruction.
 */
void SVC_Handler(void) {
    /* USER CODE BEGIN SVCall_IRQn 0 */

    /* USER CODE END SVCall_IRQn 0 */
    /* USER CODE BEGIN SVCall_IRQn 1 */

    /* USER CODE END SVCall_IRQn 1 */
}

/**
 * @brief This function handles Debug monitor.
 */
void DebugMon_Handler(void) {
    /* USER CODE BEGIN DebugMonitor_IRQn 0 */

    /* USER CODE END DebugMonitor_IRQn 0 */
    /* USER CODE BEGIN DebugMonitor_IRQn 1 */

    /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
 * @brief This function handles Pendable request for system service.
 */
void PendSV_Handler(void) {
    /* USER CODE BEGIN PendSV_IRQn 0 */

    /* USER CODE END PendSV_IRQn 0 */
    /* USER CODE BEGIN PendSV_IRQn 1 */

    /* USER CODE END PendSV_IRQn 1 */
}

/**
 * @brief This function handles System tick timer.
 */
void SysTick_Handler(void) {
    /* USER CODE BEGIN SysTick_IRQn 0 */

    /* USER CODE END SysTick_IRQn 0 */
    HAL_IncTick();
    /* USER CODE BEGIN SysTick_IRQn 1 */

    /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f1xx.s).                    */
/******************************************************************************/

/**
 * @brief This function handles EXTI line0 interrupt.
 */
void EXTI0_IRQHandler(void) {
    /* USER CODE BEGIN EXTI0_IRQn 0 */

    /* USER CODE END EXTI0_IRQn 0 */
    HAL_GPIO_EXTI_IRQHandler(KEY_WK_Pin);
    /* USER CODE BEGIN EXTI0_IRQn 1 */

    /* USER CODE END EXTI0_IRQn 1 */
}

/**
 * @brief This function handles DMA1 channel4 global interrupt.
 */
void DMA1_Channel4_IRQHandler(void) {
    /* USER CODE BEGIN DMA1_Channel4_IRQn 0 */

    /* USER CODE END DMA1_Channel4_IRQn 0 */
    HAL_DMA_IRQHandler(&hdma_usart1_tx);
    /* USER CODE BEGIN DMA1_Channel4_IRQn 1 */

    /* USER CODE END DMA1_Channel4_IRQn 1 */
}

/**
 * @brief This function handles DMA1 channel5 global interrupt.
 */
void DMA1_Channel5_IRQHandler(void) {
    /* USER CODE BEGIN DMA1_Channel5_IRQn 0 */

    /* USER CODE END DMA1_Channel5_IRQn 0 */
    HAL_DMA_IRQHandler(&hdma_usart1_rx);
    /* USER CODE BEGIN DMA1_Channel5_IRQn 1 */

    /* USER CODE END DMA1_Channel5_IRQn 1 */
}

/**
 * @brief This function handles EXTI line[9:5] interrupts.
 */
void EXTI9_5_IRQHandler(void) {
    /* USER CODE BEGIN EXTI9_5_IRQn 0 */

    /* USER CODE END EXTI9_5_IRQn 0 */
    HAL_GPIO_EXTI_IRQHandler(KEY0_Pin);
    /* USER CODE BEGIN EXTI9_5_IRQn 1 */

    /* USER CODE END EXTI9_5_IRQn 1 */
}

/**
 * @brief This function handles USART1 global interrupt.
 */
void USART1_IRQHandler(void) {
    /* USER CODE BEGIN USART1_IRQn 0 */
    printf("111");
    /* USER CODE END USART1_IRQn 0 */
    HAL_UART_IRQHandler(&huart1);
    /* USER CODE BEGIN USART1_IRQn 1 */
    HAL_UART_Receive_IT(&huart1, (uint8_t*) rxBuffer, 1);

    /* USER CODE END USART1_IRQn 1 */
}

/**
 * @brief This function handles EXTI line[15:10] interrupts.
 */
void EXTI15_10_IRQHandler(void) {
    /* USER CODE BEGIN EXTI15_10_IRQn 0 */

    /* USER CODE END EXTI15_10_IRQn 0 */
    HAL_GPIO_EXTI_IRQHandler(KEY1_Pin);
    /* USER CODE BEGIN EXTI15_10_IRQn 1 */

    /* USER CODE END EXTI15_10_IRQn 1 */
}

/* USER CODE BEGIN 1 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART1) {
        static unsigned char uRx_Data[1024] = {0};
        static unsigned char uLength = 0;
        if (rxBuffer[0] == '\n') {
            LCD_Clear(WHITE);
            uLength = 0;
            memcpy(Rx_Data, uRx_Data,sizeof(Rx_Data));
        } else {
            uRx_Data[uLength] = rxBuffer[0];
            uLength++;
        }
    }
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	HAL_Delay(500);

	POINT_COLOR = RED;
    char output[50];
	switch (GPIO_Pin) {
	case KEY0_Pin:
			HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
			 sprintf(output, "KEY0 Pressed");
			HAL_UART_Transmit(&huart1, output, strlen(output), 0xffff);
		break;
	case KEY1_Pin:
            sprintf(output, "KEY1 Pressed");
			HAL_UART_Transmit(&huart1, output, strlen(output), 0xffff);
		break;
	case KEY_WK_Pin:
			HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
			HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
			HAL_Delay(100);
			HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
			HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
			HAL_Delay(100);
			HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
			HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
			HAL_Delay(100);
			HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
			HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
		break;
	default:
		break;

	}
}
/* USER CODE END 1 */
