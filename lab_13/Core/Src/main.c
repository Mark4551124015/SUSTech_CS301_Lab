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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd.h"
#include "string.h"

// #include "lcd_v4.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define BUFFER_SIZE 1024

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_tx;
DMA_HandleTypeDef hdma_usart1_rx;

/* USER CODE BEGIN PV */
extern uint8_t recv_end_flag;
extern uint32_t rx_len;
extern uint8_t rx_buffer[BUFFER_SIZE];
const uint8_t TEXT_TO_SEND[] = {
    "1.Into the wild. A half-moon glowed on smooth granite \
boulders, turning them silver. The silence was\
broken only by the ripple of water from the swift\
black river and the whisper of trees in the forest\
beyond.\
There was a stirring in the shadows, and from\
all around lithe dark shapes crept stealthily over\
the rocks. Unsheathed claws glinted in the\
moonlight. Wary eyes flashed like amber. And\
then, as if on a silent signal, the creatures leaped\
at each other, and suddenly the rocks were alive\
with wrestling, screeching cats.\
At the center of the frenzy of fur and claws, a\
massive dark tabby pinned a bracken-colored tom\
to the ground and drew up his head triumphantly.\
\"Oakheart!\" the tabby growled. \"How dare you\
hunt in our territory? The Sunningrocks belong to\
ThunderClan!\"\
\"After tonight, Tigerclaw, this will be just\
another RiverClan hunting ground!\" the bracken-\
colored tom spat back.\
A warning yowl came from the shore, shrill\
and anxious. \"Look out! More RiverClan warriors\
are coming!\"\
Tigerclaw turned to see sleek wet bodies\
sliding out of the water below the rocks. The\
drenched RiverClan warriors bounded silently up\
the shore and hurled themselves into battle\
without even stopping to shake the water from\
their fur.\
The dark tabby glared down at Oakheart. \"You\
may swim like otters, but you and your warriors\
do not belong in this forest!\" He drew back his lips\
and showed his teeth as the cat struggled beneath\
him.\
The desperate scream of a ThunderClan she-\
cat rose above the clamor. A wiry RiverClan tom\
had pinned the brown warrior flat on her belly.\
Now he lunged toward her neck with jaws still\
dripping from his swim across the river.\
Tigerclaw heard the cry and let go of\
Oakheart. With a mighty leap, he knocked the\
enemy warrior away from the she-cat. \"Quick,\
Mousefur, run!\" he ordered, before turning on the\
RiverClan tom who had threatened her. Mousefur\
scrambled to her paws, wincing from a deep gash\
on her shoulder, and raced away.\
Behind her, Tigerclaw spat with rage as the\
RiverClan tom sliced open his nose. Blood blinded\
him for an instant, but he lunged forward\
regardless and sank his teeth into the hind leg of\
his enemy. The RiverClan cat squealed and\
struggled free.\
\"Tigerclaw!\" The yowl came from a warrior\
with a tail as red as fox fur. \"This is useless! There\
are too many RiverClan warriors!\"\
\"No, Redtail. ThunderClan will never be\
beaten!\" Tigerclaw yowled back, leaping to\
Redtail's side. \"This is our territory!\" Blood was\
welling around his broad black muzzle, and he\
shook his head impatiently, scattering scarlet\
drops onto the rocks.\
\"ThunderClan  will  honor  your  courage,\
Tigerclaw, but we cannot afford to lose any more\
of our warriors,\" Redtail urged. \"Bluestar would\
never expect her warriors to fight against these\
impossible odds. We will have another chance to\
avenge this defeat.\" He met Tigerclaw's amber-\
eyed gaze steadily, then reared away and sprang\
onto a boulder at the edge of the trees.\
\"Retreat, ThunderClan! Retreat!\" he yowled.\
At once his warriors squirmed and struggled away\
from their opponents. Spitting and snarling, they\
backed toward Redtail. For a heartbeat, the\
RiverClan cats looked confused. Was this battle so\
easily won? Then Oakheart yowled a jubilant cry.\
As soon as they heard him, the RiverClan warriors\
raised their voices and joined their deputy in\
caterwauling their victory.\
Redtail looked down at his warriors. With a\
flick of his tail, he gave the signal and the\
ThunderClan cats dived down the far side of the\
Sunningrocks, then disappeared into the trees.\
Tigerclaw followed last. He hesitated at the\
edge of the forest and glanced back at the\
bloodstained battlefield. His face was grim, his\
eyes furious slits. Then he leaped after his Clan\
into the silent forest.\
In a deserted clearing, an old gray she-cat sat\
alone, staring up at the clear night sky. All around\
her in the shadows she could hear the breathing\
and stirrings of sleeping cats.\
A small tortoiseshell she-cat emerged from a\
dark corner, her pawsteps quick and soundless.\
The gray cat dipped her head in greeting.\
\"How is Mousefur?\" she meowed.\
\"Her wounds are deep, Bluestar,\" answered the\
tortoiseshell, settling herself on the night-cool\
grass. \"But she is young and strong; she will heal\
quickly.\"\
\"And the others?\"\
\"They will all recover, too.\"\
Bluestar sighed. \"We are lucky not to have lost\
any of our warriors this time. You are a gifted\
medicine cat, Spottedleaf.\" She tilted her head\
again and studied the stars. \"I am deeply troubled\
by tonight's defeat. ThunderClan has not been\
beaten in its own territory since I became leader,\"\
she murmured. \"These are difficult times for our\
Clan. The season of newleaf is late, and there have\
been fewer kits. ThunderClan needs more\
warriors if it is to survive.\"\
\"But the year is only just beginning,\"\
Spottedleaf pointed out calmly. \"There will be\
more kits when greenleaf comes.\"\
The gray cat twitched her broad shoulders.\
\"Perhaps. But training our young to become\
warriors takes time. If ThunderClan is to defend\
its territory, it must have new warriors as soon as\
possible.\"\
\"Are you asking StarClan for answers?\"\
meowed Spottedleaf gently, following Bluestar's\
gaze and staring up at the swath of stars glittering\
in the dark sky.\
\"It is at times like this we need the words of\
ancient warriors to help us. Has StarClan spoken\
to you?\" Bluestar asked.\
\"Not for some moons, Bluestar.\"\
Suddenly a shooting star blazed over the\
treetops. Spottedleaf's tail twitched and the fur\
along her spine bristled.\
Bluestar's ears pricked but she remained silent\
as Spottedleaf continued to gaze upward.\
After a few moments, Spottedleaf lowered her\
head and turned to Bluestar. \"It was a message\
from StarClan,\" she murmured. A distant look\
came into her eyes. \"Fire alone can save our Clan.\"\
\"Fire?\" Bluestar echoed. \"But fire is feared by\
all the Clans! How can it save us?\"\
Spottedleaf shook her head. \"I do not know,\"\
she admitted. \"But this is the message StarClan\
has chosen to share with me.\"\
The ThunderClan leader fixed her clear blue\
eyes on the medicine cat. \"You have never been\
wrong before, Spottedleaf,\" she meowed. \"If\
StarClan has spoken, then it must be so. Fire will\
save our Clan.\""}; /* 要发送的内容 */
#define SEND_BUF_SIZE sizeof(TEXT_TO_SEND) + 2

uint8_t g_sendbuf[SEND_BUF_SIZE]; /* 发�?�数据缓冲区 */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

    /* MCU
     * Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the
     * Systick. */
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
    /* USER CODE BEGIN 2 */

    uint16_t i, k;
    uint16_t len;
    uint8_t mask = 0;
    float pro = 0; /* 进度 */

    LCD_Init();
    POINT_COLOR = RED;
    LCD_ShowString(30, 50, 200, 16, 16, "CS301");
    LCD_ShowString(30, 70, 200, 16, 16, "DMA TEST");
    LCD_ShowString(30, 90, 200, 16, 16, "Press KEY0 to start");
    POINT_COLOR = BLUE;

    //  lcd_init();
    //  lcd_show_string(30, 50, 200, 16, 16, "CS301", RED);
    //  lcd_show_string(30, 70, 200, 16, 16, "DMA TEST", RED);
    //  lcd_show_string(30, 90, 200, 16, 16, "Press KEY0 to start", RED);

    len = sizeof(TEXT_TO_SEND);
    k = 0;

    for (i = 0; i < SEND_BUF_SIZE; i++) /* 填充ASCII字符集数 */
    {
        if (k >= len) /* 入换行符 */
        {
            if (mask) {
                g_sendbuf[i] = 0x0a;
                k = 0;
            } else {
                g_sendbuf[i] = 0x0d;
                mask++;
            }
        } else /* 复制TEXT_TO_SEND语句 */
        {
            mask = 0;
            g_sendbuf[i] = TEXT_TO_SEND[k];
            k++;
        }
    }

    i = 0;
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    // while (1) {
    //     /* USER CODE END WHILE */

    //     /* USER CODE BEGIN 3 */
    //     if (HAL_GPIO_ReadPin(KEY0_GPIO_Port, KEY0_Pin) ==
    //         GPIO_PIN_RESET) /* KEY0按下 */
    //     {
    //         LCD_ShowString(30, 130, 200, 16, 16, "Start Transimit....");
    //         LCD_ShowString(30, 150, 200, 16, 16, "   %"); /* 显示百分�?? */
    //         //	      lcd_show_string(30, 130, 200, 16, 16, "Start
    //         // Transimit....", BLUE); 	      lcd_show_string(30, 150, 200, 16,
    //         // 16, " %", BLUE);    /* 显示百分�?? */

    //         HAL_UART_Transmit_DMA(&huart1, g_sendbuf, SEND_BUF_SIZE);
    //         /* 等待DMA传输完成，此时CPU空闲，可以处理其他任�??
    //          * 实际应用中，传输数据期间，可以执行另外的任务
    //          */

    //         while (1) {
    //             /* 等待 DMA1_Channel4 传输完成 */
    //             if (__HAL_DMA_GET_FLAG(
    //                     &hdma_usart1_tx,
    //                     DMA_FLAG_TC4)) /* 等待 DMA1_Channel4 传输完成 */
    //             {
    //                 __HAL_DMA_CLEAR_FLAG(
    //                     &hdma_usart1_tx,
    //                     DMA_FLAG_TC4); /* 清除 DMA1_Channel4 传输完成标志 */
    //                 HAL_UART_DMAStop(&huart1); /* 传输完成以后关闭串口DMA */
    //                 break;
    //             }

    //             pro = __HAL_DMA_GET_COUNTER(
    //                 &hdma_usart1_tx); /* 得到当前还剩余多少个数据 */
    //             len = SEND_BUF_SIZE;  /* 总长�?? */
    //             pro = 1 - (pro / len); /* 得到百分�?? */
    //             pro *= 100;            /* 扩大100�?? */
    //             LCD_ShowNum(30, 150, pro, 3, 16);
    //             //	          lcd_show_num(30, 150, pro, 3, 16, BLUE);
    //         }
    //         LCD_ShowNum(30, 150, 100, 3, 16); /* 显示100% */
    //         LCD_ShowString(30, 130, 200, 16, 16,
    //                        "Transimit Finished!"); /* 提示传�?�完�?? */
    //         //	      lcd_show_num(30, 150, 100, 3, 16, BLUE);    /* 显示100% */
    //         //	      lcd_show_string(30, 130, 200, 16, 16, "Transimit
    //         // Finished!", BLUE); /* 提示传�?�完�?? */
    //     }
    // }
    while (1) {
        if (recv_end_flag) {
            recv_end_flag = 0;
            HAL_UART_Transmit_DMA(&huart1, rx_buffer, BUFFER_SIZE);
            LCD_ShowString(30, 110, 200, 16, 16, "The data is: ");
            LCD_ShowString(30, 130, 200, 16, 16, rx_buffer);
            memset(rx_buffer, 0, rx_len);
            rx_len = 0;
        }
        HAL_UART_Receive_DMA(&huart1, rx_buffer, BUFFER_SIZE);
    }
    /* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Initializes the RCC Oscillators according to the specified
     * parameters in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                                  RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
        Error_Handler();
    }
}

/**
 * @brief USART1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART1_UART_Init(void) {
    /* USER CODE BEGIN USART1_Init 0 */

    /* USER CODE END USART1_Init 0 */

    /* USER CODE BEGIN USART1_Init 1 */

    /* USER CODE END USART1_Init 1 */
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart1) != HAL_OK) {
        Error_Handler();
    }
    /* USER CODE BEGIN USART1_Init 2 */
    __HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
    __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
    HAL_UART_Receive_DMA(&huart1, rx_buffer, BUFFER_SIZE);
    /* USER CODE END USART1_Init 2 */
}

/**
 * Enable DMA controller clock
 */
static void MX_DMA_Init(void) {
    /* DMA controller clock enable */
    __HAL_RCC_DMA1_CLK_ENABLE();

    /* DMA interrupt init */
    /* DMA1_Channel4_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(DMA1_Channel4_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel4_IRQn);
    /* DMA1_Channel5_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    /* USER CODE BEGIN MX_GPIO_Init_1 */
    /* USER CODE END MX_GPIO_Init_1 */

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin : KEY0_Pin */
    GPIO_InitStruct.Pin = KEY0_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(KEY0_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pin : LED0_Pin */
    GPIO_InitStruct.Pin = LED0_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED0_GPIO_Port, &GPIO_InitStruct);

    /* USER CODE BEGIN MX_GPIO_Init_2 */
    /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return
     * state
     */
    __disable_irq();
    while (1) {
    }
    /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line) {
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line
       number, ex: printf("Wrong parameters value: file %s on line %d\r\n",
       file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
