#ifndef GPIO_H
	#define GPIO_H

#include <stdint.h>
#include <stdbool.h>

#include "stm32f4xx.h"

/* Typedefs */
typedef enum
{
	PIN0 = 0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	PIN8,
	PIN9,
	PIN10,
	PIN11,
	PIN12,
	PIN13,
	PIN14,
	PIN15
} PIN_NUM;

typedef enum
{
	AF0 = 0,
	AF1,
	AF2,
	AF3,
	AF4,
	AF5,
	AF6,
	AF7,
	AF8,
	AF9,
	AF10,
	AF11,
	AF12,
	AF13,
	AF14,
	AF15
} ALT_FUNC;

typedef enum
{
	INPUT = 0,
	OUTPUT,
	ALTFUNC,
	ANALOG
} PIN_MODE;

typedef enum
{
	PUSHPULL = 0,
	OPENDRAIN
} OUTPUT_TYPE;

typedef enum
{
	NO_PULLUP_PULLDOWN = 0,
	PULLUP,
	PULLDOWN,
} PUPD_MODE;

typedef enum
{
	LOW_SPEED = 0,
	MEDIUM_SPEED,
	FAST_SPEED,
	HIGH_SPEED
} GPIO_SPEED;

/* Function prototypes */
void 	 gpioInitPort(GPIO_TypeDef *port);
void 	 gpioSelectPinMode(GPIO_TypeDef *port, PIN_NUM pin, PIN_MODE mode);
void 	 gpioSetPin(GPIO_TypeDef *port, PIN_NUM pin);
void 	 gpioResetPin(GPIO_TypeDef *port, PIN_NUM pin);
void 	 gpioTogglePin(GPIO_TypeDef *port, PIN_NUM pin);
void     gpioSelectAltFunc(GPIO_TypeDef *port, PIN_NUM pin, ALT_FUNC af);
void     gpioSelectPushPullType(GPIO_TypeDef *port, PIN_NUM pin, PUPD_MODE pupd);
bool     gpioSetOutputType(GPIO_TypeDef *port, PIN_NUM pin, OUTPUT_TYPE outType);
void     gpioSetOutputSpeed(GPIO_TypeDef *port, PIN_NUM pin, GPIO_SPEED speed);
uint8_t  gpioGetPinVal(GPIO_TypeDef *port, PIN_NUM pin);
uint16_t gpioGetPortVal(GPIO_TypeDef *port);

#endif
