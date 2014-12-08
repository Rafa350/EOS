#ifndef __EOS_QUEUE_H
#define __EOS_QUEUE_H


#ifndef __EOS_H
#include "eos.h"
#endif


#define eosQUEUE_ERROR_FULL       (eos_ERROR_USER + 0)
#define eosQUEUE_ERROR_EMPTY      (eos_ERROR_USER + 1)

#ifndef __EOS_QUEUE_INTERNAL
struct __eosQueue {};
#endif

typedef struct __eosQueue *eosHQueue;

typedef struct {             // Parametres d'inicialitzacio de la cua
    unsigned maxItems;       // -Capacitat de la cua en elements
    unsigned itemSize;       // -Tamany de cada element en bytes
} eosQueueParams;


extern eosHQueue eosQueueCreate(eosQueueParams *params);
extern void eosQueueDestroy(eosHQueue hQueue);

extern bool eosQueuePut(eosHQueue hQueue, void *data);
extern bool eosQueueGet(eosHQueue hQueue, void *data);

extern bool eosQueueGetIsEmpty(eosHQueue hQueue);
eosResult eosQueueEnumerate(eosHQueue hQueue);
eosResult eosQueueEnumerateNext(eosHQueue hQueue, void *data);


#endif