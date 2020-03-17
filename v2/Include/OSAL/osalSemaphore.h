#ifndef __osalSemaphore__
#define __osalSemaphore__


// EOS includes
//
#include "eos.h"


#ifdef	__cplusplus
extern "C" {
#endif


typedef struct OSAL_SEMAPHORE_DATA* HSemaphore;


HSemaphore osalSemaphoreCreate(unsigned maxCount);
void osalSemaphoreDestroy(HSemaphore hSemaphore);

bool osalSemaphoreWait(HSemaphore, unsigned blockTime);
bool osalSemaphoreWaitISR(HSemaphore, unsigned blockTime);
void osalSemaphoreRelease(HSemaphore hSemaphore);
void osalSemaphoreReleaseISR(HSemaphore hSemaphore);


#ifdef	__cplusplus
}
#endif


#endif // __osalSemaphore__
