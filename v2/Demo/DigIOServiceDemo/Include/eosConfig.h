#ifndef __eosConfig__
#define __eosConfig__

#define USE_LED1
#define USE_LED2
#define USE_LED3

#define USE_SW1
#define USE_SW2
#define USE_SW3

#define xUSE_APPLICATION_TICK
#define APPLICATION_TICK_PERIOD     10

#define EOS_USE_STD_STRING


#ifdef __cplusplus

#include "HTL/htlTMR.h"

namespace config {

    namespace digInputService {
        using TMR = htl::tmr::TMRDevice2;
        constexpr bool safeMode = true;
        constexpr unsigned timerPeriod = 5;
    }

    namespace digOutputService {
        using TMR = htl::tmr::TMRDevice3;
        constexpr bool safeMode = true;
        constexpr unsigned timerPeriod = 1;
    }
}
#endif


// Configuracio del servei DigInputs
//
#define DigInputService_Enabled                       1    // Servei activat
#define DigInputService_SafeMode                      1    // Modus segur
#define DigInputService_TimerPeriod                   5    // 5 ms de periode
#if defined(HARDWARE_PIC32_USB_STARTER_KIT_I)
#define DigInputService_Timer					      htl::TMR_2
#define DigInputService_TimerInterruptVector          htl::irq::VectorID::tmr2
#define DigInputService_TimerInterruptPriority        htl::irq::Priority::_2
#define DigInputService_TimerInterruptSubPriority     htl::irq::SubPriority::_0
#elif defined(HARDWARE_STM32F429I_DISC1)
#define DigInputService_Timer					      htl::TMR_2
#define DigInputService_TimerInterruptVector          htl::irq::VectorID::tmr2
#define DigInputService_TimerInterruptPriority        htl::irq::Priority::_5
#define DigInputService_TimerInterruptSubPriority     htl::irq::SubPriority::_0
#endif

// Configuracio del servei DigOutputs
//
#define DigOutputService_Enabled                      1    // Servei activat
#define DigOutputService_CommandQueueSize             5    // Tamany de la cua de comandes
#define DigOutputService_SafeMode                     1    // Modus segur
#define DigOutputService_TimerPeriod                  1    // 1 ms de periode
#if defined(HARDWARE_PIC32_USB_STARTER_KIT_I)
#define DigOutputService_Timer					      htl::TMR_3
#define DigOutputService_TimerInterruptVector         htl::irq::VectorID::tmr3
#define DigOutputService_TimerInterruptPriority       htl::irq::Priority::_2
#define DigOutputService_TimerInterruptSubPriority    htl::irq::SubPriority::_0
#elif defined(HARDWARE_STM32F429I_DISC1)
#define DigOutputService_Timer                        htl::TMR_3
#define DigOutputService_TimerInterruptVector         htl::irq::VectorID::tmr3
#define DigOutputService_TimerInterruptPriority       htl::irq::Priority::_5
#define DigOutputService_TimerInterruptSubPriority    htl::irq::SubPriority::_0
#endif


#endif // __eosConfig__
