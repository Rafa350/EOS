#ifndef __osalHeap__
#define __osalHeap__


// EOS includes
//
#include "eos.h"


#ifdef	__cplusplus
extern "C" {
#endif


typedef struct OSAL_HEAP_DATA *HHeap;


HHeap osalHeapCreate();
void *osalHeapAlloc(HHeap hHeap, int blockSize);
void osalHeapFree(HHeap hHeap, void *pBlock);


#ifdef	__cplusplus
}
#endif


#endif // __osalHeap__
