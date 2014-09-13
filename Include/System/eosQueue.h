#ifndef __EOS_QUEUE_H
#define __EOS_QUEUE_H


#ifndef __EOS_H
#include "eos.h"
#endif


#define eosQUEUE_ERROR_FULL       (eos_ERROR_FIRST + 0)
#define eosQUEUE_ERROR_EMPTY      (eos_ERROR_FIRST + 1)


typedef struct {             // Parametres d'inicialitzacio de la cua
    unsigned length;         // -Capacitat de la cua en elements
    unsigned size;           // -Tamany de cada element en bytes
} eosQueueCreateParams;


extern eosResult eosQueueCreate(eosQueueCreateParams *params, eosHandle *hQueue);
extern eosResult eosQueueDestroy(eosHandle handle);

extern eosResult eosQueuePut(eosHandle hQueue, void *data);
extern eosResult eosQueueGet(eosHandle hQueue, void *data);

extern eosResult eosQueueGetIsEmpty(eosHandle hQueue, BOOL *isEmpty);


#endif