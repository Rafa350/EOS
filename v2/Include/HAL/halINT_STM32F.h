#ifndef __EOS_HAL_INT_STM32F_H
#define __EOS_HAL_INT_STM32F_H


#include "stm32f4xx.h"


#define halINTEnableInterrupts() \
	__enable_irq()

#define halINTDisableInterrupts() \
	__disable_irq()


#endif

