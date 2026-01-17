#include "connect_logic.h"

uint8_t len = 0;
static uint8_t buf_dma[RX_SIZE];
enum parse_status_t
{
    PARSE_OK = 0,
    PARSE_ERR_EMPTY,
    PARSE_ERR_NOT_DIGIT,
    PARSE_ERR_OVERFLOW
};

void USART2_SendNumber(uint32_t num)
{
  uint16_t len = 0;

  len = u32_to_str(num, tx_buf);

  tx_buf[len++] = '\r';
  tx_buf[len++] = '\n';

  send_arr_usart2(tx_buf, len);
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

void send_arr_usart2 (const char *buf, uint16_t len)
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

void USART2_logic(uint8_t *buf, uint16_t dSize, bool need_s)
{
  uint32_t val = 0;
  uint8_t res = 0;
  uint32_t timer_val = 0;
  DMA_buf(buf, dSize, need_s);
  if(!need_s)
  {
    res = parse_from_uart(buf_dma, len, &val);
    switch (res)
    {
      case PARSE_OK:
        //logic
        break;
      case PARSE_ERR_EMPTY:
      {
        char err_str[] = "Error: Accepted empty value\r\n";
        send_string_usart2(err_str);
        break;
      }
      case PARSE_ERR_NOT_DIGIT:
      {
        char err_str[] = "Error: Accepted not digit value\r\n";
        send_string_usart2(err_str);
        break;
      }
      case PARSE_ERR_OVERFLOW:
      {
        char err_str[] = "Error: Accepted number which value exceeds uint32_t\r\n";
        send_string_usart2(err_str);
        break;
      }
      default:
        break;
    }
    len = 0;
  }
}

void DMA_buf(uint8_t *bufAddr, uint16_t dSize, bool need_s)
{
  for(uint16_t i = 0; i < dSize; i++)
  {
    uint8_t c = bufAddr[i];
    if(c == '\r' || c == '\n')
    {
      break;
    }
    buf_dma[len] = c;
    len++;
  }
  if (!need_s)
  {
    buf_dma[len] = '\0';
  }
}

enum parse_status_t parse_from_uart(const uint8_t *buf, uint16_t len, uint32_t *value)
{
  uint32_t result = 0;

  if (buf == NULL || len == 0)
  {
    return PARSE_ERR_EMPTY;
  }
  for (size_t i = 0; i < len; i++)
  {
    if (buf[i] < '0' || buf[i] > '9')
    {
      return PARSE_ERR_NOT_DIGIT;
    }
    uint8_t digit = buf[i] - '0';

    if (result > (UINT32_MAX - digit) / 10)
    {
      return PARSE_ERR_OVERFLOW;
    }
    result = result * 10 + digit;
  }

  *value = result;
  return PARSE_OK;
}

void send_string_usart2 (const char *buf)
{
  uint16_t len = strlen(buf);
  
  LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_6);
  while (LL_DMA_IsEnabledStream(DMA1, LL_DMA_STREAM_6));
    
  LL_DMA_SetMemoryAddress(DMA1, LL_DMA_STREAM_6, (uint32_t)buf);
  LL_DMA_SetDataLength(DMA1, LL_DMA_STREAM_6, len); 
  
  LL_DMA_EnableStream(DMA1, LL_DMA_STREAM_6);
  LL_USART_EnableDMAReq_TX(USART2);
}
