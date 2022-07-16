#include "eos.h"
#include "HTL/PIC32/htlCN.h"
#include "sys/attribs.h"


using namespace htl;


extern void __ISR(_CHANGE_NOTICE_VECTOR, IPL2SOFT) isrCNWrapper(void);


/// ----------------------------------------------------------------------
/// \brief    Procesa el vector _CHANGE_NOTICE_VECTOR
///
extern "C" void isrCNHandler() {

    if (IFS1bits.CNIF) {
        CN_1::interruptHandler(CNEvent::change);
        IFS1bits.CNIF = 0;
    }
}
