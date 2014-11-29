#ifndef __EOS_POOL_H
#define __EOS_POOL_H


#ifndef __EOS_H
#include "eos.h"
#endif


typedef struct __eosPool *eosHPool;


extern eosHPool eosPoolCreate(unsigned elementSize, unsigned maxElements);
extern void *eosPoolAlloc(eosHPool hPool);
extern void eosPoolFree(void *p);


#endif
