#ifndef __EOS_HAL_PIC32_INT_H
#define __EOS_HAL_PIC32_INT_H


#include "xc.h"


#define halINTEnableInterrupts() \
	__builtin_enable_interrupts()

#define halINTDisableInterrupts() \
	__builtin_disable_interrupts()


#endif

