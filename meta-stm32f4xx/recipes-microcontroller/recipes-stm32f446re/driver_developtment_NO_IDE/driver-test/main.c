#include "stm32f4xx.h"
#include "system_stm32f4xx.h"
#include "stm32f4xx_hal_spi.h"

#define HAL_SPI_MODULE_ENABLED
#define MIN_DATA 1


int main(void)
{
	const char pBufferTX[] = " Testing my SPI";
	uint16_t txCounter = 0;
	HAL_SPI_StateTypeDef StatusVal;
	uint16_t RetErrorCode;
	SPI_HandleTypeDef SpiCOnfig = {
									.Instance=SPI1_BASE,
									.Init=
									{
										.Mode=SPI_MODE_MASTER,
										.Direction=SPI_DIRECTION_2LINES,
										.DataSize=SPI_DATASIZE_8BIT,
										.CLKPolarity=SPI_POLARITY_LOW,
										.CLKPhase=SPI_PHASE_1EDGE,
										.NSS=SPI_NSS_HARD_OUTPUT,
										.BaudRatePrescaler=SPI_BAUDRATEPRESCALER_4,
										.FirstBit=SPI_FIRSTBIT_MSB,
										.TIMode=SPI_TIMODE_DISABLE,
										.CRCCalculation=SPI_CRCCALCULATION_DISABLE,
										.CRCPolynomial=MIN_DATA
									},
									.pTxBuffPtr=pBufferTX,
									.TxXferSize=((uint16_t)sizeof(pBufferTX)/sizeof(*pBufferTX)),
									.TxXferCount=txCounter,
									.pRxBuffPtr=NULL,
									.RxXferCount=0,
									.RxXferSize=0,
									.TxISR=NULL,
									.RxISR=NULL,
									.hdmatx=NULL,
									.hdmarx=NULL,
									.Lock=HAL_UNLOCKED,
									.State=StatusVal,
									.ErrorCode=RetErrorCode
								};
	HAL_SPI_Init(&SpiCOnfig);

	while(1);
	return 0;
}
