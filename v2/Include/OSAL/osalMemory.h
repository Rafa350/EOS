#ifndef __osalMemory__
#define __osalMemory__


// EOS includes
//
#include "eos.h"


#ifdef	__cplusplus
extern "C" {
#endif


void *osalMemoryAlloc(unsigned size);
void osalMemoryFree(void *p);
void osalMemoryCopy(void *pDst, const void *pSrc, unsigned size);


#ifdef	__cplusplus
}
#endif


#endif // __osalMemory__
