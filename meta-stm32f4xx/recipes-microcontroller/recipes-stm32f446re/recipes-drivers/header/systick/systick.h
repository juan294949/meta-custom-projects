#ifndef SYSTICK
#define SYSTICK

#include <stdint.h>
#include <stdbool.h>

#include "stm32f4xx.h"
#include "system_stm32f4xx.h"

/* Macros */
#define DECREMENT_TIMER( timer )   \
    ( {                            \
        if ( timer > 0 )           \
            --timer;               \
    } )

/* Defines */
#define SYSTICK_PRECISION_10US	(100000)
#define SYSTICK_PRECISION_100US	(10000)
#define SYSTICK_PRECISION_1MS	(1000)
#define SYSTICK_PRECISION_10MS	(100)
#define SYSTICK_PRECISION_100MS	(10)
#define SYSTICK_PRECISION_1S	(1)

/* Function prototypes */
void sysTickInit(uint32_t precision);
void sysTickUpdateTimer(uint32_t *timer);
void sysTickUpdateTimers(uint32_t* list[], uint32_t listSize);
bool sysTickTimerExpired(uint32_t timer);

/* Extern Variables */
extern bool timerTrigger;

#endif
