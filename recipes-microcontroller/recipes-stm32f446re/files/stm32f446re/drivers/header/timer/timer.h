#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include <stdbool.h>

#include "stm32f4xx.h"

/* Function prototypes */
void timerBusClkOn(TIM_TypeDef *tim);
void timerBusClkOff(TIM_TypeDef *tim);
void timerSetPrescaler(TIM_TypeDef *tim, uint16_t psc);
void timerSetAutoReloadValue(TIM_TypeDef *tim, uint32_t reload);
void timerEnableInterrupt(TIM_TypeDef *tim);
void timerStart(TIM_TypeDef *tim);
void timerStop(TIM_TypeDef *tim);

#endif
