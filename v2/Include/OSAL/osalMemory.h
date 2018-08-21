#ifndef __osalMemory__
#define __osalMemory__


// EOS includes
//
#include "eos.h"

// Standard includes
//
#include "stddef.h"


#ifdef	__cplusplus
extern "C" {
#endif


void *osalMemoryAlloc(size_t size);
void osalMemoryFree(void *p);


#ifdef	__cplusplus
}
#endif


#endif // __osalMemory__
