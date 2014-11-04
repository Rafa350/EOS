#ifndef __EOS_QUEUE_H
#define __EOS_QUEUE_H


#ifndef __EOS_H
#include "eos.h"
#endif


#define eosQUEUE_ERROR_FULL       (eos_ERROR_USER + 0)
#define eosQUEUE_ERROR_EMPTY      (eos_ERROR_USER + 1)


typedef struct {             // Parametres d'inicialitzacio de la cua
    unsigned maxItems;       // -Capacitat de la cua en elements
    unsigned itemSize;       // -Tamany de cada element en bytes
} eosQueueCreateParams;


extern eosResult eosQueueCreate(eosQueueCreateParams *params, eosHandle *hQueue);
extern eosResult eosQueueDestroy(eosHandle hQueue);

extern eosResult eosQueuePut(eosHandle hQueue, void *data);
extern eosResult eosQueueGet(eosHandle hQueue, void *data);

extern eosResult eosQueueGetIsEmpty(eosHandle hQueue, BOOL *isEmpty);
eosResult eosQueueEnumerate(eosHandle hQueue);
eosResult eosQueueEnumerateNext(eosHandle hQueue, void *data);


#endif