#ifndef __STM32_halINT__
#define __STM32_halINT__


// EOS includes
//
#include "eos.h"


#define halINTEnableInterrupts() \
	__enable_irq()

#define halINTDisableInterrupts() \
	__disable_irq()


#ifdef	__cplusplus
extern "C" {
#endif


void halINTSetPriority(IRQn_Type irq, uint32_t priority, uint32_t subPriority);
void halINTEnableIRQ(IRQn_Type irq);
void halINTDisableIRQ(IRQn_Type irq);


#ifdef	__cplusplus
}
#endif


#endif // __STM32_halINT__

