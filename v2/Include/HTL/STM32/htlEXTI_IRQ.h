#pragma once
#ifndef __STM32_htlEXTI_IRQ__
#define __STM32_htlEXTI_IRQ__


// EOS includes
//
#include "eos.h"


#ifdef __cplusplus
extern "C" {
#endif
    void EXTI_0_InterruptHandler();
    void EXTI_1_InterruptHandler();
    void EXTI_2_InterruptHandler();
    void EXTI_3_InterruptHandler();
    void EXTI_4_InterruptHandler();
    void EXTI_5_6_7_8_9_InterruptHandler();
    void EXTI_10_11_12_13_14_15_InterruptHandler();
#ifdef __cplusplus
}
#endif


#endif // __STM32_htlEXTI_IRQ__
