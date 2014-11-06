#define __EOS_QUEUE_INTERNAL
#include "System/eosQueue.h"
#include "System/eosMemory.h"


struct __eosQueue {                    // Cua FIFO
    unsigned itemSize;                 // -Tamany de cada element
    unsigned maxItems;                 // -Numero maxim d'elements en la cua
    unsigned numItems;                 // -Numero actual d'elements en la cua
    BYTE *start;                       // -Punter al inici de la cua
    BYTE *end;                         // -Punter al final de la cua
    BYTE *tail;                        // -Punter a l'ultim element insertat
    BYTE *head;                        // -Punter al primer element per extreure
};


/*************************************************************************
 *
 *       Crea una cua de tipus FIFO
 *
 *       Funcio:
 *           eosResult eosQueueCreate(
 *               eosQueueParams *params,
 *               eosQueue *queue)
 *
 *       Entrada:
 *           params: Parametres d'inicialitzacio de la cua
 *
 *       Sortida:
 *           queue: El handler de la cua
 *
 *       Retorn:
 *           eos_RESULT_SUCCESS si tot es correxte
 *
 *************************************************************************/

eosResult eosQueueCreate(eosQueueParams *params, eosQueue *_queue) {

    // Verifica els parametres
    //
#ifdef eos_OPTION_CheckInputParams
    if (_queue == NULL)
        return eos_ERROR_PARAM_NULL;
    if (params == NULL)
        return eos_ERROR_PARAM_NULL;
#endif

    // Inicialitza la cua
    //
    int queueSize = params->maxItems * params->itemSize;

    eosQueue queue = eosAlloc(sizeof(struct __eosQueue) + queueSize);
    if (queue == NULL)
        return eos_ERROR_ALLOC;

    queue->start = (BYTE*) queue + sizeof(struct __eosQueue);
    queue->end = queue->start + queueSize;
    queue->itemSize = params->itemSize;
    queue->maxItems = params->maxItems;
    queue->numItems = 0;
	queue->tail = queue->start;
	queue->head = queue->start;

    *_queue = queue;

    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Comprova si la cua es buida
 *
 *       Funcio:
 *           eosResult eosQueueGetIsEmpry(
 *               eosQueue queue,
 *               BOOL *isEmpry)
 *
 *       Entrada:
 *           queue: Handler de la cua
 *
 *       Sortida:
 *           isEmpty: TRUE si la cua es buida
 *
 *       Retorn:
 *           eos_RESULT_SUCCESS si tot es correcte
 *
 *************************************************************************/

eosResult eosQueueGetIsEmpty(eosQueue queue, BOOL *isEmpty) {

    // Verifica els parametres
    //
#ifdef eos_OPTION_CheckInputParams
    if (queue == NULL)
        return eos_ERROR_PARAM_NULL;
    if (isEmpty == NULL)
        return eos_ERROR_PARAM_NULL;
#endif

    eosDisableInterrupts();
    
    *isEmpty = queue->numItems == 0;

    eosEnableInterrupts();

    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Afegeix un element en la cua
 *
 *       Funcio:
 *           eosResult eosQueuePut(
 *               eosQueue queue,
 *               void* data)
 *
 *       Entrada:
 *           queue: Handler de la cua
 *           data : Punter al buffer de l'element a afeigit
 *
 *       Retorn:
 *           eos_RESULT_SUCCESS si tot es correcte
 *
 *************************************************************************/

eosResult eosQueuePut(eosQueue queue, void* data) {

    // Verifica els parametres
    //
#ifdef eos_OPTION_CheckInputParams
    if (queue == NULL)
        return eos_ERROR_PARAM_NULL;
    if (data == NULL)
        return eos_ERROR_PARAM_NULL;
#endif

    eosResult result = eos_RESULT_SUCCESS;

    eosDisableInterrupts();

	if (queue->numItems < queue->maxItems) {

        memcpy(queue->head, data, queue->itemSize);
	    queue->head = queue->head + queue->itemSize;
	    if (queue->head >= queue->end)
	        queue->head = queue->start;
		queue->numItems++;
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
 *               eosQueue queue,
 *               void* data)
 *
 *       Entrada:
 *           queue: Handler de la cua
 *           data : Punter al buffer de l'element a exterure
 *
 *       Retorn:
 *           eos_RESULT_SUCCESS si tot es correcte
 *
 *************************************************************************/

eosResult eosQueueGet(eosQueue queue, void *data) {

    // Verifica els parametres
    //
#ifdef eos_OPTION_CheckInputParams
    if (queue == NULL)
        return eos_ERROR_PARAM_NULL;
    if (data == NULL)
        return eos_ERROR_PARAM_NULL;
#endif

    eosResult result = eos_RESULT_SUCCESS;

    eosDisableInterrupts();

	if (queue->numItems > 0) {
	    memcpy(data, queue->tail, queue->itemSize);
		queue->tail = queue->tail + queue->itemSize;
	    if (queue->tail >= queue->end)
	        queue->tail = queue->start;
		queue->numItems--;
    }
	else
        result = eosQUEUE_ERROR_EMPTY;

    eosEnableInterrupts();

	return result;
}
