#ifndef __STM32_halINT__
#define __STM32_halINT__


// EOS includes
//
#include "eos.h"

// Prioritats de les interrupcions
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

// Subprioritats de les interrupcions
#define HAL_INT_SUBPRIORITY_LEVEL0    0
#define HAL_INT_SUBPRIORITY_LEVEL1    1
#define HAL_INT_SUBPRIORITY_LEVEL2    2
#define HAL_INT_SUBPRIORITY_LEVEL3    3

// Interrupcions (Alguns vectors son compartits)
#define HAL_INT_SOURCE_DAC            TIM6_DAC_IRQn
#define HAL_INT_SOURCE_DMA2D          DMA2D_IRQn
#define HAL_INT_SOURCE_LTDC           LTDC_IRQn
#define HAL_INT_SOURCE_LTDC_ER        LTDC_ER_IRQn
#define HAL_INT_SOURCE_SPI1           SPI1_IRQn
#define HAL_INT_SOURCE_SPI2           SPI2_IRQn
#define HAL_INT_SOURCE_SPI3           SPI3_IRQn
#define HAL_INT_SOURCE_SPI4           SPI4_IRQn
#define HAL_INT_SOURCE_SPI5           SPI5_IRQn
#define HAL_INT_SOURCE_SPI6           SPI6_IRQn
#define HAL_INT_SOURCE_TMR1_BRK       TIM1_BRK_TIM9_IRQn
#define HAL_INT_SOURCE_TMR1_CC        TIM1_CC_IRQn
#define HAL_INT_SOURCE_TMR1_TRG       TIM1_TRG_COM_TIM11_IRQn
#define HAL_INT_SOURCE_TMR1_UP        TIM1_UP_TIM10_IRQn
#define HAL_INT_SOURCE_TMR2           TIM2_IRQn
#define HAL_INT_SOURCE_TMR3           TIM3_IRQn
#define HAL_INT_SOURCE_TMR4           TIM4_IRQn
#define HAL_INT_SOURCE_TMR5           TIM5_IRQn
#define HAL_INT_SOURCE_TMR6           TIM6_DAC_IRQn
#define HAL_INT_SOURCE_TMR7           TIM7_IRQn
#define HAL_INT_SOURCE_TMR9           TIM1_BRK_TIM9_IRQn
#define HAL_INT_SOURCE_TMR8_BRK       TIM8_BRK_TIM12_IRQn
#define HAL_INT_SOURCE_TMR8_CC        TIM8_CC_IRQn
#define HAL_INT_SOURCE_TMR8_TRG       TIM8_TRG_COM_TIM14_IRQn
#define HAL_INT_SOURCE_TMR8_UP        TIM8_UP_TIM13_IRQn
#define HAL_INT_SOURCE_TMR10          TIM1_UP_TIM10_IRQn
#define HAL_INT_SOURCE_TMR11          TIM1_TRG_COM_TIM11_IRQn
#define HAL_INT_SOURCE_TMR12          TIM8_BRK_TIM12_IRQn
#define HAL_INT_SOURCE_TMR13          TIM8_UP_TIM13_IRQn
#define HAL_INT_SOURCE_TIM14          TIM8_TRG_COM_TIM14_IRQn


#define halINTEnableInterrupts() \
	__enable_irq()

#define halINTDisableInterrupts() \
	__disable_irq()


#ifdef	__cplusplus
extern "C" {
#endif


typedef uint32_t INTSource;


void halINTSetPriority(INTSource source, uint32_t priority, uint32_t subPriority);

void halINTEnableInterrupt(INTSource source);
bool halINTDisableInterrupt(INTSource source);
void halINTRestoreInterrupt(INTSource source, bool state);


#ifdef	__cplusplus
}
#endif


#endif // __STM32_halINT__

