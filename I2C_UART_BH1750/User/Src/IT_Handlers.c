#include "IT_Handlers.h"

void DMA1_Stream6_IRQHandler(void)
{
  if (LL_DMA_IsActiveFlag_TC6(DMA1))
  {
    LL_DMA_ClearFlag_TC6(DMA1);

    LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_6);
    LL_USART_DisableDMAReq_TX(USART2);
  }
}