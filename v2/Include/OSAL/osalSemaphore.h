#ifndef __osalSemaphore__
#define __osalSemaphore__


// EOS includes
//
#include "eos.h"


#ifdef	__cplusplus
extern "C" {
#endif


typedef struct OSAL_SEMAPHORE_DATA *HSemaphore;


HSemaphore osalSemaphoreCreate(int maxCount);
void osalSemaphoreDestroy(HSemaphore hSemaphore);

bool osalSemaphoreWait(HSemaphore hSemaphore, unsigned blockTime);
void osalSemaphoreRelease(HSemaphore hSemaphore);
void osalSemaphoreReleaseISR(HSemaphore hSemaphore);


#ifdef	__cplusplus
}
#endif


#endif // __osalSemaphore__
