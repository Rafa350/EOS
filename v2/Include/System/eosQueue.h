#ifndef __EOS_QUEUE_H
#define __EOS_QUEUE_H


#ifndef __EOS_H
#include "eos.h"
#endif


typedef void *eosQueueHandle;


// Creacio i destruccio de la cua
//
extern eosQueueHandle eosQueueCreate(unsigned itemSize, unsigned maxItems);
extern void eosQueueDestroy(eosQueueHandle hQueue);

// Insercio i extraccio d'elements en la cua
//
extern bool eosQueuePut(eosQueueHandle hQueue, void *data, unsigned timeout);
extern bool eosQueueGet(eosQueueHandle hQueue, void *data, unsigned timeout);
extern bool eosQueueISRPut(eosQueueHandle hQueue, void *data);
extern bool eosQueueISRGet(eosQueueHandle hQueue, void *data);
extern void eosQueueClear(eosQueueHandle hQueue);



#endif