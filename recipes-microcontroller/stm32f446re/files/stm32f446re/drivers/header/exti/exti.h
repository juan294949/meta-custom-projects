#ifndef _EXTI_
#define _EXTI_

#include <stdint.h>
#include <stdbool.h>

#include "stm32f4xx.h"
#include "system_stm32f4xx.h"

#include "gpio.h"

/* Typedefs */
typedef enum
{
    PORT_A = 0,    // EXTI mask for GPIOA
    PORT_B,        // EXTI mask for GPIOB
    PORT_C,        // EXTI mask for GPIOC
    PORT_D,        // ...
    PORT_E,
    PORT_F,
    PORT_G,
    PORT_H         // EXTI mask for GPIOH
} EXIT_PORT;

typedef enum
{
    EXTI_PIN0 = 0,
    EXTI_PIN1,
    EXTI_PIN2,
    EXTI_PIN3,
    EXTI_PIN4,
    EXTI_PIN5,
    EXTI_PIN6,
    EXTI_PIN7,
    EXTI_PIN8,
    EXTI_PIN9,
    EXTI_PIN10,
    EXTI_PIN11,
    EXTI_PIN12,
    EXTI_PIN13,
    EXTI_PIN14,
    EXTI_PIN15,
    EXTI_VOLTAGE_DETECTION,
    EXTI_RTC_ALARM,
    EXTI_USB_OTG_FS,          // USB on-the-go full speed
    EXTI_DONT_USE,
    EXTI_USB_OTG_HS,          // USB on-the-go high speed
    EXTI_RTC_TAMPER,
    EXTI_RTC_WAKEUP
} EXTI_IRQ_NUM;

typedef enum
{
    RISING_EDGE = 0,
    FALLING_EDGE,
    RISING_AND_FALLING
} EXTI_TRIGGER;

/* Function prototypes */
void extiInit(void);
void extiConfigIrq(GPIO_TypeDef *port, PIN_NUM pin);
void extiEnableIrq(EXTI_IRQ_NUM irqNum);
void extiDisableIrq(EXTI_IRQ_NUM irqNum);
void extiSetTriggerEdge(EXTI_IRQ_NUM irqNum, EXTI_TRIGGER trigger);
void extiResetPending(EXTI_IRQ_NUM irqNum);

#endif
