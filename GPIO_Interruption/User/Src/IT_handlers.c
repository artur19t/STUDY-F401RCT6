#include "IT_handlers.h"

enum state
{
  RELEASED,
  PRESSED,
  WAIT_RELEASED
};

enum state but = RELEASED;
uint8_t deb = DEBOUNCE_TIME;
bool but_press = 0;

void EXTI0_IRQHandler (void)
{
  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_0);
  but_press = true;
}

void debouncing (void)
{
  switch (but)
  {
    case RELEASED:
    {
      deb = DEBOUNCE_TIME;
      if(but_press)
      {
        but = PRESSED;
        but_press = false;
      }
      break;
    }
    case PRESSED:
    {
      deb--;
      if (deb>0)
      {
        break;
      }
      if(but_press)
      {
        deb = DEBOUNCE_TIME;
        but_press = false;
        break;
      }
      if (deb == 0)
      {
        LL_GPIO_TogglePin(GPIOC, LL_GPIO_PIN_13);
        but = WAIT_RELEASED;
        deb = DEBOUNCE_TIME;
      }
      break;
    }
    case WAIT_RELEASED:
    {
      if (LL_GPIO_IsInputPinSet(GPIOA, LL_GPIO_PIN_0))
      {
        but = RELEASED;
        deb = DEBOUNCE_TIME;
        but_press = false;
      }
      break;
    }
    default:
    {
      break;
    }
  }
}