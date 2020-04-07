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

bool osalMutexLock(HMutex hMutex, unsigned blockTime);
bool osalMutexUnlock(HMutex hMutex);


#ifdef	__cplusplus
}
#endif


#endif // __osalMutex__