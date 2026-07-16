#include "stm32f4xx_hal_spi.h"
#include "gpio.h"
#include <string.h>

#define WAIT_1SEC 1000
#define MIN_DATA 1
#define SPI_TIMEOUT 1000

SPI_HandleTypeDef SpiCOnfig = { 
												.Instance=SPI1, 
												.Init= 
												{ .Mode=SPI_MODE_MASTER, 
													.Direction=SPI_DIRECTION_2LINES, 
													.DataSize=SPI_DATASIZE_8BIT, 
													.CLKPolarity=SPI_POLARITY_LOW, 
													.CLKPhase=SPI_PHASE_1EDGE, 
													.NSS=SPI_NSS_SOFT, 
													.BaudRatePrescaler=SPI_BAUDRATEPRESCALER_16, 
													.FirstBit=SPI_FIRSTBIT_MSB, 
													.TIMode=SPI_TIMODE_DISABLE, 
													.CRCCalculation=SPI_CRCCALCULATION_DISABLE, 
													.CRCPolynomial=MIN_DATA 
												}, 
												.hdmatx=NULL, 
												.hdmarx=NULL,
											};

int spi_test(void)
{
	int TestStatus = 0;
	const char pBufferTX[] = " Testing SPI";
	char pBufferRX[16]={0};
	// gpioSelectPinMode(GPIOA, PIN15, ALTFUNC);      // PA2   : Modus = Alt. Funktion
	// gpioSelectAltFunc(GPIOA, PIN15, AF5);          // PA2   : AF7 = USART2 Rx
	gpioSelectPinMode(GPIOA, PIN5, ALTFUNC);      // PA3   : Modus = Alt. Funktion
	gpioSelectAltFunc(GPIOA, PIN5, AF5);          // PA3   : AF7 = USART2 Tx
	gpioSelectPinMode(GPIOA, PIN6, ALTFUNC);      // PA3   : Modus = Alt. Funktion
	gpioSelectAltFunc(GPIOA, PIN6, AF5);          // PA3   : AF7 = USART2 Tx
	gpioSelectPinMode(GPIOA, PIN7, ALTFUNC);      // PA3   : Modus = Alt. Funktion
	gpioSelectAltFunc(GPIOA, PIN7, AF5);          // PA3   : AF7 = USART2 Tx
	uint16_t txCounter = 0; 
	HAL_SPI_StateTypeDef StatusVal; 
	uint16_t RetErrorCode;

	HAL_SPI_Init(&SpiCOnfig);
	TestStatus = HAL_SPI_TransmitReceive(&SpiCOnfig,pBufferTX,pBufferRX,(uint16_t)sizeof(pBufferTX)/sizeof(*pBufferTX),WAIT_1SEC);
	TestStatus = memcmp(pBufferTX,pBufferRX,(size_t)sizeof(pBufferTX)/sizeof(*pBufferTX));

  return TestStatus;
}
