#include "hw_tim.h"

// --- Tim for PWM
void TIM3_PWM_Init (void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);
  // --- set tick to 1kHz
  LL_TIM_SetPrescaler(TIM3, 84-1);
  LL_TIM_SetAutoReload(TIM3,1000-1);
  // --- Set PWM mode 1Ch
  LL_TIM_OC_SetMode(TIM3, LL_TIM_CHANNEL_CH1, LL_TIM_OCMODE_PWM1);
  LL_TIM_OC_SetCompareCH1(TIM3, 200);
  LL_TIM_OC_EnablePreload(TIM3, LL_TIM_CHANNEL_CH1);
  // --- Conect to LED Pin
  LL_TIM_CC_EnableChannel(TIM3, LL_TIM_CHANNEL_CH1);
  // --- Enable TIM3
  LL_TIM_EnableARRPreload(TIM3);
  LL_TIM_EnableCounter(TIM3);
  LL_TIM_GenerateEvent_UPDATE(TIM3);
}

// --- Tim tick for ButState
void TIM2_BUT_STATE_Init(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);
  // --- set tick to 1kHz
  LL_TIM_SetPrescaler(TIM2, 84-1);
  LL_TIM_SetAutoReload(TIM2,1000-1);
  
  LL_TIM_EnableUpdateEvent(TIM2);
  LL_TIM_EnableIT_UPDATE(TIM2);
  LL_TIM_EnableCounter(TIM2);
  
  NVIC_SetPriority(TIM2_IRQn,1);
  NVIC_EnableIRQ(TIM2_IRQn);
}
