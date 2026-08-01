#include "gpio.h"

int gpio_test(void)
{

    int status = ERROR;

    /*configure the GPIO at PORTA Pin 5*/
	// gpioSelectPinMode(GPIOA, PIN5, OUTPUT);
    // gpioSetOutputType(GPIOA, PIN5, PUSHPULL);
    // gpioSelectPushPullType(GPIOA, PIN5, NO_PULLUP_PULLDOWN);
    // /*Set pin high, and check its state.*/
    // gpioSetPin(GPIOA,PIN5);
    // ((int)gpioGetPinVal(GPIOA,PIN5) > 0) ? (status=SUCCESS): (status=ERROR);
    // if(status != ERROR)
    // {
    //  gpioResetPin(GPIOA,PIN5);
    //  ((int)gpioGetPinVal(GPIOA,PIN5) == 0) ? (status=SUCCESS): (status=ERROR);
    // }

    return status;
}