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

    UART_1::interruptHandler();
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Procesa el vector _UART_2_VECTOR
///
#ifdef _UART2
extern "C" void UART_2_InterruptHandler(void) {

    UART_2::interruptHandler();
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Procesa el vector _UART_3_VECTOR
///
#ifdef _UART3
extern "C" void UART_3_InterruptHandler(void) {

    UART_3::interruptHandler();
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Procesa el vector _UART_4_VECTOR
///
#ifdef _UART4
extern "C" void UART_4_InterruptHandler(void) {

    UART_4::interruptHandler();
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Procesa el vector _UART_5_VECTOR
///
#ifdef _UART5
extern "C" void UART_5_InterruptHandler(void) {

    UART_5::interruptHandler();
}
#endif
