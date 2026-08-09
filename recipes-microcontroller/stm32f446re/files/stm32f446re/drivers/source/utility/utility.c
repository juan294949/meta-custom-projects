#include "utility.h"
#include <string.h>
#include "gpio.h"

void initUtilities()
{
	//Initialize and confiure Usart
	gpioSelectPinMode(GPIOA, PIN3, ALTFUNC);      // PA2   : Modus = Alt. Funktion
	gpioSelectAltFunc(GPIOA, PIN3, AF7);          // PA2   : AF7 = USART2 Rx
	gpioSelectPinMode(GPIOA, PIN2, ALTFUNC);      // PA3   : Modus = Alt. Funktion
	gpioSelectAltFunc(GPIOA, PIN2, AF7);          // PA3   : AF7 = USART2 Tx

	usartSelectUsart(USART2);
	usartStartUsart(USART2);
	usartSetCommParams(USART2, 9600, NO_PARITY, LEN_8BIT, ONE_BIT);

	//Init SysTick
	sysTickInit(SYSTICK_PRECISION_1MS);
}

void print(const char* msg, ...)
{
	va_list args;
	char buffer[100];
	memset(buffer, 0, 100);

	va_start(args, msg);
	vsprintf(buffer, msg, args);
	usartSendString(USART2, buffer);
	va_end(args);
}

void blockMilliseconds(uint32_t delay)
{
	uint32_t  timer0 = delay;
	uint32_t* timerList[] = {&timer0};
	uint32_t  timerListSize = sizeof(timerList) / sizeof(uint32_t);	
	while(sysTickTimerExpired(timer0) == false)
	{
		sysTickUpdateTimers(timerList, timerListSize);
	}
}
