#include "eos.h"
#include "HTL/PIC32/htlTMR.h"
#include "sys/attribs.h"


using namespace htl;
/*

#ifdef _TMR1
extern "C" void __ISR(_TIMER_1_VECTOR, IPL2SOFT) isrTMR1Wrapper(void);
#endif
#ifdef _TMR2
extern "C" void __ISR(_TIMER_2_VECTOR, IPL2SOFT) isrTMR2Wrapper(void);
#endif
#ifdef _TMR3
extern "C" void __ISR(_TIMER_3_VECTOR, IPL2SOFT) isrTMR3Wrapper(void);
#endif
#ifdef _TMR4
extern "C" void __ISR(_TIMER_4_VECTOR, IPL2SOFT) isrTMR4Wrapper(void);
#endif
#ifdef _TMR5
extern "C" void __ISR(_TIMER_5_VECTOR, IPL2SOFT) isrTMR5Wrapper(void);
#endif


/// ----------------------------------------------------------------------
/// \brief    Procesa el vector _TIMER_1_VECTOR
///
#ifdef _TMR1
extern "C" void isrTMR1Handler(void) {

    if (IFS0bits.T1IF) {
        TMR_1::interruptHandler(TMREvent::update);
        IFS0bits.T1IF = 0;
    }
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Procesa el vector _TIMER_2_VECTOR
///
#ifdef _TMR2
extern "C" void isrTMR2Handler(void) {

    if (IFS0bits.T2IF) {
        TMR_2::interruptHandler(TMREvent::update);
        IFS0bits.T2IF = 0;
    }
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Procesa el vector _TIMER_3_VECTOR
///
#ifdef _TMR3
extern "C" void isrTMR3Handler(void) {

    if (IFS0bits.T3IF) {
        TMR_3::interruptHandler(TMREvent::update);
        IFS0bits.T3IF = 0;
    }
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Procesa el vector _TIMER_4_VECTOR
///
#ifdef _TMR4
extern "C" void isrTMR4Handler(void) {

    if (IFS0bits.T4IF) {
        TMR_4::interruptHandler(TMREvent::update);
        IFS0bits.T4IF = 0;
    }
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Procesa el vector _TIMER_5_VECTOR
///
#ifdef _TMR5
extern "C" void isrTMR5Handler(void) {

    if (IFS0bits.T5IF) {
        TMR_5::interruptHandler(TMREvent::update);
        IFS0bits.T5IF = 0;
    }
}
#endif
*/