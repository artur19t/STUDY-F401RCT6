#include "hw_it.h"

// --- User Button Iterrupt ---
void IT_EXTI0_Init(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
  LL_EXTI_InitTypeDef IT_USER_BUT_Init = {0};
  IT_USER_BUT_Init.LineCommand = ENABLE;
  IT_USER_BUT_Init.Line_0_31 = LL_EXTI_LINE_0;
  IT_USER_BUT_Init.Mode = LL_EXTI_MODE_IT;
  IT_USER_BUT_Init.Trigger = LL_EXTI_TRIGGER_FALLING;
  LL_EXTI_Init(&IT_USER_BUT_Init);
  LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_0);
  
  NVIC_SetPriority(EXTI0_IRQn, 0);
  NVIC_EnableIRQ(EXTI0_IRQn);
}