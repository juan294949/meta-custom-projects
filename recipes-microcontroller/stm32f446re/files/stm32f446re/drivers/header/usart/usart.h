#ifndef USART_H
	#define USART_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "stm32f4xx.h"

#include "system.h"

/* Defines */
#define BUFFERSIZE  (128)

/* Typedefs */
typedef struct
{
    uint8_t inPtr;
    uint8_t outPtr;
    uint8_t buffer[BUFFERSIZE];
} USART_BUFFER_t;

typedef enum
{
    USART_ENABLE = 0,
    USART_DISABLE
} USART_MODE_t;

typedef enum
{
    NO_PARITY = 0,
    EVEN_PARITY,
    ODD_PARITY
} USART_PARITY;

typedef enum
{
    LEN_8BIT = 0,
    LEN_9BIT
} USART_WORDLEN;

typedef enum
{
    HALF_BIT        = 0,
    HALF_STOP       = 0,
    ONE_BIT         = 1,
    ONE_STOP        = 1,
    ONE_DOT_FIVE    = 2,
    TWO_BIT         = 3,
    TWO_STOP        = 3
} USART_STOPBITS;

typedef enum
{
    OVER16 = 0,
    OVER8
} USART_OVER;

typedef enum
{
    RECEIVER_OFF = 0,
    RECEIVER_ON
} USART_RX;

typedef enum
{
    TRANSMITTER_OFF = 0,
    TRANSMITTER_ON
} USART_TX;

typedef enum
{
    OFF = 0,
    ON
} USART_IRQ_MODE;

typedef enum
{
    USART_IRQ_TXEIE = 0,
    USART_IRQ_CTSIE,
    USART_IRQ_TCIE,
    USART_IRQ_RXNEIE,
    USART_IRQ_IDLE,
    USART_IRQ_PEIE,
    USART_IRQ_LBDIE,
    USART_IRQ_EIE
} USART_IRQ_TYPES;

typedef enum
{
    USART_CTS_FLG,
    USART_LBD_FLG,
    USART_TC_FLG,
    USART_RXNE_FLG
} USART_IRQ_FLAG_t;

typedef enum
{
    DMA_TRANSMIT_OFF,
    DMA_TRANSMIT_ON
} USART_DMA_TXMODE_t;

typedef enum
{
    DMA_RECEIVE_OFF,
    DMA_RECEIVE_ON
} USART_DMA_RXMode_t;

/* Function prototypes */

/* General UART/USART */
void usartEnableUsart  (USART_TypeDef *usart);
void usartStartUsart   (USART_TypeDef *usart);
void usartDisableUsart (USART_TypeDef *usart);
void usartSelectUsart  (USART_TypeDef *usart);
void usartDeselectUsart(USART_TypeDef *usart);

/* Interrupts */
void usartEnableIrq	  (USART_TypeDef *usart, USART_IRQ_TYPES irqType);
void usartDisableIrq	  (USART_TypeDef *usart, USART_IRQ_TYPES irqType);
void usartResetIrqFlag (USART_TypeDef *usart, USART_IRQ_FLAG_t irqFlag);
void usartEnableIrqList(USART_TypeDef *usart, USART_IRQ_TYPES *irqList);

/* Communication parameters */
void usartSetBaudrate    (USART_TypeDef *usart, uint32_t baudrate);
void usartSetCommParams  (USART_TypeDef *usart, uint32_t baudrate,
							 USART_PARITY parity,  USART_WORDLEN len,
							 USART_STOPBITS num);
void usartSetWordlength	(USART_TypeDef *usart, USART_WORDLEN len);
void usartSetParity		(USART_TypeDef *usart, USART_PARITY parity);
void usartSetNumStopBits	(USART_TypeDef *usart, USART_STOPBITS num);
void usartSetOversampling(USART_TypeDef *usart, USART_OVER over);
void usartEnableReceiver	(USART_TypeDef *usart, USART_RX enable);
void usartEnableTransmitter(USART_TypeDef *usart, USART_TX enable);

/* USART buffer */
void usartSendString(USART_TypeDef *usart, char *data);
void usartInitBuffer(void);

/* DMA */
void usartSetDmaTxMode(USART_TypeDef *usart, USART_DMA_TXMODE_t dmaMode);
void usartSetDmaRxMode(USART_TypeDef *usart, USART_DMA_RXMode_t dmaMode);

#endif
