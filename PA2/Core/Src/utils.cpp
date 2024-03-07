#include "utils.h"
#include <sstream>
#include "string.h"

extern UART_HandleTypeDef huart1;
void uart_print(const char *str) {
    HAL_UART_Transmit(&huart1, (uint8_t *)str, strlen(str), 0xFFFF);
}
