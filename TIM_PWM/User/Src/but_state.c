#include "but_state.h"

enum state
{
  RELEASED,
  PRESSED,
  WAIT_RELEASED,
  LONG_PRESSED
};

typedef struct 
{
  bool press;
  enum state st;
  uint32_t count_tick;
  bool pwm_but;
}BUT_State;

static BUT_State b_state = 
{
  .press = false,
  .st = RELEASED,
  .count_tick = 0,
  .pwm_but = false
};

void TIM2_IRQHandler(void)
{
  if(LL_TIM_IsActiveFlag_UPDATE(TIM2))
  {
    LL_TIM_ClearFlag_UPDATE(TIM2);
    debounce();
    if(!b_state.pwm_but){
      PWM_Control();
    }
  }
}

void EXTI0_IRQHandler(void)
{
  if(LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_0))
  {
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_0);
    b_state.press = true;
    if (b_state.pwm_but){
      PWM_BUTTON_Control();
    }
  }
}

void debounce(void)
{
  switch (b_state.st)
  {
    case RELEASED:
      if (b_state.press)
      {
        b_state.press = false;
        b_state.st = PRESSED;
        b_state.count_tick = 0;
      }
      break;
    case PRESSED:
      if (b_state.press)
      {
        b_state.press = false;
        b_state.st = RELEASED;
      }
      b_state.count_tick++;
      if (b_state.count_tick>20)
      {
        b_state.st = WAIT_RELEASED;
      }
      break;
    case WAIT_RELEASED:
      if (b_state.press)
      {
        b_state.press = false;
        b_state.st = RELEASED;
      }
      if (LL_GPIO_IsInputPinSet(GPIOA, LL_GPIO_PIN_0))
      {
        b_state.press = false;
        b_state.st = RELEASED;
      }
      b_state.count_tick++;
      if (b_state.count_tick>2000)
      {
        b_state.st = LONG_PRESSED;
      }
      break;
    case LONG_PRESSED:
      if (LL_GPIO_IsInputPinSet(GPIOA, LL_GPIO_PIN_0))
      {
        b_state.press = false;
        b_state.st = RELEASED;
        b_state.pwm_but = !b_state.pwm_but;
        if(b_state.pwm_but){
          LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_13);
        }else{
          LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_13);
        }
      }
      break;
    default:
      break;
  }
}

