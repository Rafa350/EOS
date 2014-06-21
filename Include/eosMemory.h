#ifndef __EOS_MEMORY_H
#define __EOS_MEMORY_H

#ifndef __EOS_H
#include "eos.h"
#endif


extern void* eosAlloc(unsigned size);
extern void* eosRealloc(void *p, unsigned size);
extern void* eosAllocString(const char *s);
extern void eosFree(void *p);



#endif