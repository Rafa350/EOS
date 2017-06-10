#ifndef __EOS_HAL_STM32_INT_H
#define __EOS_HAL_STM32_INT_H


#include "stm32f4xx.h"


#define halINTEnableInterrupts() \
	__enable_irq()

#define halINTDisableInterrupts() \
	__disable_irq()


#endif

