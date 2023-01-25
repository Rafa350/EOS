#pragma once
#ifndef __STM32_htlTMR_IRQ__
#define __STM32_htlTMR_IEQ__


// EOS includes
//
#include "HTL/htl.h"


#ifdef __cplusplus
extern "C" {
#endif

#ifdef HTL_TMR1_EXIST
	void TMR_1_InterruptHandler();
#endif
#ifdef HTL_TMR2_EXIST
	void TMR_2_InterruptHandler();
#endif
#ifdef HTL_TMR3_EXIST
	void TMR_3_InterruptHandler();
#endif
#ifdef HTL_TMR4_EXIST
	void TMR_4_InterruptHandler();
#endif
#ifdef HTL_TMR5_EXIST
	void TMR_5_InterruptHandler();
#endif
#ifdef HTL_TMR6_EXIST
	void TMR_6_InterruptHandler();
#endif
#ifdef HTL_TMR7_EXIST
	void TMR_7_InterruptHandler();
#endif
#ifdef HTL_TMR8_EXIST
	void TMR_8_InterruptHandler();
#endif
#ifdef HTL_TMR9_EXIST
	void TMR_9_InterruptHandler();
#endif
#ifdef HTL_TMR10_EXIST
	void TMR_10_InterruptHandler();
#endif
#ifdef HTL_TMR11_EXIST
	void TMR_11_InterruptHandler();
#endif
#ifdef HTL_TMR12_EXIST
	void TMR_12_InterruptHandler();
#endif
#ifdef HTL_TMR13_EXIST
	void TMR_13_InterruptHandler();
#endif
#ifdef HTL_TMR14_EXIST
	void TMR_14_InterruptHandler();
#endif
	
#ifdef __cplusplus
}
#endif


#endif // __STM32_htlTMR_IRQ__
