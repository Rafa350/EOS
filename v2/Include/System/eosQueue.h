#ifndef __EOS_QUEUE_H
#define __EOS_QUEUE_H


#ifndef __EOS_H
#include "eos.h"
#endif


typedef struct __eosQueue *eosQueueHandle;

typedef struct {             // Parametres d'inicialitzacio de la cua
    unsigned maxItems;       // -Capacitat de la cua en elements
    unsigned itemSize;       // -Tamany de cada element en bytes
} eosQueueParams;


// Creacio i destruccio de la cua
//
extern eosQueueHandle eosQueueCreate(eosQueueParams *params);
extern void eosQueueDestroy(eosQueueHandle hQueue);

// Insercio i extraccio d'elements en la cua
//
extern bool eosQueuePut(eosQueueHandle hQueue, void *data, unsigned timeout);
extern bool eosQueueGet(eosQueueHandle hQueue, void *data, unsigned timeout);
extern bool eosQueueISRPut(eosQueueHandle hQueue, void *data);
extern bool eosQueueISRGet(eosQueueHandle hQueue, void *data);



#endif