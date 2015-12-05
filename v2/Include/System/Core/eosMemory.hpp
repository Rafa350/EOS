#ifndef __EOS_MEMORY_HPP
#define __EOS_MEMORY_HPP


#ifndef __EOS_HPP
#include "eos.hpp"
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