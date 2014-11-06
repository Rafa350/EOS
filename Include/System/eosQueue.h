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

typedef struct __eosQueue *eosQueue;

typedef struct {             // Parametres d'inicialitzacio de la cua
    unsigned maxItems;       // -Capacitat de la cua en elements
    unsigned itemSize;       // -Tamany de cada element en bytes
} eosQueueParams;


extern eosResult eosQueueCreate(eosQueueParams *params, eosQueue *queue);
extern eosResult eosQueueDestroy(eosQueue queue);

extern eosResult eosQueuePut(eosQueue queue, void *data);
extern eosResult eosQueueGet(eosQueue queue, void *data);

extern eosResult eosQueueGetIsEmpty(eosQueue queue, BOOL *isEmpty);
eosResult eosQueueEnumerate(eosQueue queue);
eosResult eosQueueEnumerateNext(eosQueue queue, void *data);


#endif