#ifndef __EOS_MEMORY_H
#define __EOS_MEMORY_H

#ifndef __EOS_H
#include "eos.h"
#endif


// Heap

#define eosAlloc(s)          eosHeapAlloc(NULL, s)
#define eosAllocString(p)    eosHeapAllocString(NULL, p)
#define eosRealloc(p, s)     eosHeapRealloc(NULL, p, s)
#define eosFree(p)           eosHeapFree(p)

typedef struct __eosHeap *eosHeapHandle;

extern eosHeapHandle eosHeapCreate(unsigned size);
extern void *eosHeapAlloc(eosHeapHandle hHeap, unsigned size);
extern void *eosHeapAllocString(eosHeapHandle hHeap, const char *s);
extern void *eosHeapRealloc(eosHeapHandle hHeap, void *p, unsigned size);
extern void eosHeapFree(void *p);


// Pool

typedef struct __eosPool *eosPoolHandle;

extern eosPoolHandle eosPoolCreate(unsigned elementSize, unsigned maxElements);
extern void *eosPoolAlloc(eosPoolHandle hPool);
extern void eosPoolFree(void *p);


#endif