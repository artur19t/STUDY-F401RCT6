#ifndef _PWM_CONTROL
#define _PWM_CONTROL

#include "main.h"
typedef struct 
{
  bool rise;
  uint16_t count_pwm;
}PWM_State;

static PWM_State pwm = 
{
  .rise = true,
  .count_pwm = 0,
};
void PWM_Control(void);
void PWM_BUTTON_Control(void);
#endif 