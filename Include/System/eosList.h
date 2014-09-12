#ifndef __EOS_LIST_H
#define __EOS_LIST_H


#ifndef __EOS_H
#include "eos.h"
#endif


extern eosResult eosListCreate(eosHandle *hList);
extern eosResult eosListDestroy(eosHandle hList);

extern eosResult eosListEmpty(eosHandle hList);
extern eosResult eosListAdd(eosHandle hList, void *data);
extern eosResult eosListRemove(eosHandle hList, void *data);


#endif