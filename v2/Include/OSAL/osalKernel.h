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
bool osalIsSchedulerActive();

void osalSuspendAll();
void osalResumeAll();
unsigned osalGetTickCount();
unsigned osalGetTickTime();
void osalDelay(unsigned time);
void osalDelayUntil(unsigned time, unsigned* lastTick);

void osalSysTickHandler();


#ifdef	__cplusplus
}
#endif


#endif // __osalKernel__
