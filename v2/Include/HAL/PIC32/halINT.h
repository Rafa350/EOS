#ifndef __PIC32_halINT__
#define __PIC32_halINT__


#include "eos.h"


#define halINTEnableInterrupts() \
	__builtin_enable_interrupts()

#define halINTDisableInterrupts() \
	__builtin_disable_interrupts()

// Prioritats de les interrupcions
#define HAL_INT_PRIORITY_LEVEL0       0
#define HAL_INT_PRIORITY_LEVEL1       1
#define HAL_INT_PRIORITY_LEVEL2       2
#define HAL_INT_PRIORITY_LEVEL3       3
#define HAL_INT_PRIORITY_LEVEL4       4
#define HAL_INT_PRIORITY_LEVEL5       5
#define HAL_INT_PRIORITY_LEVEL6       6
#define HAL_INT_PRIORITY_LEVEL7       7

// Subprioritats de les interrupcions
#define HAL_INT_SUBPRIORITY_LEVEL0    0
#define HAL_INT_SUBPRIORITY_LEVEL1    1
#define HAL_INT_SUBPRIORITY_LEVEL2    2
#define HAL_INT_SUBPRIORITY_LEVEL3    3

// Interrupcions
#define HAL_INT_SOURCE_TMR1           _TIMER_1_IRQ
#define HAL_INT_SOURCE_TMR2           _TIMER_2_IRQ
#define HAL_INT_SOURCE_TMR3           _TIMER_3_IRQ
#define HAL_INT_SOURCE_TMR4           _TIMER_4_IRQ
#define HAL_INT_SOURCE_TMR5           _TIMER_5_IRQ


typedef uint32_t INTSource;


void halINTSetInterruptPriority(INTSource source, unsigned priority, unsigned subPriority);
void halINTEnableInterrupt(INTSource source);
bool halINTDisableInterrupt(INTSource source);
void halINTRestoreInterrupt(INTSource source, bool state);
bool halINTGetInterruptFlag(INTSource source);
void halINTClearInterruptFlag(INTSource source);


#endif // __PIC32_halINT__

