#ifndef __osalMutex__
#define __osalMutex__


// EOS includes
//
#include "eos.h"


#ifdef	__cplusplus
extern "C" {
#endif

typedef struct OSAL_MUTEX_DATA* HMutex;

HMutex osalMutexCreate(void);
void osalMutexDestroy(HMutex hMutex);

bool osalMutexWait(HMutex hMutex, unsigned waitTime);
bool osalMutexRelease(HMutex hMutex);


#ifdef	__cplusplus
}
#endif


#endif // __osalMutex__
