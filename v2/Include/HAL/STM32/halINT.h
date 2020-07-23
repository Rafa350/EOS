#ifndef __STM32_halINT__
#define __STM32_halINT__


// EOS includes
//
#include "eos.h"


#define HAL_INT_PRIORITY_LEVEL0       0
#define HAL_INT_PRIORITY_LEVEL1       1
#define HAL_INT_PRIORITY_LEVEL2       2
#define HAL_INT_PRIORITY_LEVEL3       3
#define HAL_INT_PRIORITY_LEVEL4       4
#define HAL_INT_PRIORITY_LEVEL5       5
#define HAL_INT_PRIORITY_LEVEL6       6
#define HAL_INT_PRIORITY_LEVEL7       7
#define HAL_INT_PRIORITY_LEVEL8       8
#define HAL_INT_PRIORITY_LEVEL9       9
#define HAL_INT_PRIORITY_LEVEL10      10
#define HAL_INT_PRIORITY_LEVEL11      11
#define HAL_INT_PRIORITY_LEVEL12      12
#define HAL_INT_PRIORITY_LEVEL13      13
#define HAL_INT_PRIORITY_LEVEL14      14
#define HAL_INT_PRIORITY_LEVEL15      15

#define HAL_INT_SUBPRIORITY_LEVEL0    0
#define HAL_INT_SUBPRIORITY_LEVEL1    1
#define HAL_INT_SUBPRIORITY_LEVEL2    2
#define HAL_INT_SUBPRIORITY_LEVEL3    3


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

