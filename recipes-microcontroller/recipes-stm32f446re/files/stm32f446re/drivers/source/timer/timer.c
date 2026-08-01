#include "timer.h"

void timerBusClkOn(TIM_TypeDef *tim)
{
    if (TIM1 == tim)
    {
        RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    }
    else if (TIM2 == tim)
    {
        RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    }
    else if (TIM3 == tim)
    {
        RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    }
    else if (TIM4 == tim)
    {
        RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
    }
    else if (TIM5 == tim)
    {
        RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
    }
    else if (TIM6 == tim)
    {
        RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
    }
    else if (TIM7 == tim)
    {
        RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
    }
    else if (TIM8 == tim)
    {
        RCC->APB2ENR |= RCC_APB2ENR_TIM8EN;
    }
    else if (TIM9 == tim)
    {
        RCC->APB2ENR |= RCC_APB2ENR_TIM9EN;
    }
    else if (TIM10 == tim)
    {
        RCC->APB2ENR |= RCC_APB2ENR_TIM10EN;
    }
    else if (TIM11 == tim)
    {
        RCC->APB2ENR |= RCC_APB2ENR_TIM11EN;
    }
    else if (TIM12 == tim)
    {
        RCC->APB1ENR |= RCC_APB1ENR_TIM12EN;
    }
    else if (TIM13 == tim)
    {
        RCC->APB1ENR |= RCC_APB1ENR_TIM13EN;
    }
    else if (TIM14 == tim)
    {
        RCC->APB1ENR |= RCC_APB1ENR_TIM14EN;
    }
    else
    {
        while(1)
        {
            // Timer not supported
        }
    }

    tim->CR1 = 0;  // Reset all bits of TIMx_CR1 to 0
}

void timerBusClkOff(TIM_TypeDef *tim)
{
    if (TIM1 == tim)
    {
        RCC->APB2RSTR |= RCC_APB2RSTR_TIM1RST;
    }
    else if (TIM2 == tim)
    {
        RCC->APB1RSTR |= RCC_APB1RSTR_TIM2RST;
    }
    else if (TIM3 == tim)
    {
        RCC->APB1RSTR |= RCC_APB1RSTR_TIM3RST;
    }
    else if (TIM4 == tim)
    {
        RCC->APB1RSTR |= RCC_APB1RSTR_TIM4RST;
    }
    else if (TIM5 == tim)
    {
        RCC->APB1RSTR |= RCC_APB1RSTR_TIM5RST;
    }
    else if (TIM6 == tim)
    {
        RCC->APB1RSTR |= RCC_APB1RSTR_TIM6RST;
    }
    else if (TIM7 == tim)
    {
        RCC->APB1RSTR |= RCC_APB1RSTR_TIM7RST;
    }
    else if (TIM8 == tim)
    {
        RCC->APB2RSTR |= RCC_APB2RSTR_TIM8RST;
    }
    else if (TIM9 == tim)
    {
        RCC->APB2RSTR |= RCC_APB2RSTR_TIM9RST;
    }
    else if (TIM10 == tim)
    {
        RCC->APB2RSTR |= RCC_APB2RSTR_TIM10RST;
    }
    else if (TIM11 == tim)
    {
        RCC->APB2RSTR |= RCC_APB2RSTR_TIM11RST;
    }
    else if (TIM12 == tim)
    {
        RCC->APB1RSTR |= RCC_APB1RSTR_TIM12RST;
    }
    else if (TIM13 == tim)
    {
        RCC->APB1RSTR |= RCC_APB1RSTR_TIM13RST;
    }
    else if (TIM14 == tim)
    {
        RCC->APB1RSTR |= RCC_APB1RSTR_TIM14RST;
    }
    else
    {
        while(1)
        {
            // Timer not supported
        }
    }
}

void timerSetPrescaler(TIM_TypeDef *tim, uint16_t psc)
{
    tim->PSC = psc;
}

void timerSetAutoReloadValue(TIM_TypeDef *tim, uint32_t reload)
{
    // 32-bit reload values are only valid for TIM2 and TIM5.
    if ((TIM2 == tim) || (TIM5 == tim))
    {
        tim->ARR = reload;
    }
    else
    {
        // For all other timers: Check that reload does not exceed UIN16_MAX.
        if (reload > UINT16_MAX)
        {
            reload = 0;   // reload value too high --> set to 0 -->
                          // timer will not start!
        }
        tim->ARR = reload;
    }
}

void timerEnableInterrupt(TIM_TypeDef *tim)
{
    tim->DIER |= 1;
}

void timerStart(TIM_TypeDef *tim)
{
    tim->CR1 |= TIM_CR1_CEN;
}

void timerStop(TIM_TypeDef *tim)
{
    tim->CR1 &= ~1;
}
