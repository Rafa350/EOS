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
	void TMRDevice1_InterruptHandler();
#endif
#ifdef HTL_TMR2_EXIST
	void TMRDevice2_InterruptHandler();
#endif
#ifdef HTL_TMR3_EXIST
	void TMRDevice3_InterruptHandler();
#endif
#ifdef HTL_TMR4_EXIST
	void TMRDevice4_InterruptHandler();
#endif
#ifdef HTL_TMR5_EXIST
	void TMRDevice5_InterruptHandler();
#endif
#ifdef HTL_TMR6_EXIST
	void TMRDevice6_InterruptHandler();
#endif
#ifdef HTL_TMR7_EXIST
	void TMRDevice7_InterruptHandler();
#endif
#ifdef HTL_TMR8_EXIST
	void TMRDevice8_InterruptHandler();
#endif
#ifdef HTL_TMR9_EXIST
	void TMRDevice9_InterruptHandler();
#endif
#ifdef HTL_TMR10_EXIST
	void TMRDevice10_InterruptHandler();
#endif
#ifdef HTL_TMR11_EXIST
	void TMRDevice11_InterruptHandler();
#endif
#ifdef HTL_TMR12_EXIST
	void TMRDevice12_InterruptHandler();
#endif
#ifdef HTL_TMR13_EXIST
	void TMRDevice13_InterruptHandler();
#endif
#ifdef HTL_TMR14_EXIST
	void TMRDevice14_InterruptHandler();
#endif
#ifdef HTL_TMR15_EXIST
	void TMRDevice15_InterruptHandler();
#endif
#ifdef HTL_TMR16_EXIST
	void TMRDevice16_InterruptHandler();
#endif
#ifdef HTL_TMR17_EXIST
	void TMRDevice17_InterruptHandler();
#endif
	
#ifdef __cplusplus
}
#endif


#endif // __STM32_htlTMR_IRQ__
