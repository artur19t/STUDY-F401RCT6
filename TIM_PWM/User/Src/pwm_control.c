#include "pwm_control.h"

void PWM_BUTTON_Control(void)
{
  uint16_t val = LL_TIM_OC_GetCompareCH1(TIM3);
  if (val+100>1000)
  {
    LL_TIM_OC_SetCompareCH1(TIM3, 0);
  }else
  {
    LL_TIM_OC_SetCompareCH1(TIM3, val+100);
  }
}

void PWM_Control(void)
{
  pwm.count_pwm++;
  if (pwm.count_pwm>5)
  {
    pwm.count_pwm = 0;
    uint16_t bright = LL_TIM_OC_GetCompareCH1(TIM3);
    if (bright >= 1000){
      pwm.rise = false;
    }else if(bright <= 0){
      pwm.rise = true;
    }
    if (pwm.rise){
      LL_TIM_OC_SetCompareCH1(TIM3, bright+1);
    }else{
      LL_TIM_OC_SetCompareCH1(TIM3, bright-1);
    }
  }
}