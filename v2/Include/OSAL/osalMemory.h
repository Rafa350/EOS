#ifndef __osalMemory__
#define __osalMemory__


// EOS includes
//
#include "eos.h"


#ifdef	__cplusplus
extern "C" {
#endif


void *osalMemAlloc(unsigned size);
void osalMemFree(void *p);


#ifdef	__cplusplus
}
#endif


#endif // __osalMemory__