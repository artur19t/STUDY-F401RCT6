#include "usart_data.h"


void USART2_IRQHandler(void)
{
   if(LL_USART_IsActiveFlag_IDLE(USART2)){
     LL_USART_ClearFlag_IDLE(USART2);
     USART2_Read_Data();
   }
}

void USART2_Read_Data(void)
{
  uint32_t pos = RX_BUF_SIZE - LL_DMA_GetDataLength(DMA1, LL_DMA_STREAM_5);
  if (pos != rx_last_pos)
  {
    uint16_t len;

    if (pos > rx_last_pos)
      len = pos - rx_last_pos;
    else
      len = RX_BUF_SIZE - rx_last_pos + pos;

    static uint8_t packet[RX_BUF_SIZE];
    for (uint16_t i = 0; i < len; i++)
      packet[i] = rx_buf[(rx_last_pos + i) % RX_BUF_SIZE];

    packet[len] = 0; 

    rx_last_pos = pos;

    USART2_HandleCommand((char*)packet);
  }
}

void USART2_HandleCommand(char *cmd)
{
  if (strcmp(cmd, "LED1 ON") == 0)
  {
    LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_13);
    USART2_SendString_DMA("OK: LED1 ON\n");
  }
  else if (strcmp(cmd, "LED1 OFF") == 0)
  {
    LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_13);
    USART2_SendString_DMA("OK: LED1 OFF\n");
  }
  else if (strncmp(cmd, "FAN SET ", 8) == 0)
  {
    int val = atoi(cmd + 8);
    // ????????? ???????? ???????????
    USART2_SendString_DMA("OK: FAN SET\n");
  }
  else if (strcmp(cmd, "TEMP?") == 0)
  {
    USART2_SendString_DMA("TEMP 23.4\n");
  }
  else
  {
    USART2_SendString_DMA("ERR: UNKNOWN CMD\n");
  }
}

void USART2_SendString_DMA(const char *str)
{
  static uint8_t busy = 0;
  while (busy); // ????? ???????? ?? ???????
  busy = 1;

  uint16_t len = strlen(str);

  LL_DMA_DeInit(DMA1, LL_DMA_STREAM_6);

  LL_DMA_SetChannelSelection(DMA1, LL_DMA_STREAM_6, LL_DMA_CHANNEL_4);
  LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_STREAM_6, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
  LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_STREAM_6, LL_DMA_MEMORY_INCREMENT);
  LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_STREAM_6, LL_DMA_PERIPH_NOINCREMENT);
  LL_DMA_SetMemorySize(DMA1, LL_DMA_STREAM_6, LL_DMA_MDATAALIGN_BYTE);
  LL_DMA_SetPeriphSize(DMA1, LL_DMA_STREAM_6, LL_DMA_PDATAALIGN_BYTE);
  LL_DMA_SetMode(DMA1, LL_DMA_STREAM_6, LL_DMA_MODE_NORMAL);

  LL_DMA_SetPeriphAddress(DMA1, LL_DMA_STREAM_6, (uint32_t)&USART2->DR);
  LL_DMA_SetMemoryAddress(DMA1, LL_DMA_STREAM_6, (uint32_t)str);
  LL_DMA_SetDataLength(DMA1, LL_DMA_STREAM_6, len);

  LL_DMA_EnableStream(DMA1, LL_DMA_STREAM_6);
  LL_USART_EnableDMAReq_TX(USART2);

  // ???? ????????? ????????
  while (!LL_DMA_IsActiveFlag_TC6(DMA1));
  LL_DMA_ClearFlag_TC6(DMA1);

  while (!LL_USART_IsActiveFlag_TC(USART2)); // USART ??? ???????? stop-???

  busy = 0;
}