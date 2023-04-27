#pragma once
#ifndef __STM32_htlSPI_IRQ__
#define __STM32_htlSPI_IRQ__


// EOS includes
//
#include "HTL/htl.h"


#ifdef __cplusplus
extern "C" {
#endif

#ifdef HTL_SPI1_EXIST
	void SPIDevice1_InterruptHandler();
#endif
#ifdef HTL_SPI2_EXIST
	void SPIDevice2_InterruptHandler();
#endif
#ifdef HTL_SPI3_EXIST
	void SPIDevice3_InterruptHandler();
#endif
#ifdef HTL_SPI4_EXIST
	void SPIDevice4_InterruptHandler();
#endif
#ifdef HTL_SPI5_EXIST
	void SPIDevice5_InterruptHandler();
#endif
#ifdef HTL_SPI6_EXIST
	void SPIDevice6_InterruptHandler();
#endif
	
#ifdef __cplusplus
}
#endif


#endif // __STM32_htlSPI_IRQ__
