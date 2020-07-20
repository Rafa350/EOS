#ifndef __PIC32_halINT__
#define __PIC32_halINT__


#include "eos.h"


#define halINTEnableInterrupts() \
	__builtin_enable_interrupts()

#define halINTDisableInterrupts() \
	__builtin_disable_interrupts()


#define HAL_INT_PRIORITY_LEVEL0       0
#define HAL_INT_PRIORITY_LEVEL1       1
#define HAL_INT_PRIORITY_LEVEL2       2
#define HAL_INT_PRIORITY_LEVEL3       3
#define HAL_INT_PRIORITY_LEVEL4       4
#define HAL_INT_PRIORITY_LEVEL5       5
#define HAL_INT_PRIORITY_LEVEL6       6
#define HAL_INT_PRIORITY_LEVEL7       7

#define HAL_INT_SUBPRIORITY_LEVEL0    0
#define HAL_INT_SUBPRIORITY_LEVEL1    1
#define HAL_INT_SUBPRIORITY_LEVEL2    2
#define HAL_INT_SUBPRIORITY_LEVEL3    3


void halINTEnable();
unsigned halINTDisable();
void halINTRestore(unsigned state);


#endif // __PIC32_halINT__

