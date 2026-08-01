#include "usart.h"

#define USART_TX_EMPTY(usart)  ((usart)->SR & USART_SR_TXE)
#define USART_WAIT(usart)      do { while(!USART_TX_EMPTY(usart)); } while(0)

/* Variables */
USART_BUFFER_t  *receiveBuffer;
USART_BUFFER_t  *transmitBuffer;

void usartEnableUsart(USART_TypeDef *usart)
{
    if (USART1 == usart)
    {
        USART1->CR1 |= USART_CR1_UE;
    }
    else if (USART2 == usart)
    {
        USART2->CR1 |= USART_CR1_UE;
    }
    else if (USART3 == usart)
    {
        USART3->CR1 |= USART_CR1_UE;
    }
    else if (UART4 == usart)
    {
        UART4->CR1 |= USART_CR1_UE;
    }
    else if (UART5 == usart)
    {
        UART5->CR1 |= USART_CR1_UE;
    }
    else if (USART6 == usart)
    {
        USART6->CR1 |= USART_CR1_UE;
    }
}

void usartStartUsart(USART_TypeDef *usart)
{
    if (USART1 == usart)
    {
        USART1->CR1 |= USART_CR1_UE;
    }
    else if (USART2 == usart)
    {
        USART2->CR1 |= USART_CR1_UE;
    }
    else if (USART3 == usart)
    {
        USART3->CR1 |= USART_CR1_UE;
    }
    else if (UART4 == usart)
    {
        UART4->CR1 |= USART_CR1_UE;
    }
    else if (UART5 == usart)
    {
        UART5->CR1 |= USART_CR1_UE;
    }
    else if (USART6 == usart)
    {
        USART6->CR1 |= USART_CR1_UE;
    }
}

void usartDisableUsart(USART_TypeDef *usart)
{
    if (USART1 == usart)
    {
        USART1->CR1 &= ~USART_CR1_UE_Msk;
    }
    else if (USART2 == usart)
    {
        USART2->CR1 &= ~USART_CR1_UE_Msk;
    }
    else if (USART3 == usart)
    {
        USART3->CR1 &= ~USART_CR1_UE_Msk;
    }
    else if (UART4 == usart)
    {
        UART4->CR1 &= ~USART_CR1_UE_Msk;
    }
    else if (UART5 == usart)
    {
        UART5->CR1 &= ~USART_CR1_UE_Msk;
    }
    else if (USART6 == usart)
    {
        USART6->CR1 &= ~USART_CR1_UE_Msk;
    }
}

void usartSelectUsart(USART_TypeDef *usart)
{
    if (USART1 == usart)
    {
        RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    }

    if (USART2 == usart)
    {
        RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    }

    if (USART3 == usart)
    {
        RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
    }

    if (UART4 == usart)
    {
        RCC->APB1ENR |= RCC_APB1ENR_UART4EN;
    }

    if (UART5 == usart)
    {
        RCC->APB1ENR |= RCC_APB1ENR_UART5EN;
    }

    if (USART6 == usart)
    {
        RCC->APB2ENR |= RCC_APB2ENR_USART6EN;
    }
}

void usartDeselectUsart(USART_TypeDef *usart)
{
    if (USART1 == usart)
    {
        RCC->APB2ENR &= ~RCC_APB2ENR_USART1EN;
    }

    if (USART2 == usart)
    {
        RCC->APB1ENR &= ~RCC_APB1ENR_USART2EN;
    }

    if (USART3 == usart)
    {
        RCC->APB1ENR &= ~RCC_APB1ENR_USART3EN;
    }

    if (UART4 == usart)
    {
        RCC->APB1ENR &= ~RCC_APB1ENR_UART4EN;
    }

    if (UART5 == usart)
    {
        RCC->APB1ENR &= ~RCC_APB1ENR_UART5EN;
    }

    if (USART6 == usart)
    {
        RCC->APB2ENR &= ~RCC_APB2ENR_USART6EN;
    }
}

void usartEnableIrq(USART_TypeDef *usart, USART_IRQ_TYPES irqType)
{
    switch (irqType)
    {
        /* Transmit buffer empty */
        case USART_IRQ_TXEIE:
            usart->CR1 |= USART_CR1_TXEIE;
            break;

        /* Clear-to-send */
        case USART_IRQ_CTSIE:
            usart->CR3 |= USART_CR3_CTSIE;
            break;

        /* Transmission complete */
        case USART_IRQ_TCIE:
            usart->CR1 |= USART_CR1_TCIE;
            break;

        /* Error: Detects framing/overrun/noise errors */
        case USART_IRQ_EIE:
            usart->CR3 |= USART_CR3_EIE;
            break;

        /* Receive buffer not empty */
        case USART_IRQ_RXNEIE:
            usart->CR1 |= USART_CR1_RXNEIE;
            break;

        /* UART/USART idle (no activity) */
        case USART_IRQ_IDLE:
            usart->CR1 |= USART_CR1_IDLEIE;
            break;

        /* Parity error */
        case USART_IRQ_PEIE:
            usart->CR1 |= USART_CR1_PEIE;
            break;

        /* Line break */
        case USART_IRQ_LBDIE:
            break;
    }
}

void usartDisableIrq(USART_TypeDef *usart, USART_IRQ_TYPES irqType)
{
    switch (irqType)
    {
        /* Transmit buffer empty */
        case USART_IRQ_TXEIE:
            usart->CR1 &= ~USART_CR1_TXEIE_Msk;
            break;

        /* Clear-to-send */
        case USART_IRQ_CTSIE:
            usart->CR3 &= ~USART_CR3_CTSIE_Msk;
            break;

        /* Transmission complete */
        case USART_IRQ_TCIE:
            usart->CR1 &= ~USART_CR1_TCIE_Msk;
            break;

        /* Error: Detects framing/overrun/noise errors */
        case USART_IRQ_EIE:
            usart->CR3 &= ~USART_CR3_EIE_Msk;
            break;

        /* Receive buffer not empty */
        case USART_IRQ_RXNEIE:
            usart->CR1 &= ~USART_CR1_RXNEIE_Msk;
            break;

        /* UART/USART idle (no activity) */
        case USART_IRQ_IDLE:
            usart->CR1 &= ~USART_CR1_IDLEIE_Msk;
            break;

        /* Parity error */
        case USART_IRQ_PEIE:
            usart->CR1 &= ~USART_CR1_PEIE_Msk;
            break;

        /* Line break */
        case USART_IRQ_LBDIE:
            usart->CR2 &= ~USART_CR2_LBDIE_Msk;
            break;
    }
}

void usartSetBaudrate(USART_TypeDef *usart, uint32_t baudrate)
{
    uint32_t systemClock = 0u;
    uint8_t  over = 0;
    uint32_t baudRateMantissa = 0.0f;
    uint32_t baudRateFraction = 0.0f;

    SystemCoreClockUpdate();
    systemClock = systemGetSysClock();

    over = usart->CR1 & USART_CR1_OVER8;

    baudRateMantissa = (systemClock / (8 * (2 - over) * baudrate));    // Korrekt = 104 bei 9600 bps @ 16 MHz
    baudRateFraction = (systemClock - (baudRateMantissa * 8 * (2 - over) * baudrate)) / baudrate;

    usart->BRR = baudRateMantissa << 4 | baudRateFraction;
}

void usartSetCommParams(	USART_TypeDef *usart,
                        	uint32_t baudrate,
							USART_PARITY parity,
							USART_WORDLEN len,
							USART_STOPBITS num)
{
    usartSelectUsart(usart);
    usartSetBaudrate(usart, baudrate);              // Set baudrate
    usartEnableUsart(usart);
    usartSetWordlength(usart, len);
    usartSetNumStopBits(usart, num);
    usartSetParity(usart, parity);
    usartEnableReceiver(usart, RECEIVER_ON);        // Always activate receiver ...
    usartEnableTransmitter(usart, TRANSMITTER_ON);  // ... and transmitter
}

void usartSetWordlength(USART_TypeDef *usart, USART_WORDLEN len)
{
    if (LEN_8BIT == len)
    {
        usart->CR1 &= ~USART_CR1_M;
    }
    else
    {
        usart->CR1 |= USART_CR1_M;
    }
}

void usartSetParity(USART_TypeDef *usart, USART_PARITY parity)
{
    if (NO_PARITY == parity)
    {
        usart->CR1 &= ~USART_CR1_PCE;       // No parity
    }
    else
    {
        if (EVEN_PARITY == parity)
        {
            usart->CR1 |= USART_CR1_PCE;
            usart->CR1 &= ~USART_CR1_PS;    // Even parity
        }
        else
        {
            usart->CR1 |= USART_CR1_PCE;
            usart->CR1 |= USART_CR1_PS;     // Odd parity
        }
    }
}

void usartSetNumStopBits(USART_TypeDef *usart, USART_STOPBITS num)
{
    usart->CR2 &= ~USART_CR2_STOP_Msk;          // Default: 1 stop bit

    switch (num)
    {
        case HALF_BIT:
            usart->CR2 |= USART_CR2_STOP_0;     // 0.5 stop bits
            break;

        case ONE_BIT:
            usart->CR2 &= ~USART_CR2_STOP_Msk;  // 1 stop bit
            break;

        case ONE_DOT_FIVE:
            usart->CR2 |= USART_CR2_STOP_1;     // 1.5 stop bits
            break;

        case TWO_BIT:
            usart->CR2 |= USART_CR2_STOP;       // 2 stop bits

        default:
            usart->CR2 &= ~USART_CR2_STOP_Msk;  // 1 stop bit
            break;
    }
}

void usartSetOversampling(USART_TypeDef *usart, USART_OVER over)
{
    usart->CR1 &= ~USART_CR1_OVER8_Msk;         // Default is 16x

    if (OVER8 == over)
    {
        usart->CR1 |= USART_CR1_OVER8;
    }
}

void usartEnableReceiver(USART_TypeDef *usart, USART_RX enable)
{
    if (RECEIVER_OFF == enable)
    {
        usart->CR1 &= ~USART_CR1_RE_Msk;
    }
    else
    {
        usart->CR1 |= USART_CR1_RE;
    }
}

void usartEnableTransmitter(USART_TypeDef *usart, USART_TX enable)
{
    if (TRANSMITTER_OFF == enable)
    {
        usart->CR1 &= ~USART_CR1_TE_Msk;
    }
    else
    {
        usart->CR1 |= USART_CR1_TE;
    }
}

void usartEnableIrqList(USART_TypeDef *usart, USART_IRQ_TYPES *irqList)
{
    uint8_t         i = 0;
    size_t          numIrqs = 0;
    USART_IRQ_TYPES irqType;

    numIrqs = sizeof(irqList);
    for (i = 0; i < numIrqs; i++)
    {
        irqType = irqList[i];
        usartEnableIrq(usart, irqType);
    }
}

void usartSendString(USART_TypeDef *usart, char *data)
{
    while (*data)
    {
        USART_WAIT(usart);
        usart->DR = *data++ & 0x01FF;
        USART_WAIT(usart);
    }
}

void usartInitBuffer(void)
{
    transmitBuffer->inPtr  = 0;
    transmitBuffer->outPtr = 0;

    receiveBuffer->inPtr   = 0;
    receiveBuffer->outPtr  = 0;
}

void usartResetIrqFlag(USART_TypeDef *usart, USART_IRQ_FLAG_t irqFlag)
{
    switch (irqFlag)
    {
        case USART_CTS_FLG:
            usart->SR &= ~USART_SR_TC_Msk;
            break;
        case USART_LBD_FLG:
            usart->SR &= ~USART_SR_LBD_Msk;
            break;
        case USART_TC_FLG:
            usart->SR &= ~USART_SR_TC_Msk;
            break;
        case USART_RXNE_FLG:
            usart->SR &= ~USART_SR_RXNE_Msk;
            break;

        default:
            break;
    }
}

void usartSetDmaTxMode(USART_TypeDef *usart, USART_DMA_TXMODE_t dmaMode)
{
    if (DMA_TRANSMIT_OFF == dmaMode)
    {
        usart->CR3 &= ~USART_CR3_DMAT_Msk;
    }
    else
    {
        usart->CR3 |= USART_CR3_DMAT;
    }
}

void usartSetDmaRxMode(USART_TypeDef *usart, USART_DMA_RXMode_t dmaMode)
{
    if (DMA_RECEIVE_OFF == dmaMode)
    {
        usart->CR3 &= ~USART_CR3_DMAR_Msk;
    }
    else
    {
        usart->CR3 |= USART_CR3_DMAR;
    }
}
