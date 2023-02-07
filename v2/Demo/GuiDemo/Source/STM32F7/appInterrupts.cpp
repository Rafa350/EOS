#include "eos.h"
#include "HTL/STM32/htlEXTI_IRQ.h"


extern "C" void EXTI15_10_IRQHandler() {

    EXTI_10_11_12_13_14_15_InterruptHandler();
}
