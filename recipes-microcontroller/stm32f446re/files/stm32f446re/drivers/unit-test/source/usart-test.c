#include "gpio.h"
#include "utility.h"

int usart_test_tx(const char* Str, unsigned long long size)
{
    int status = ERROR;

    if(size > 0 )
    {
        /* Check size not 0*/
        print(Str);
        status = SUCCESS;
    }

    return status;
}

void usart2_init(void)
{
    gpioSelectPinMode(GPIOA, PIN3, ALTFUNC);      // PA3   : Modus = Alt. Funktion
	gpioSelectAltFunc(GPIOA, PIN3, AF7);          // PA3   : AF7 = USART2 Rx
	gpioSelectPinMode(GPIOA, PIN2, ALTFUNC);      // PA2   : Modus = Alt. Funktion
	gpioSelectAltFunc(GPIOA, PIN2, AF7);          // PA2   : AF7 = USART2 Tx
	usartSelectUsart(USART2);
	usartStartUsart(USART2);
	usartSetCommParams(USART2, 9600, NO_PARITY, LEN_8BIT, ONE_BIT);
}