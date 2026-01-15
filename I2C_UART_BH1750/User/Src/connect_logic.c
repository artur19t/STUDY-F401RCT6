#include "connect_logic.h"

void USART2_SendNumber(uint32_t num)
{
  uint16_t len = 0;

  len = u32_to_str(num, tx_buf);

  tx_buf[len++] = '\r';
  tx_buf[len++] = '\n';

  send_string_usart2(tx_buf, len);
}

uint8_t u32_to_str(uint32_t val, char *buf)
{
  char tmp[10];
  uint8_t i = 0, j = 0;

  if (val == 0)
  {
    buf[0] = '0';
    return 1;
  }

  while (val)
  {
    tmp[i++] = (val % 10) + '0';
    val /= 10;
  }

  // reverse
  while (i)
    buf[j++] = tmp[--i];

  return j;
}

void send_string_usart2 (const char *buf, uint16_t len)
{ 
  LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_6);
  while (LL_DMA_IsEnabledStream(DMA1, LL_DMA_STREAM_6));
    
  LL_DMA_SetMemoryAddress(DMA1, LL_DMA_STREAM_6, (uint32_t)buf);
  LL_DMA_SetDataLength(DMA1, LL_DMA_STREAM_6, len); 
  
  LL_DMA_EnableStream(DMA1, LL_DMA_STREAM_6);
  LL_USART_EnableDMAReq_TX(USART2);
}