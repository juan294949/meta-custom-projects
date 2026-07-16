
#ifndef _DMA_H_
	#define _DMA_H_

typedef enum
{
	DMA_SELECT_1 = 1,
	DMA_SELECT_2 = 2

}DmaSelectEnum;

typedef enum 
{
	INVALID_DMA = -1,
	DMA_ENABLED = 0,
	DMA_DISABLED = 1,

}DmaStatusEnum;

DmaStatusEnum enable_dma_module(DmaSelectEnum dma);

#endif /* end of _DMA_H_*/