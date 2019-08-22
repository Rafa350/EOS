#ifndef __STM32_halINT__
#define __STM32_halINT__


// EOS includes
//
#include "eos.h"


#if defined (EOS_STM32F4)
#include "stm32f4xx.h"
#elif defined(EOS_STM32F7)
#include "stm32f7xx.h"
#endif


#define halINTEnableInterrupts() \
	__enable_irq()

#define halINTDisableInterrupts() \
	__disable_irq()


#endif // __STM32_halINT__

