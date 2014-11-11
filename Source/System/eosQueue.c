#define __EOS_QUEUE_INTERNAL
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
 *           eosResult eosQueueCreate(
 *               eosQueueParams *params,
 *               eosQueue *hQueue)
 *
 *       Entrada:
 *           params: Parametres d'inicialitzacio de la cua
 *
 *       Sortida:
 *           hQueue: El handler de la cua
 *
 *       Retorn:
 *           eos_RESULT_SUCCESS si tot es correxte
 *
 *************************************************************************/

eosResult eosQueueCreate(
    eosQueueParams *params,
    eosHQueue *_hQueue) {

    // Inicialitza la cua
    //
    int queueSize = params->maxItems * params->itemSize;

    eosHQueue hQueue = eosAlloc(sizeof(Queue) + queueSize);
    if (hQueue == NULL)
        return eos_ERROR_ALLOC;

    hQueue->start = (BYTE*) hQueue + sizeof(Queue);
    hQueue->end = hQueue->start + queueSize;
    hQueue->itemSize = params->itemSize;
    hQueue->maxItems = params->maxItems;
    hQueue->numItems = 0;
	hQueue->tail = hQueue->start;
	hQueue->head = hQueue->start;

    *_hQueue = hQueue;

    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Comprova si la cua es buida
 *
 *       Funcio:
 *           eosResult eosQueueGetIsEmpry(
 *               eosHQueue hQueue,
 *               BOOL *isEmpry)
 *
 *       Entrada:
 *           hQueue: Handler de la cua
 *
 *       Sortida:
 *           isEmpty: TRUE si la cua es buida
 *
 *       Retorn:
 *           eos_RESULT_SUCCESS si tot es correcte
 *
 *************************************************************************/

eosResult eosQueueGetIsEmpty(
    eosHQueue hQueue,
    BOOL *isEmpty) {

    eosDisableInterrupts();
    
    *isEmpty = hQueue->numItems == 0;

    eosEnableInterrupts();

    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Afegeix un element en la cua
 *
 *       Funcio:
 *           eosResult eosQueuePut(
 *               eosHQueue hQueue,
 *               void* data)
 *
 *       Entrada:
 *           hQueue: Handler de la cua
 *           data : Punter al buffer de l'element a afeigit
 *
 *       Retorn:
 *           eos_RESULT_SUCCESS si tot es correcte
 *
 *************************************************************************/

eosResult eosQueuePut(
    eosHQueue hQueue,
    void* data) {

    eosResult result = eos_RESULT_SUCCESS;

    eosDisableInterrupts();

	if (hQueue->numItems < hQueue->maxItems) {

        memcpy(hQueue->head, data, hQueue->itemSize);
	    hQueue->head = hQueue->head + hQueue->itemSize;
	    if (hQueue->head >= hQueue->end)
	        hQueue->head = hQueue->start;
		hQueue->numItems++;
	}
    else
        result = eosQUEUE_ERROR_FULL;

    eosEnableInterrupts();

    return result;
}


/*************************************************************************
 *
 *       Exteru un element en la cua
 *
 *       Funcio:
 *           eosResult eosQueueGet(
 *               eosHQueue hQueue,
 *               void* data)
 *
 *       Entrada:
 *           hQueue: Handler de la cua
 *           data  : Punter al buffer de l'element a exterure
 *
 *       Retorn:
 *           eos_RESULT_SUCCESS si tot es correcte
 *
 *************************************************************************/

eosResult eosQueueGet(
    eosHQueue hQueue,
    void *data) {

    eosResult result = eos_RESULT_SUCCESS;

    eosDisableInterrupts();

	if (hQueue->numItems > 0) {
	    memcpy(data, hQueue->tail, hQueue->itemSize);
		hQueue->tail = hQueue->tail + hQueue->itemSize;
	    if (hQueue->tail >= hQueue->end)
	        hQueue->tail = hQueue->start;
		hQueue->numItems--;
    }
	else
        result = eosQUEUE_ERROR_EMPTY;

    eosEnableInterrupts();

	return result;
}
