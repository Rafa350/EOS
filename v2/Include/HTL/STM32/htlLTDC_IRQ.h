#pragma once
#ifndef __STM32_htlLTDC_IRQ__
#define __STM32_htlLTDC_IRQ__


// EOS includes
//
#include "HTL/htl.h"


#ifdef __cplusplus
extern "C" {
#endif
	void LTDC_InterruptHandler();
	void LTDC_ER_InterruptHandler();
#ifdef __cplusplus
}
#endif


#endif // __STM32_htlLTDC_IRQ__