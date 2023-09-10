#pragma once
#ifndef __STM32_htlGPIO_IRQ__
#define __STM32_htlGPIO_IRQ__


// EOS includes
//
#include "HTL/htl.h"


#ifdef __cplusplus
extern "C" {
#endif
#ifdef HTL_GPIOA_EXIST
	void PortA_InterruptHandler();
#endif
#ifdef HTL_GPIOB_EXIST
	void PortB_InterruptHandler();
#endif
#ifdef HTL_GPIOC_EXIST
	void PortC_InterruptHandler();
#endif
#ifdef HTL_GPIOD_EXIST
	void PortD_InterruptHandler();
#endif
#ifdef HTL_GPIOE_EXIST
	void PortE_InterruptHandler();
#endif
#ifdef HTL_GPIOF_EXIST
	void PortF_InterruptHandler();
#endif
#ifdef HTL_GPIOG_EXIST
	void PortG_InterruptHandler();
#endif
#ifdef HTL_GPIOH_EXIST
	void PortH_InterruptHandler();
#endif
#ifdef HTL_GPIOI_EXIST
	void PortI_InterruptHandler();
#endif
#ifdef HTL_GPIOJ_EXIST
	void PortJ_InterruptHandler();
#endif
#ifdef HTL_GPIOK_EXIST
	void PortK_InterruptHandler();
#endif
#ifdef __cplusplus
}
#endif


#endif // __STM32_htlLTDC_IRQ__
