#include "hw_gpio.h"
//PB4
//PC13
//PA0

// --- PWM_LED TIM3_CH1 ---
void GPIO_PWM_LED_Init (void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
  LL_GPIO_InitTypeDef GPIO_PWM_Init = {0};
  GPIO_PWM_Init.Alternate = LL_GPIO_AF_2;
  GPIO_PWM_Init.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_PWM_Init.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_PWM_Init.Pin = LL_GPIO_PIN_4;
  GPIO_PWM_Init.Pull = LL_GPIO_PULL_NO;
  GPIO_PWM_Init.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;
  LL_GPIO_Init(GPIOB, &GPIO_PWM_Init);
}

// --- Indicator LED ---
void GPIO_LED_INDICATOR_Init (void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
  LL_GPIO_InitTypeDef GPIO_LED_Init = {0};
  GPIO_LED_Init.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_LED_Init.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_LED_Init.Pin = LL_GPIO_PIN_13;
  GPIO_LED_Init.Pull = LL_GPIO_PULL_NO;
  GPIO_LED_Init.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;
  LL_GPIO_Init(GPIOC, &GPIO_LED_Init);
  LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_13);
}

// --- User Button ---
void GPIO_USER_BUT_Init (void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
  LL_GPIO_InitTypeDef GPIO_BUT_Init = {0};
  GPIO_BUT_Init.Mode = LL_GPIO_MODE_INPUT;
  GPIO_BUT_Init.Pin = LL_GPIO_PIN_0;
  GPIO_BUT_Init.Pull = LL_GPIO_PULL_UP;
  GPIO_BUT_Init.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;
  LL_GPIO_Init(GPIOA, &GPIO_BUT_Init);
}