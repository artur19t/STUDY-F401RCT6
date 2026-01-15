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

uint8_t I2C2_WriteByte(uint8_t addr, uint8_t data)
{
  uint32_t t;
  t = 200000;
  while (LL_I2C_IsActiveFlag_BUSY(I2C1))
  {
    if(--t==0) 
      return 0; 
  }

  t = 200000;
  LL_I2C_GenerateStartCondition(I2C1);
  while (!LL_I2C_IsActiveFlag_SB(I2C1))
  {
    if(--t==0) 
      return 0; 
  }

  LL_I2C_TransmitData8(I2C1, addr);
  t = 200000;
  while (!LL_I2C_IsActiveFlag_ADDR(I2C1))
  {
    if(--t==0) 
      return 0; 
  }
  LL_I2C_ClearFlag_ADDR(I2C1);

  t = 200000;
  while (!LL_I2C_IsActiveFlag_TXE(I2C1))
  {
    if(--t==0) 
      return 0; 
  }
  LL_I2C_TransmitData8(I2C1, data);

  t = 200000;
  while (!LL_I2C_IsActiveFlag_BTF(I2C1))
  {
    if(--t==0) 
      return 0; 
  }
  LL_I2C_GenerateStopCondition(I2C1);
  
  return 1;
}