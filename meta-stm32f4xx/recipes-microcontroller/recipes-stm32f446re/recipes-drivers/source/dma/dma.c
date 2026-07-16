#include "../../CMSIS/Device/Include/stm32f446xx.h"
#include "../../header/dma/dma.h"
#include "../../header/common/common.h"

/***********************************************************************************************
* @brief Enables the DMA module selected from DmaSelectEnum.
* The two DMA controllers (DMA1, DMA2) have 8 streams each, dedicated to managing
* memory access requests from one or more peripherals.Dual AHB master bus architecture, 
* one dedicated to memory accesses and one dedicated to peripheral accesses
* DMA1: peripherals.
* DMA2: memory to memory.
* @param dma Receives a enumeration from DmaSelectEnum with the selected DMA to enable.
*
************************************************************************************************/
inline DmaStatusEnum enable_dma_module(DmaSelectEnum dma)
{
  DmaStatusEnum ret_status = -1;
  
  switch (dma)
  {
    case DMA_SELECT_1:
    {
      /* configure clock source.*/
      if((RCC->AHB1ENR & (RCC_AHB1ENR_DMA1EN)) != RCC_AHB1ENR_DMA1EN)
      {
      	RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;
      	/* check again if read as disabled*/
      	ret_status = ((RCC->AHB1ENR & (RCC_AHB1ENR_DMA1EN)) == RCC_AHB1ENR_DMA1EN) ? DMA_ENABLED:DMA_DISABLED;
      }
      break;
    }
    case DMA_SELECT_2:
    {
      /* configure clock source.*/
      if((RCC->AHB1ENR & (RCC_AHB1ENR_DMA2EN)) != RCC_AHB1ENR_DMA2EN)
      {
      	RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN; 
      	/* check again if read as disabled*/
      	ret_status = ((RCC->AHB1ENR & (RCC_AHB1ENR_DMA2EN)) == RCC_AHB1ENR_DMA2EN) ? DMA_ENABLED:DMA_DISABLED;
      }
      break;
    }
    default:
    {
      ret_status = INVALID_DMA;
      break;
    }
  }
  return ret_status;
}


/***********************************************************************************************
* @brief 
* @param dma
*
************************************************************************************************/
DmaStatusEnum dma_init(DmaSelectEnum dma)
{
  DmaStatusEnum Ret_status = DMA_DISABLED;

  /* Check if the clock source for the DMAx has been inititalized.*/
  switch(dma)
  {
    case DMA_SELECT_1:
    {
      if((RCC->AHB1ENR & (RCC_AHB1ENR_DMA1EN)) != RCC_AHB1ENR_DMA1EN)
      {
        Ret_status = enable_dma_module(DMA_SELECT_1); /* Initialize the DMA that is required to be used.*/
      }
      else Ret_status = DMA_ENABLED;
      break;
    }
    case(DMA_SELECT_2):
    {
      if((RCC->AHB1ENR & (RCC_AHB1ENR_DMA2EN)) != RCC_AHB1ENR_DMA2EN)
      {
        Ret_status = enable_dma_module(DMA_SELECT_2); /* Initialize the DMA that is required to be used.*/
      }
      else Ret_status = DMA_ENABLED;
      break;
    }
  }

  if(Ret_status == DMA_ENABLED)
  {
    /*The following sequence must be followed to configure a DMA stream x (where x is the
    stream number):*/
    /*1).If the stream is enabled, disable it by resetting the EN bit in the DMA_SxCR register,
    then read this bit in order to confirm that there is no ongoing stream operation. Writing
    this bit to 0 is not immediately effective since it is actually written to 0 once all the
    current transfers are finished. When the EN bit is read as 0, this means that the stream
    is ready to be configured. It is therefore necessary to wait for the EN bit to be cleared
    before starting any stream configuration. All the stream dedicated bits set in the status
    register (DMA_LISR and DMA_HISR) from the previous data block DMA transfer must
    be cleared before the stream can be re-enabled.*/
    DMA_TypeDef* DMA_array[2] = {DMA1,DMA2};
    //DMA_array[dma - 1]->
  }
  return Ret_status;
}

/***********************************************************************************************
* @brief 
* @param dma
*
************************************************************************************************/
DmaStatusEnum write_memory_to_memory(uint8_t* source, uint8_t destination,uint32_t buffer_size)
{
  
}