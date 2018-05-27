#ifndef __osalMemory__
#define __osalMemory__


// EOS includes
//
#include "eos.h"
#include "osal/osal.h"


#ifdef	__cplusplus
extern "C" {
#endif


void *osalMemoryAlloc(unsigned size);
void osalMemoryFree(void *p);


#ifdef	__cplusplus
}
#endif


#endif // __osalMemory__
