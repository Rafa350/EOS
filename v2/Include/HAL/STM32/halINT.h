#ifndef __STM32_halINT__
#define __STM32_halINT__


#include "stm32f4xx.h"


#define halINTEnableInterrupts() \
	__enable_irq()

#define halINTDisableInterrupts() \
	__disable_irq()


#endif // __STM32_halINT__

