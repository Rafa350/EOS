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
	void SPI_1_InterruptHandler();
#endif
#ifdef HTL_SPI2_EXIST
	void SPI_2_InterruptHandler();
#endif
#ifdef HTL_SPI3_EXIST
	void SPI_3_InterruptHandler();
#endif
#ifdef HTL_SPI4_EXIST
	void SPI_4_InterruptHandler();
#endif
#ifdef HTL_SPI5_EXIST
	void SPI_5_InterruptHandler();
#endif
#ifdef HTL_SPI6_EXIST
	void SPI_6_InterruptHandler();
#endif
	
#ifdef __cplusplus
}
#endif


#endif // __STM32_htlSPI_IRQ__
