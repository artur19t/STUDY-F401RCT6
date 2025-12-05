#include "hw_it.h"

void IT_But_init(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
  LL_EXTI_InitTypeDef IT_But_Init = {0};
  IT_But_Init.LineCommand = ENABLE;
  IT_But_Init.Line_0_31 = LL_EXTI_LINE_0;
  IT_But_Init.Mode = LL_EXTI_MODE_IT;
  IT_But_Init.Trigger = LL_EXTI_TRIGGER_FALLING;
  LL_EXTI_Init(&IT_But_Init);
  
  LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_0);
  NVIC_SetPriority(EXTI0_IRQn, 0);
  NVIC_EnableIRQ(EXTI0_IRQn);
}

void SysTick_Init(void)
{
  SysTick->LOAD = (SystemCoreClock/1000) - 1;
  SysTick->VAL = 0;
  SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk |SysTick_CTRL_ENABLE_Msk;
}