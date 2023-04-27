#pragma once
#ifndef __STM32_htlLTDC_IRQ__
#define __STM32_htlLTDC_IRQ__


// EOS includes
//
#include "HTL/htl.h"


#ifdef __cplusplus
extern "C" {
#endif
	void LTDCDevice_InterruptHandler();
	void LTDCDevice_InterruptHandler_ER();
#ifdef __cplusplus
}
#endif


#endif // __STM32_htlLTDC_IRQ__
