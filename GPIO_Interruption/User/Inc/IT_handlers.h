#ifndef _IT_HANDLERS
#define _IT_HANDLERS

#include "main.h"
#define DEBOUNCE_TIME 100;
void EXTI0_IRQHandler (void);
//void SysTick_Handler (void);
void debouncing (void);
#endif