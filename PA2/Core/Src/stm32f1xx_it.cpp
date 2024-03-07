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

#include <stdio.h>

#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "game.h"
#include "led.h"
#include "string.h"
#include "utils.h"

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
typedef enum PIN { KEY0 = 0, KEY_WK = 1, KEY1 = 2 } PIN;

PIN current;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern UART_HandleTypeDef huart1;
extern IWDG_HandleTypeDef hiwdg;
extern LED leddev;
extern Game game;
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
 * @brief This function handles TIM2 global interrupt.
 */
void TIM2_IRQHandler(void) {
    /* USER CODE BEGIN TIM2_IRQn 0 */

    /* USER CODE END TIM2_IRQn 0 */
    HAL_TIM_IRQHandler(&htim2);
    /* USER CODE BEGIN TIM2_IRQn 1 */

    /* USER CODE END TIM2_IRQn 1 */
}

/**
 * @brief This function handles TIM3 global interrupt.
 */
void TIM3_IRQHandler(void) {
    /* USER CODE BEGIN TIM3_IRQn 0 */

    /* USER CODE END TIM3_IRQn 0 */
    HAL_TIM_IRQHandler(&htim3);
    /* USER CODE BEGIN TIM3_IRQn 1 */

    /* USER CODE END TIM3_IRQn 1 */
}

/**
 * @brief This function handles TIM4 global interrupt.
 */
void TIM4_IRQHandler(void) {
    /* USER CODE BEGIN TIM4_IRQn 0 */

    /* USER CODE END TIM4_IRQn 0 */
    HAL_TIM_IRQHandler(&htim4);
    /* USER CODE BEGIN TIM4_IRQn 1 */

    /* USER CODE END TIM4_IRQn 1 */
}

/**
 * @brief This function handles USART1 global interrupt.
 */
void USART1_IRQHandler(void) {
    /* USER CODE BEGIN USART1_IRQn 0 */
    /* USER CODE END USART1_IRQn 0 */
    HAL_UART_IRQHandler(&huart1);
    /* USER CODE BEGIN USART1_IRQn 1 */
    HAL_UART_Receive_IT(&huart1, (uint8_t *)rxBuffer, 1);
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
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == KEY0_Pin || GPIO_Pin == KEY1_Pin) {
        current = GPIO_Pin == KEY0_Pin ? KEY0 : KEY1;
        HAL_TIM_Base_Start_IT(&htim3);
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART1) {
        static unsigned char uRx_Data[1024];
        static unsigned char uLength = 0;
        if (rxBuffer[0] == '\n') {
            memset(Rx_Data, 0, sizeof(Rx_Data));
            memcpy(Rx_Data, uRx_Data, uLength * sizeof(unsigned char));
            game.answer_question((char *)Rx_Data);
            uLength = 0;
        } else {
            uRx_Data[uLength] = rxBuffer[0];
            uLength++;
        }
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim == (&htim2)) {
        // LED tick
        leddev.tick();
    }
    if (htim == (&htim3)) {
        HAL_TIM_Base_Stop_IT(htim);
        switch (current) {
            case KEY0: {
                if (HAL_GPIO_ReadPin(KEY0_GPIO_Port, KEY0_Pin) ==
                    GPIO_PIN_RESET) {
                    // uart_print("KEY0 pressed\r\n");
                    switch (game.get_game_state()) {
                        case Game::waiting: {
                            game.current_state = Game::playing;
                            game.generate_question();
                            break;
                        }
                        case Game::win: {
                            HAL_TIM_Base_Stop_IT(&htim4);
                            // HAL_NVIC_SystemReset();
                            break;
                        }
                        case Game::lose: {
                            HAL_TIM_Base_Stop_IT(&htim4);
                            // HAL_NVIC_SystemReset();
                            break;
                        }
                        case Game::playing: {
                            char *output = new char[100];
                            game.update_time();
                            sprintf(output,
                                    "[INFO] Time limit changed: %d min.\r\n", game.time_remains/60);
                            uart_print(output);
                            break;
                        }
                    }
                }
                break;
            }
            case KEY1: {
                if (HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) ==
                    GPIO_PIN_RESET) {
                    if (game.get_game_state() != Game::playing) return;
                    // uart_print("KEY1 pressed\r\n");
                    char *output = new char[100];
                    game.update_mode();
                    switch (game.current_mode) {
                        case mode_plus: {
                            sprintf(output, "[INFO] Mode changed: PLUS.\r\n");
                            break;
                        }
                        case mode_minus: {
                            sprintf(output, "[INFO] Mode changed: MINUS.\r\n");
                            break;
                        }
                        case mode_multiply: {
                            sprintf(output,
                                    "[INFO] Mode changed: MULTIPLY.\r\n");
                            break;
                        }
                        case mode_divide: {
                            sprintf(output, "[INFO] Mode changed: DIVIDE.\r\n");
                            break;
                        }
                    }
                    uart_print(output);
                }
                game.generate_question();
                break;
            }
            default:
                break;
        }
    }

    if (htim == (&htim4)) {
        game.tick();
        HAL_IWDG_Refresh(&hiwdg);
    }
}
/* USER CODE END 1 */
