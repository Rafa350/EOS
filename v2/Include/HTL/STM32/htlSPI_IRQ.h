#pragma once
#ifndef __STM32_htlSPI_IRQ__
#define __STM32_htlSPI_IRQ__


// EOS includes
//
#include "HTL/htl.h"


#ifdef __cplusplus
extern "C" {
#endif
	void SPI_1_InterruptHandler();
	void SPI_2_InterruptHandler();
	void SPI_3_InterruptHandler();
	void SPI_4_InterruptHandler();
	void SPI_5_InterruptHandler();
	void SPI_6_InterruptHandler();
#ifdef __cplusplus
}
#endif


#endif // __STM32_htlLTDC_IRQ__
