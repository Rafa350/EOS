#ifndef __EOS_MEMORY_H
#define __EOS_MEMORY_H

#ifndef __EOS_H
#include "eos.h"
#endif


#ifdef eos_OPTION_AllocMacro
#define eosAlloc(s)          malloc(s)
#define eosFree(p)           free(p)
#else
extern void* eosAlloc(unsigned size);
extern void eosFree(void *p);
#endif


extern void* eosRealloc(void *p, unsigned size);
extern void* eosAllocString(const char *s);


// Heap


// Pool

typedef struct __eosPool *eosHPool;

extern eosHPool eosPoolCreate(unsigned elementSize, unsigned maxElements);
extern void *eosPoolAlloc(eosHPool hPool);
extern void eosPoolFree(void *p);


#endif