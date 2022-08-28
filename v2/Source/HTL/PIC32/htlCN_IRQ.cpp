#include "eos.h"
#include "HTL/PIC32/htlCN.h"
#include "sys/attribs.h"


using namespace htl;


extern void __ISR(_CHANGE_NOTICE_VECTOR, IPL2SOFT) CN_1_InterruptVector(void);


/// ----------------------------------------------------------------------
/// \brief    Procesa el vector _CHANGE_NOTICE_VECTOR
///
extern "C" void CN_1_InterruptHandler() {

    if (CN_1::getInterruptFlag(CNEvent::change)) {
        CN_1::interruptHandler(CNEvent::change);
        CN_1::clearInterruptFlag(CNEvent::change);
    }
}
