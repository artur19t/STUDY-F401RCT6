#ifndef _HW_INIT
#define _HW_INIT

#include "main.h"

#define RX_SIZE 256

extern uint8_t rx_buf[RX_SIZE];

void DMA1_UsrInit(void);
void USART2_UsrInit(void);
void GPIO_I2C1_Init(void);
void GPIO_USART2_Init(void);
void I2C1_UsrInit(void);

#endif