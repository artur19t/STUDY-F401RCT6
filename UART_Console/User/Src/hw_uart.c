#include "hw_uart.h"

// --- USART2 Init ---
void USART2_Console_Init(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
  
  LL_USART_InitTypeDef USART2_Usr_Init = {0};
  USART2_Usr_Init.BaudRate = 9600;
  USART2_Usr_Init.DataWidth = LL_USART_DATAWIDTH_8B;
  USART2_Usr_Init.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
  USART2_Usr_Init.OverSampling = LL_USART_OVERSAMPLING_16;
  USART2_Usr_Init.Parity = LL_USART_PARITY_NONE;
  USART2_Usr_Init.StopBits = LL_USART_STOPBITS_1;
  USART2_Usr_Init.TransferDirection = LL_USART_DIRECTION_TX_RX;
  LL_USART_Init(USART1, &USART2_Usr_Init);
  
  LL_USART_ConfigAsyncMode(USART2);
  LL_USART_Enable(USART2);
  
  LL_USART_EnableIT_IDLE(USART2);
  NVIC_SetPriority(USART2_IRQn, 0);
  NVIC_EnableIRQ(USART2_IRQn);
}