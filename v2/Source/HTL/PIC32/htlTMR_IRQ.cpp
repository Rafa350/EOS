#include "eos.h"
#include "HTL/PIC32/htlTMR.h"
#include "sys/attribs.h"


using namespace htl;


#ifdef _TMR1
extern "C" void __ISR(_TIMER_1_VECTOR, IPL2SOFT) TMR_1_InterruptVector(void);
#endif
#ifdef _TMR2
extern "C" void __ISR(_TIMER_2_VECTOR, IPL2SOFT) TMR_2_InterruptVector(void);
#endif
#ifdef _TMR3
extern "C" void __ISR(_TIMER_3_VECTOR, IPL2SOFT) TMR_3_InterruptVector(void);
#endif
#ifdef _TMR4
extern "C" void __ISR(_TIMER_4_VECTOR, IPL2SOFT) TMR_4_InterruptVector(void);
#endif
#ifdef _TMR5
extern "C" void __ISR(_TIMER_5_VECTOR, IPL2SOFT) TMR_5_InterruptVector(void);
#endif


/// ----------------------------------------------------------------------
/// \brief    Procesa el vector _TIMER_1_VECTOR
///
#ifdef _TMR1
extern "C" void TMR_1_InterruptHandler(void) {

    htl::tmr::TMRDevice1::interruptHandler();
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Procesa el vector _TIMER_2_VECTOR
///
#ifdef _TMR2
extern "C" void TMR_2_InterruptHandler(void) {

    htl::tmr::TMRDevice2::interruptHandler();
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Procesa el vector _TIMER_3_VECTOR
///
#ifdef _TMR3
extern "C" void TMR_3_InterruptHandler(void) {

    htl::tmr::TMRDevice3::interruptHandler();
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Procesa el vector _TIMER_4_VECTOR
///
#ifdef _TMR4
extern "C" void TMR_4_InterruptHandler(void) {

    htl::tmr::TMRDevice4::interruptHandler();
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Procesa el vector _TIMER_5_VECTOR
///
#ifdef _TMR5
extern "C" void TMR_5_InterruptHandler(void) {

    htl::tmr::TMRDevice5::interruptHandler();
}
#endif
