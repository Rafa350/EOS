#pragma once
#ifndef __STM32_htlUART_InterruptHandler__
#define __STM32_htlUART_InterruptHandler__


// EOS includes
//
#include "eos.h"


#ifdef __cplusplus
extern "C" {
#endif
    void UART_1_InterruptHandler();
    void UART_2_InterruptHandler();
    void UART_3_InterruptHandler();
    void UART_4_InterruptHandler();
    void UART_5_InterruptHandler();
    void UART_6_InterruptHandler();
    void UART_7_InterruptHandler();
    void UART_8_InterruptHandler();
#ifdef __cplusplus
}
#endif


#endif // __STM32_htlUART_InterruptHandler__
