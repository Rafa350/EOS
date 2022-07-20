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

    if (IFS0bits.U1EIF) {
        UART_1::interruptHandler(UARTEvent::error);
        IFS0bits.U1EIF = 0;
    }

    if (IFS0bits.U1RXIF) {
        UART_1::interruptHandler(UARTEvent::receive);
        IFS0bits.U1RXIF = 0;
    }

    if (IFS0bits.U1TXIF) {
        UART_1::interruptHandler(UARTEvent::transmit);
        IFS0bits.U1TXIF = 0;
    }
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Procesa el vector _UART_2_VECTOR
///
#ifdef _UART2
extern "C" void UART_2_InterruptHandler(void) {

    if (IFS1bits.U2EIF) {
        UART_2::interruptHandler(UARTEvent::error);
        IFS1bits.U2EIF = 0;
    }

    if (IFS1bits.U2RXIF) {
        UART_2::interruptHandler(UARTEvent::receive);
        IFS1bits.U2RXIF = 0;
    }

    if (IFS1bits.U2TXIF) {
        UART_2::interruptHandler(UARTEvent::transmit);
        IFS1bits.U2TXIF = 0;
    }
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Procesa el vector _UART_3_VECTOR
///
#ifdef _UART3
extern "C" void UART_3_InterruptHandler(void) {

}
#endif


/// ----------------------------------------------------------------------
/// \brief    Procesa el vector _UART_4_VECTOR
///
#ifdef _UART4
extern "C" void UART_4_InterruptHandler(void) {

}
#endif


/// ----------------------------------------------------------------------
/// \brief    Procesa el vector _UART_5_VECTOR
///
#ifdef _UART5
extern "C" void UART_5_InterruptHandler(void) {

}
#endif
