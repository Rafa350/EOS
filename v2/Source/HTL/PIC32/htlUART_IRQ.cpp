#include "eos.h"
#include "HTL/PIC32/htlUART.h"
#include "sys/attribs.h"


using namespace htl;


#ifdef _UART1
extern "C" void __ISR(_UART_1_VECTOR, IPL2SOFT) UART_1_InterruptVector(void);
#endif
#ifdef _UART2
extern "C" void __ISR(_UART_2_VECTOR, IPL2SOFT) UART_2_InterruptVector(void);
#endif
#ifdef _UART3
extern "C" void __ISR(_UART_3_VECTOR, IPL2SOFT) UART_3_InterruptVector(void);
#endif
#ifdef _UART4
extern "C" void __ISR(_UART_4_VECTOR, IPL2SOFT) UART_4_InterruptVector(void);
#endif
#ifdef _UART5
extern "C" void __ISR(_UART_5_VECTOR, IPL2SOFT) UART_5_InterruptVector(void);
#endif


/// ----------------------------------------------------------------------
/// \brief    Procesa el vector _UART_1_VECTOR
///
#ifdef _UART1
extern "C" void UART_1_InterruptHandler(void) {

    if (UART_1::getInterruptFlag(UARTEvent::error)) {
        UART_1::clearInterruptFlag(UARTEvent::error);
        UART_1::interruptHandler(UARTEvent::error);
    }

    if (UART_1::getInterruptFlag(UARTEvent::rxNotEmpty)) {
        UART_1::clearInterruptFlag(UARTEvent::rxNotEmpty);
        UART_1::interruptHandler(UARTEvent::rxNotEmpty);
    }

    if (UART_1::getInterruptFlag(UARTEvent::txEmpty)) {
        UART_1::clearInterruptFlag(UARTEvent::txEmpty);
        UART_1::interruptHandler(UARTEvent::txEmpty);
    }
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Procesa el vector _UART_2_VECTOR
///
#ifdef _UART2
extern "C" void UART_2_InterruptHandler(void) {

    if (UART_2::getInterruptFlag(UARTEvent::error)) {
        UART_2::clearInterruptFlag(UARTEvent::error);
        UART_2::interruptHandler(UARTEvent::error);
    }

    if (UART_2::getInterruptFlag(UARTEvent::rxNotEmpty)) {
        UART_2::clearInterruptFlag(UARTEvent::rxNotEmpty);
        UART_2::interruptHandler(UARTEvent::rxNotEmpty);
    }

    if (UART_2::getInterruptFlag(UARTEvent::txEmpty)) {
        UART_2::clearInterruptFlag(UARTEvent::txEmpty);
        UART_2::interruptHandler(UARTEvent::txEmpty);
    }
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Procesa el vector _UART_3_VECTOR
///
#ifdef _UART3
extern "C" void UART_3_InterruptHandler(void) {

    if (UART_3::getInterruptFlag(UARTEvent::error)) {
        UART_3::clearInterruptFlag(UARTEvent::error);
        UART_3::interruptHandler(UARTEvent::error);
    }

    if (UART_3::getInterruptFlag(UARTEvent::rxNotEmpty)) {
        UART_3::clearInterruptFlag(UARTEvent::rxNotEmpty);
        UART_3::interruptHandler(UARTEvent::rxNotEmpty);
    }

    if (UART_3::getInterruptFlag(UARTEvent::txEmpty)) {
        UART_3::clearInterruptFlag(UARTEvent::txEmpty);
        UART_3::interruptHandler(UARTEvent::txEmpty);
    }
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Procesa el vector _UART_4_VECTOR
///
#ifdef _UART4
extern "C" void UART_4_InterruptHandler(void) {

    if (UART_4::getInterruptFlag(UARTEvent::error)) {
        UART_4::clearInterruptFlag(UARTEvent::error);
        UART_4::interruptHandler(UARTEvent::error);
    }

    if (UART_4::getInterruptFlag(UARTEvent::rxNotEmpty)) {
        UART_4::clearInterruptFlag(UARTEvent::rxNotEmpty);
        UART_4::interruptHandler(UARTEvent::rxNotEmpty);
    }

    if (UART_4::getInterruptFlag(UARTEvent::txEmpty)) {
        UART_4::clearInterruptFlag(UARTEvent::txEmpty);
        UART_4::interruptHandler(UARTEvent::txEmpty);
    }
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Procesa el vector _UART_5_VECTOR
///
#ifdef _UART5
extern "C" void UART_5_InterruptHandler(void) {

    if (UART_5::getInterruptFlag(UARTEvent::error)) {
        UART_5::clearInterruptFlag(UARTEvent::error);
        UART_5::interruptHandler(UARTEvent::error);
    }

    if (UART_5::getInterruptFlag(UARTEvent::rxNotEmpty)) {
        UART_5::clearInterruptFlag(UARTEvent::rxNotEmpty);
        UART_5::interruptHandler(UARTEvent::rxNotEmpty);
    }

    if (UART_5::getInterruptFlag(UARTEvent::txEmpty)) {
        UART_5::clearInterruptFlag(UARTEvent::txEmpty);
        UART_5::interruptHandler(UARTEvent::txEmpty);
    }
}
#endif
