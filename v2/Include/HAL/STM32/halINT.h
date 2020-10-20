/// \file      halINT.h
/// \author    Rafael Serrano (rsr.openware@gmail.com)
/// \brief     Gestio de les interrupcions
/// \addtogroup HAL Hardware Abstraction Layer
/// @{
/// \addtogroup HAL_STM32 STM32 Hardware Abstraction Layer
/// @{
/// \defgroup HAL_STM32_INT INT
/// @{
///
#ifndef __STM32_halINT__
#define __STM32_halINT__


// EOS includes
//
#include "eos.h"


// Prioritats de les interrupcions
#define HAL_INT_PRIORITY_0             0
#define HAL_INT_PRIORITY_1             1
#define HAL_INT_PRIORITY_2             2
#define HAL_INT_PRIORITY_3       	   3
#define HAL_INT_PRIORITY_4             4
#define HAL_INT_PRIORITY_5             5
#define HAL_INT_PRIORITY_6   		   6
#define HAL_INT_PRIORITY_7       	   7
#define HAL_INT_PRIORITY_8             8
#define HAL_INT_PRIORITY_9             9
#define HAL_INT_PRIORITY_10            10
#define HAL_INT_PRIORITY_11            11
#define HAL_INT_PRIORITY_12            12
#define HAL_INT_PRIORITY_13            13
#define HAL_INT_PRIORITY_14            14
#define HAL_INT_PRIORITY_15            15

// Subprioritats de les interrupcions
#define HAL_INT_SUBPRIORITY_0          0
#define HAL_INT_SUBPRIORITY_1          1
#define HAL_INT_SUBPRIORITY_2          2
#define HAL_INT_SUBPRIORITY_3          3

// Vectord d'interrupcion
#define HAL_INT_VECTOR_DAC            TIM6_DAC_IRQn
#define HAL_INT_VECTOR_DMA2D          DMA2D_IRQn
#define HAL_INT_VECTOR_EXTI10         EXTI15_10_IRQn
#define HAL_INT_VECTOR_EXTI11         EXTI15_10_IRQn
#define HAL_INT_VECTOR_EXTI12         EXTI15_10_IRQn
#define HAL_INT_VECTOR_EXTI13         EXTI15_10_IRQn
#define HAL_INT_VECTOR_EXTI14         EXTI15_10_IRQn
#define HAL_INT_VECTOR_EXTI15         EXTI15_10_IRQn
#define HAL_INT_VECTOR_LTDC           LTDC_IRQn
#define HAL_INT_VECTOR_LTDC_ER        LTDC_ER_IRQn
#define HAL_INT_VECTOR_SPI1           SPI1_IRQn
#define HAL_INT_VECTOR_SPI2           SPI2_IRQn
#define HAL_INT_VECTOR_SPI3           SPI3_IRQn
#define HAL_INT_VECTOR_SPI4           SPI4_IRQn
#define HAL_INT_VECTOR_SPI5           SPI5_IRQn
#define HAL_INT_VECTOR_SPI6           SPI6_IRQn
#define HAL_INT_VECTOR_TMR1_BRK       TIM1_BRK_TIM9_IRQn
#define HAL_INT_VECTOR_TMR1_CC        TIM1_CC_IRQn
#define HAL_INT_VECTOR_TMR1_TRG       TIM1_TRG_COM_TIM11_IRQn
#define HAL_INT_VECTOR_TMR1_UP        TIM1_UP_TIM10_IRQn
#define HAL_INT_VECTOR_TMR2           TIM2_IRQn
#define HAL_INT_VECTOR_TMR3           TIM3_IRQn
#define HAL_INT_VECTOR_TMR4           TIM4_IRQn
#define HAL_INT_VECTOR_TMR5           TIM5_IRQn
#define HAL_INT_VECTOR_TMR6           TIM6_DAC_IRQn
#define HAL_INT_VECTOR_TMR7           TIM7_IRQn
#define HAL_INT_VECTOR_TMR8_BRK       TIM8_BRK_TIM12_IRQn
#define HAL_INT_VECTOR_TMR8_CC        TIM8_CC_IRQn
#define HAL_INT_VECTOR_TMR8_TRG       TIM8_TRG_COM_TIM14_IRQn
#define HAL_INT_VECTOR_TMR8_UP        TIM8_UP_TIM13_IRQn
#define HAL_INT_VECTOR_TMR9           TIM1_BRK_TIM9_IRQn
#define HAL_INT_VECTOR_TMR10          TIM1_UP_TIM10_IRQn
#define HAL_INT_VECTOR_TMR11          TIM1_TRG_COM_TIM11_IRQn
#define HAL_INT_VECTOR_TMR12          TIM8_BRK_TIM12_IRQn
#define HAL_INT_VECTOR_TMR13          TIM8_UP_TIM13_IRQn
#define HAL_INT_VECTOR_TIM14          TIM8_TRG_COM_TIM14_IRQn
#define HAL_INT_VECTOR_UART1          USART1_IRQn
#define HAL_INT_VECTOR_UART2          USART2_IRQn
#define HAL_INT_VECTOR_UART3          USART3_IRQn
#define HAL_INT_VECTOR_UART4          UART4_IRQn
#define HAL_INT_VECTOR_UART5          UART5_IRQn
#define HAL_INT_VECTOR_UART6          USART6_IRQn
#define HAL_INT_VECTOR_UART7          UART7_IRQn
#define HAL_INT_VECTOR_UART8          UART8_IRQn


#ifdef	__cplusplus
extern "C" {
#endif


#define halINTEnableInterrupts()      __enable_irq()
#define halINTDisableInterrupts()     __disable_irq()

#define __halINTEnableInterrupts()    __enable_irq()
#define __halINTDisableInterrupts()   __disable_irq()


void halINTSetInterruptVectorPriority(uint32_t vector, uint32_t priority, uint32_t subPriority);
void halINTEnableInterruptVector(uint32_t vector);

void halINTEnableInterruptSource(uint32_t source);
bool halINTDisableInterruptSource(uint32_t source);
void halINTRestoreInterruptSource(uint32_t source, bool state);


#ifdef	__cplusplus
}
#endif


#endif // __STM32_halINT__

/// @}
/// @}
/// @}

