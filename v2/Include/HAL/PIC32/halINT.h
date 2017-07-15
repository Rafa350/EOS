#ifndef __PIC32_halINT__
#define __PIC32_halINT__


#include "xc.h"


#define halINTEnableInterrupts() \
	__builtin_enable_interrupts()

#define halINTDisableInterrupts() \
	__builtin_disable_interrupts()


#endif // __PIC32_halINT__

