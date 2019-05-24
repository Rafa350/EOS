#ifndef __osalKernel__
#define __osalKernel__


// EOS includes
//
#include "eos.h"


#ifdef	__cplusplus
extern "C" {
#endif


void osalEnterCritical();
void osalExitCritical();

void osalStartScheduler();
void osalStopScheduler();

void osalSuspendAll();
void osalResumeAll();
unsigned osalGetTickCount();
void osalDelay(unsigned time);
void osalDelayUntil(unsigned time, unsigned *lastTick);

void osalSystickHandler();


#ifdef	__cplusplus
}

#endif


#endif // __osalKernel__
