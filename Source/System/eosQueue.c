#include "System/eosQueue.h"
#include "System/eosMemory.h"


typedef struct __eosQueue {            // Cua FIFO
    unsigned itemSize;                 // -Tamany de cada element
    unsigned maxItems;                 // -Numero maxim d'elements en la cua
    unsigned numItems;                 // -Numero actual d'elements en la cua
    BYTE *start;                       // -Punter al inici de la cua
    BYTE *end;                         // -Punter al final de la cua
    BYTE *tail;                        // -Punter a l'ultim element insertat
    BYTE *head;                        // -Punter al primer element per extreure
} Queue;


/*************************************************************************
 *
 *       Crea una cua de tipus FIFO
 *
 *       Funcio:
 *           eosHQueue eosQueueCreate(
 *               eosQueueParams *params)
 *
 *       Entrada:
 *           params: Parametres d'inicialitzacio de la cua
 *
 *       Retorn:
 *           El handler de la cua. NULL en cas d'error
 *
 *************************************************************************/

eosHQueue eosQueueCreate(
    eosQueueParams *params) {

    // Inicialitza la cua
    //
    int queueSize = params->maxItems * params->itemSize;

    eosHQueue hQueue = eosAlloc(sizeof(Queue) + queueSize);
    if (hQueue == NULL)
        return NULL;

    hQueue->start = (BYTE*) hQueue + sizeof(Queue);
    hQueue->end = hQueue->start + queueSize;
    hQueue->itemSize = params->itemSize;
    hQueue->maxItems = params->maxItems;
    hQueue->numItems = 0;
	hQueue->tail = hQueue->start;
	hQueue->head = hQueue->start;

    return hQueue;
}


/*************************************************************************
 *
 *       Comprova si la cua es buida
 *
 *       Funcio:
 *           bool eosQueueGetIsEmpry(
 *               eosHQueue hQueue)
 *
 *       Entrada:
 *           hQueue: Handler de la cua
 *
 *       Retorn:
 *           true si la cua es buida
 *
 *************************************************************************/

bool eosQueueGetIsEmpty(
    eosHQueue hQueue) {

    bool intState = eosInterruptDisable();
    
    bool isEmpty = hQueue->numItems == 0;

    eosInterruptRestore(intState);

    return isEmpty;
}


/*************************************************************************
 *
 *       Afegeix un element en la cua
 *
 *       Funcio:
 *           bool eosQueuePut(
 *               eosHQueue hQueue,
 *               void* data)
 *
 *       Entrada:
 *           hQueue: Handler de la cua
 *           data : Punter al buffer de l'element a afeigit
 *
 *       Retorn:
 *           true si tot es correcte
 *
 *************************************************************************/

bool eosQueuePut(
    eosHQueue hQueue,
    void* data) {

    eosResult result = true;

    bool intState = eosInterruptDisable();

	if (hQueue->numItems < hQueue->maxItems) {

        memcpy(hQueue->head, data, hQueue->itemSize);
	    hQueue->head = hQueue->head + hQueue->itemSize;
	    if (hQueue->head >= hQueue->end)
	        hQueue->head = hQueue->start;
		hQueue->numItems++;
	}
    else
        result = false;

    eosInterruptRestore(intState);

    return result;
}


/*************************************************************************
 *
 *       Exteru un element en la cua
 *
 *       Funcio:
 *           bool eosQueueGet(
 *               eosHQueue hQueue,
 *               void* data)
 *
 *       Entrada:
 *           hQueue: Handler de la cua
 *           data  : Punter al buffer de l'element a exterure
 *
 *       Retorn:
 *           True si tot es correcte
 *
 *************************************************************************/

bool eosQueueGet(
    eosHQueue hQueue,
    void *data) {

    eosResult result = true;

    bool intState = eosInterruptDisable();

	if (hQueue->numItems > 0) {
	    memcpy(data, hQueue->tail, hQueue->itemSize);
		hQueue->tail = hQueue->tail + hQueue->itemSize;
	    if (hQueue->tail >= hQueue->end)
	        hQueue->tail = hQueue->start;
		hQueue->numItems--;
    }
	else
        result = false;

    eosInterruptRestore(intState);

	return result;
}
