#ifndef __EOS_QUEUE_H
#define __EOS_QUEUE_H


#include "eos.h"


typedef void *eosQueueHandle;


extern eosQueueHandle eosQueueCreate(unsigned itemSize, unsigned maxItems);
extern void eosQueueDestroy(eosQueueHandle hQueue);
extern void eosQueueClear(eosQueueHandle hQueue);
extern bool eosQueuePut(eosQueueHandle hQueue, void *data, unsigned timeout);
extern bool eosQueueGet(eosQueueHandle hQueue, void *data, unsigned timeout);
extern bool eosQueueISRPut(eosQueueHandle hQueue, void *data);
extern bool eosQueueISRGet(eosQueueHandle hQueue, void *data);


#endif