#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdint.h>
#include <stdbool.h>

#include "stm32f4xx.h"

/* Defines */
#define HSI_VALUE       ((uint32_t) 16000000u)
#define HSE_VALUE       ((uint32_t) 25000000u)

/* Function prototypes */
uint32_t systemGetSysClock(void);
uint32_t systemGetHclkFreq(void);
uint32_t systemGetPclk1Freq(void);
uint32_t systemGetPclk2Freq(void);

#endif
