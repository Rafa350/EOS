#ifndef __EOS_MEMORY_H
#define __EOS_MEMORY_H


#ifndef __EOS_H
#include "eos.h"
#endif


// Gestio de memoria tipus 'Heap'

typedef struct __eosHeap *eosHeapHandle;

extern eosHeapHandle eosHeapCreate(unsigned size);
extern void *eosHeapAlloc(eosHeapHandle hHeap, unsigned size);
extern void eosHeapFree(void *p);


// Gestio de memoria tipus 'Pool'

typedef struct __eosPool *eosPoolHandle;

extern eosPoolHandle eosPoolCreate(unsigned elementSize, unsigned maxElements);
extern void *eosPoolAlloc(eosPoolHandle hPool);
extern void eosPoolFree(void *p);


#endif