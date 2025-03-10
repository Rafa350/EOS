#ifndef __osalHeap__
#define __osalHeap__


// EOS includes
//
#include "eos.h"


#ifdef	__cplusplus
extern "C" {
#endif


typedef struct OSAL_HEAP_DATA *HHeap;

typedef struct {
	unsigned start;
	unsigned length;
	unsigned allocated;
	unsigned available;
	unsigned allocCount;
	unsigned freeCount;
} HeapInformation;

HHeap osalHeapCreate(void);
void osalHeapDestroy(HHeap hHeap);

void *osalHeapAlloc(HHeap hHeap, unsigned size);
void osalHeapFree(HHeap hHeap, void *block);

bool osalHeapVerify(HHeap hHeap, void *block);
void osalHeapGetInfo(HHeap hHeap, HeapInformation *info);
unsigned osalHeapGetAvailable(HHeap hHeap);

void* osal_malloc(int size);
void osal_free(void* p);


#ifdef	__cplusplus
}
#endif


#endif // __osalHeap__
