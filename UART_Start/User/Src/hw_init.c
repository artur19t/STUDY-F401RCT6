#include "hw_init.h"

//PA: 2,3

// --- GPIO Init for USART2 ---
void GPIO_USART2_UsrInit (void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
  // --- USART2_TX ---
  LL_GPIO_InitTypeDef GPIO_Usr_Struct = {0};
  GPIO_Usr_Struct.Alternate = LL_GPIO_AF_7;
  GPIO_Usr_Struct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_Usr_Struct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_Usr_Struct.Pin = LL_GPIO_PIN_2;
  GPIO_Usr_Struct.Pull = LL_GPIO_PULL_NO;
  GPIO_Usr_Struct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;
  LL_GPIO_Init(GPIOA, &GPIO_Usr_Struct);
  // --- USART2_RX ---
  GPIO_Usr_Struct = (LL_GPIO_InitTypeDef){0};
  GPIO_Usr_Struct.Alternate = LL_GPIO_AF_7;
  GPIO_Usr_Struct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_Usr_Struct.Pin = LL_GPIO_PIN_3;
  GPIO_Usr_Struct.Pull = LL_GPIO_PULL_UP;
  GPIO_Usr_Struct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;
  LL_GPIO_Init(GPIOA, &GPIO_Usr_Struct);
}

// --- USART2 Init ---
void USART2_UsrInit (void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
  
  LL_USART_InitTypeDef USART_Usr_Struct = {0};
  USART_Usr_Struct.BaudRate = 9600;
  USART_Usr_Struct.DataWidth = LL_USART_DATAWIDTH_8B;
  USART_Usr_Struct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
  USART_Usr_Struct.OverSampling = LL_USART_OVERSAMPLING_8;
  USART_Usr_Struct.Parity = LL_USART_PARITY_NONE;
  USART_Usr_Struct.StopBits = LL_USART_STOPBITS_1;
  USART_Usr_Struct.TransferDirection = LL_USART_DIRECTION_TX_RX;
  LL_USART_Init (USART2, &USART_Usr_Struct);
  
  LL_USART_ConfigAsyncMode(USART2);
  LL_USART_EnableIT_RXNE(USART2);
}