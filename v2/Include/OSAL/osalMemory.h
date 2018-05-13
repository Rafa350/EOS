#ifndef __osalMemory__
#define __osalMemory__


// EOS includes
//
#include "eos.h"
#include "osal/osal.h"


// Stdlib includes
//
#include "stdint.h"


#ifdef	__cplusplus
extern "C" {
#endif


uint8_t osalMemoryAlloc(unsigned size, void **p);
uint8_t osalMemoryFree(void *p);


#ifdef	__cplusplus
}
#endif


#endif // __osalMemory__
