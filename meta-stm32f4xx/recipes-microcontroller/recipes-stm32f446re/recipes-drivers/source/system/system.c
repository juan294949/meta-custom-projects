/**
 ******************************************************************************
 * @file    stm32f4xx_hrcc.c
 * @author  MCD Application Team
 * @version V1.4.0
 * @date    14-August-2015
 * @brief   RCC HAL module driver.
 *          This file provides firmware functions to manage the following
 *          functionalities of the Reset and Clock Control (RCC) peripheral:
 *           + Initialization and de-initialization functions
 *           + Peripheral Control functions
 *
 @verbatim
 ==============================================================================
 ##### RCC specific features #####
 ==============================================================================
 [..]
 After reset the device is running from Internal High Speed oscillator
 (HSI 16MHz) with Flash 0 wait state, Flash prefetch buffer, D-Cache
 and I-Cache are disabled, and all peripherals are off except internal
 SRAM, Flash and JTAG.
 (+) There is no prescaler on High speed (AHB) and Low speed (APB) busses;
 all peripherals mapped on these busses are running at HSI speed.
 (+) The clock for all peripherals is switched off, except the SRAM and FLASH.
 (+) All GPIOs are in input floating state, except the JTAG pins which
 are assigned to be used for debug purpose.

 [..]
 Once the device started from reset, the user application has to:
 (+) Configure the clock source to be used to drive the System clock
 (if the application needs higher frequency/performance)
 (+) Configure the System clock frequency and Flash settings
 (+) Configure the AHB and APB busses prescalers
 (+) Enable the clock for the peripheral(s) to be used
 (+) Configure the clock source(s) for peripherals which clocks are not
 derived from the System clock (I2S, RTC, ADC, USB OTG FS/SDIO/RNG)

 ##### RCC Limitations #####
 ==============================================================================
 [..]
 A delay between an RCC peripheral clock enable and the effective peripheral
 enabling should be taken into account in order to manage the peripheral read/write
 from/to registers.
 (+) This delay depends on the peripheral mapping.
 (+) If peripheral is mapped on AHB: the delay is 2 AHB clock cycle
 after the clock enable bit is set on the hardware register
 (+) If peripheral is mapped on APB: the delay is 2 APB clock cycle
 after the clock enable bit is set on the hardware register

 [..]
 Possible Workarounds:
 (#) Enable the peripheral clock sometimes before the peripheral read/write
 register is required.
 (#) For AHB peripheral, insert two dummy read to the peripheral register.
 (#) For APB peripheral, insert a dummy read to the peripheral register.

 @endverbatim
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

#include "system.h"

#define __RCC_GET_PLL_OSCSOURCE() ((uint32_t)(RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC))

const uint8_t APBAHBPrescTable[16] =
{
		0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9
};

uint32_t systemGetSysClock(void)
{

//    RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC
    uint32_t pllm = 0u;
    uint32_t pllvco = 0u;
    uint32_t pllp = 0u;
    uint32_t sysClock = 0u;

    switch (RCC->CFGR & RCC_CFGR_SWS)
    {
        case RCC_CFGR_SWS_HSI:
        {
            sysClock = HSI_VALUE;    // High-speed internal = 16MHz
            break;
        }

        case RCC_CFGR_SWS_HSE:
        {
            sysClock = HSE_VALUE;    // High-speed external = 25MHz (max.)
        }

        case RCC_CFGR_SWS_PLL:
        {
            pllm = RCC->PLLCFGR & RCC_PLLCFGR_PLLM;
        }

            if (__RCC_GET_PLL_OSCSOURCE() != RCC_PLLCFGR_PLLSRC_HSI)
            {
                /* HSE used as PLL clock source */
                pllvco = (uint32_t) ((((uint64_t) HSE_VALUE
                        * ((uint64_t) ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN)
                                >> RCC_PLLCFGR_PLLN_Pos)))) / (uint64_t) pllm);
            }
            else
            {
                /* HSI used as PLL clock source */
                pllvco = (uint32_t) ((((uint64_t) HSI_VALUE
                        * ((uint64_t) ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN)
                                >> RCC_PLLCFGR_PLLN_Pos)))) / (uint64_t) pllm);
            }
            pllp = ((((RCC->PLLCFGR & RCC_PLLCFGR_PLLP) >> RCC_PLLCFGR_PLLP_Pos)
                    + 1U) * 2U);

            sysClock = pllvco / pllp;
            break;

        default:
        {
            sysClock = HSI_VALUE;
            break;
        }
    }

    return sysClock;
}

uint32_t systemGetHclkFreq(void)
{
    SystemCoreClock = systemGetSysClock()
            >> APBAHBPrescTable[(RCC->CFGR & RCC_CFGR_HPRE)
            >> POSITION_VAL(RCC_CFGR_HPRE)];
    return SystemCoreClock;
}

uint32_t systemGetPclk1Freq(void)
{
    /* Get HCLK source and Compute PCLK1 frequency ---------------------------*/
    return (systemGetHclkFreq()
            >> APBAHBPrescTable[(RCC->CFGR & RCC_CFGR_PPRE1)
            >> POSITION_VAL(RCC_CFGR_PPRE1)]);
}

uint32_t systemGetPclk2Freq(void)
{
    /* Get HCLK source and Compute PCLK2 frequency ---------------------------*/
    return (systemGetHclkFreq()
            >> APBAHBPrescTable[(RCC->CFGR & RCC_CFGR_PPRE2)
            >> POSITION_VAL(RCC_CFGR_PPRE2)]);
}
