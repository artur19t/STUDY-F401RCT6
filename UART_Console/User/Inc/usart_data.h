#ifndef _USART_DATA
#define _USART_DATA

#include "main.h"

extern uint8_t rx_buf[];
extern uint32_t rx_last_pos;

void USART2_Read_Data(void);
void USART2_HandleCommand(char *cmd);
void USART2_SendString_DMA(const char *str);
#endif