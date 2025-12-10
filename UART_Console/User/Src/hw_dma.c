#include "hw_dma.h"

uint8_t rx_buf[RX_BUF_SIZE];

void DMA1_Usr_Init(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
  // --- USART2_RX, Stream 5 ---
  LL_DMA_InitTypeDef DMA1_UsrStrctRX_Init = {0};
  DMA1_UsrStrctRX_Init.Channel = LL_DMA_CHANNEL_4;
  DMA1_UsrStrctRX_Init.Direction = LL_DMA_DIRECTION_PERIPH_TO_MEMORY;
  DMA1_UsrStrctRX_Init.MemoryOrM2MDstAddress = (uint32_t)rx_buf;
  DMA1_UsrStrctRX_Init.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_BYTE;
  DMA1_UsrStrctRX_Init.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_INCREMENT;
  DMA1_UsrStrctRX_Init.Mode = LL_DMA_MODE_CIRCULAR;
  DMA1_UsrStrctRX_Init.NbData = RX_BUF_SIZE;
  DMA1_UsrStrctRX_Init.PeriphOrM2MSrcAddress = (uint32_t)&USART2->DR;
  DMA1_UsrStrctRX_Init.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE;
  DMA1_UsrStrctRX_Init.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;
  DMA1_UsrStrctRX_Init.Priority = LL_DMA_PRIORITY_HIGH;
  LL_DMA_Init(DMA1, LL_DMA_STREAM_5, &DMA1_UsrStrctRX_Init);
  // --- USART2_TX, Stream 6 ---
  LL_DMA_InitTypeDef DMA1_UsrStrctTX_Init = {0};
  DMA1_UsrStrctTX_Init.Channel = LL_DMA_CHANNEL_4;
  DMA1_UsrStrctTX_Init.Direction = LL_DMA_DIRECTION_MEMORY_TO_PERIPH;
  DMA1_UsrStrctTX_Init.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_BYTE;
  DMA1_UsrStrctTX_Init.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_INCREMENT;
  DMA1_UsrStrctTX_Init.Mode = LL_DMA_MODE_NORMAL;
  DMA1_UsrStrctTX_Init.PeriphOrM2MSrcAddress = (uint32_t)&USART2->DR;
  DMA1_UsrStrctTX_Init.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE;
  DMA1_UsrStrctTX_Init.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;
  DMA1_UsrStrctTX_Init.Priority = LL_DMA_PRIORITY_LOW;
  LL_DMA_Init(DMA1, LL_DMA_STREAM_6, &DMA1_UsrStrctTX_Init);
  
  LL_USART_EnableDMAReq_RX(USART2);
  LL_USART_EnableDMAReq_TX(USART2);
	LL_DMA_EnableStream(DMA1, LL_DMA_STREAM_5);
}