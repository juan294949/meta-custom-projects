#include "exti.h"

void extiInit(void)
{
    for(uint8_t i = 0; i < 4; ++i)
    {
        SYSCFG->EXTICR[i] = 0x0000;
    }
}

void extiConfigIrq(GPIO_TypeDef *port, PIN_NUM pin)
{
    uint8_t index = 0;
    uint8_t shift = 0;
    uint8_t mask;

    switch((uint8_t) pin)
    {
        case PIN0:
        case PIN1:
        case PIN2:
        case PIN3:
            shift = pin * 4;        // Every pin uses four bits
            index = 0;              // Set the array-index of SYSCFG->EXTICR[]
            break;

        case PIN4:
        case PIN5:
        case PIN6:
        case PIN7:
            shift = (pin - 4) * 4;
            index = 1;
            break;

        case PIN8:
        case PIN9:
        case PIN10:
        case PIN11:
            index = 2;
            shift = (pin - 8) * 4;
            break;

        case PIN12:
        case PIN13:
        case PIN14:
        case PIN15:
            shift = (pin - 12) * 4;
            index = 3;
            break;
    }

    if(GPIOA == port)
    {
        mask = PORT_A;              // Inversion of the port mask
    }
    else if(GPIOB == port)
    {
        mask = PORT_B;
    }
    else if(GPIOC == port)
    {
        mask = PORT_C;
    }
    else if(GPIOD == port)
    {
        mask = PORT_D;
    }
    else if (GPIOE == port)
    {
        mask = PORT_E;
    }
    else if (GPIOF == port)
    {
        mask = PORT_F;
    }
    else if(GPIOG == port)
    {
        mask = PORT_G;
    }
    else if(GPIOH == port)
    {
        mask = PORT_H;
    }

    SYSCFG->EXTICR[index] |= (mask << shift);
}

void extiEnableIrq(EXTI_IRQ_NUM irqNum)
{
    EXTI->IMR |= 1 << irqNum;
}

void extiDisableIrq(EXTI_IRQ_NUM irqNum)
{
    EXTI->IMR &= ~(1 << irqNum);
}

void extiSetTriggerEdge(EXTI_IRQ_NUM irqNum, EXTI_TRIGGER trigger)
{
    if(RISING_EDGE == trigger)
    {
        EXTI->RTSR |= 1 << irqNum;      // Enable rising edge
        EXTI->FTSR &= ~(1 << irqNum);   // Disable falling edge
    }
    else if(FALLING_EDGE == trigger)
    {
        EXTI->FTSR |= 1 << irqNum;      // Enable falling edge
        EXTI->RTSR &= ~(1 << irqNum);   // Disable rising edge
    }
    else if(RISING_AND_FALLING == trigger)
    {
        EXTI->RTSR |= 1 << irqNum;      // Enable rising edge
        EXTI->FTSR |= 1 << irqNum;      // Enable falling edge
    }
}

void extiResetPending(EXTI_IRQ_NUM irqNum)
{
	EXTI->PR |= 1 << irqNum;
}
