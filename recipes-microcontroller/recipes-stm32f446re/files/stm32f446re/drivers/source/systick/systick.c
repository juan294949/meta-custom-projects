#include "systick.h"

bool timerTrigger = false;

void sysTickInit(uint32_t precision)
{
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / precision);
	timerTrigger = true;
}

void sysTickUpdateTimer(uint32_t *timer)
{
	if(timerTrigger == true)
	{
		DECREMENT_TIMER(*timer);
		timerTrigger = false;
	}
}

void sysTickUpdateTimers(uint32_t* list[], uint32_t listSize)
{
	if(timerTrigger == true)
	{
		uint32_t* timer;

		for(uint8_t i = 0; i < listSize; ++i)
		{
			timer = list[i];
			DECREMENT_TIMER(*timer);
		}

		timerTrigger = false;
	}
}

bool sysTickTimerExpired(uint32_t timer)
{
	bool timerState = false;

	if(0 == timer)
	{
		timerState = true;
	}

	return timerState;
}

