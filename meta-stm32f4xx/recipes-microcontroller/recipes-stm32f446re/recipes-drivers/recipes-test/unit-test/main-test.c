#include "usart-test.h"
#include "gpio-test.h"
#include "spi-test.h"

#include "wiznet-5500-spi.h"
//#include "wizchip_port.h"

#include "utility.h"
#include "gpio.h"
#include "exti.h"
#include "w5500.h"
#include "stm32f4xx_hal_def.h" 
#include "stm32f4xx_hal_spi.h"
// stm32f4xx_hal.h enables all HALL modules. 
#include "stm32f4xx_hal.h"

void NVIC_PrintStatus(void);
void initialize(void);
int main(void)
{
	/*Initialize the HAL (Hardware abstraction layer*/
	HAL_Init();
	/* Initialize Clocks that will be used in the program.*/
	initialize();

  /*Test Usart*/
  // testing only USART2 TX for now. PORTA PIN2 TX and PIN3 RX.
  char StringTest[] = "Testing Uart!\r\n";
  int TestStatus = usart_test_tx(StringTest,sizeof(StringTest)/sizeof(*StringTest));
  TestStatus > 0 ? print("From main-test.c: USART TEST: FAILED\r\n") : print("From main-test.c: USART TEST: SUCCESS\r\n");
	
  /*Test GPIO*/
  // testing on Port A pin 5
  TestStatus = gpio_test();
  TestStatus > 0 ? print("From main-test.c: GPIO TEST: FAILED\r\n") : print("From main-test.c: GPIO TEST: SUCCESS\r\n");

	/*Test SPI With HALL*/
	TestStatus = spi_test();
	TestStatus != 0 ? print("From main-test.c: SPI TEST TX: FAILED\r\n") : print("From main-test.c: SPI TEST TX: SUCCESS\r\n");

	gpioSelectPinMode(GPIOA, PIN15, OUTPUT); // Will work as the Chip select for the w5500 chip. Controlled by software.
	gpioSelectPinMode(GPIOB, PIN6, OUTPUT); // Will work as the reset pin for the w5500 chip.

	w5500_Init();
	TestStatus = w5500_ping_test();
	TestStatus != 0 ? print("From main-test.c: PING TEST: FAILED\r\n") : print("From main-test.c:  PING TEST: SUCCESS\r\n");
	
	
  while(1);

  return 0;
}

void NVIC_PrintStatus(void)
{
  print("\n===== NVIC STATUS =====\r\n");
  for (int i = 0; i < 8; i++)   // STM32F4 has up to 240 IRQs → 8 x 32
  {
    uint32_t enabled  = NVIC->ISER[i];
    uint32_t pending  = NVIC->ISPR[i];
    uint32_t active   = NVIC->IABR[i];
    if (enabled || pending || active)
    {
      print("Block %d:\r\n", i);
      print("  ENABLED : 0x%08lX\r\n", enabled);
      print("  PENDING : 0x%08lX\r\n", pending);
      print("  ACTIVE  : 0x%08lX\r\n", active);
    }
  }
}

void initialize(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_SPI1_CLK_ENABLE();
	usart2_init();
	print("systemGetHclkFreq = %d\r\n",(int)systemGetHclkFreq());
	print("systemGetPclk1Freq = %d\r\n",(int)systemGetPclk1Freq());
	print("systemGetPclk2Freq = %d\r\n ",(int)systemGetPclk2Freq());
	print("systemGetPclk2Freq = %d\r\n ",(int)systemGetSysClock());
	__enable_irq();
}