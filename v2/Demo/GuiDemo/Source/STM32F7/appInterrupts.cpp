#include "eos.h"
#include "HTL/STM32/htlEXTI_IRQ.h"
#include "HTL/STM32/htlLTDC_IRQ.h"
#include "HTL/STM32/htlDMA2D_IRQ.h"
#include "HTL/STM32/htlTMR_IRQ.h"


using namespace eos;
using namespace htl;


extern "C" void EXTI15_10_IRQHandler() {

    EXTI_10_11_12_13_14_15_InterruptHandler();
}
