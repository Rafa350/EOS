#include "System/eosQueue.h"
#include "System/eosMemory.h"


typedef struct {        // Cua FIFO
    unsigned size;      // -Tamany de cada element
    unsigned length;    // -Numero maxim d'elements en la cua
    unsigned count;     // -Numero actual d'elements en la cua
    BYTE *start;        // -Punter al inici de la cua
    BYTE *end;          // -Punter al final de la cua
    BYTE *tail;         // -Punter a l'ultim element insertat
    BYTE *head;         // -Punter al primer element per extreure
} Queue, *PQueue;


/*************************************************************************
 *
 *       Crea una cua de tipus FIFO
 *
 *       Funcio:
 *           eosResult eosQueueCreate(
 *               eosQueueCreateParams *params,
 *               eosHandle *hQueue)
 *
 *       Entrada:
 *           params     : Parametres d'inicialitzacio de la cua
 *
 *       Sortida:
 *           hQueue     : El handler de la cua
 *
 *       Retorn:
 *           eos_RESULT_SUCCESS si tot es correxte
 *
 *************************************************************************/

eosResult eosQueueCreate(eosQueueCreateParams *params, eosHandle *hQueue) {

    // Verifica els parametres
    //
    if (hQueue == NULL)
        return eos_ERROR_PARAM_NULL;
    if (params == NULL)
        return eos_ERROR_PARAM_NULL;

    // Inicialitza la cua
    //
    int queueSize = params->length * params->size;

    PQueue queue = eosAlloc(sizeof(Queue) + queueSize);
    if (queue == NULL)
        return eos_ERROR_ALLOC;

    queue->start = (BYTE*) queue + sizeof(Queue);
    queue->end = queue->start + queueSize;
    queue->size = params->size;
    queue->length = params->length;
    queue->count = 0;
	queue->tail = queue->start;
	queue->head = queue->start;

    *hQueue = (eosHandle) queue;

    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Comprova si la cua es buida
 *
 *       Funcio:
 *           eosResult eosQueueGetIsEmpry(
 *               eosHandle hQueue,
 *               BOOL *isEmpry)
 *
 *       Entrada:
 *           hQueue     : Handler de la cua
 *
 *       Sortida:
 *           isEmpty    : TRUE si la cua es buida
 *
 *       Retorn:
 *           eos_RESULT_SUCCESS si tot es correcte
 *
 *************************************************************************/

eosResult eosQueueGetIsEmpty(eosHandle hQueue, BOOL *isEmpty) {

    // Verifica els parametres
    //
    if (hQueue == NULL)
        return eos_ERROR_PARAM_NULL;
    if (isEmpty == NULL)
        return eos_ERROR_PARAM_NULL;

    PQueue queue = (PQueue) hQueue;

    eosDisableInterrupts();
    
    *isEmpty = queue->count == 0;

    eosEnableInterrupts();

    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Afegeix un element en la cua
 *
 *       Funcio:
 *           eosResult eosQueuePut(
 *               eosHandle hQueue,
 *               void* data)
 *
 *       Entrada:
 *           hQueue     : Handler de la cua
 *           data       : Punter al buffer de l'element a afeigit
 *
 *       Retorn:
 *           eos_RESULT_SUCCESS si tot es correcte
 *
 *************************************************************************/

eosResult eosQueuePut(eosHandle hQueue, void* data) {

    // Verifica els parametres
    //
    if (hQueue == NULL)
        return eos_ERROR_PARAM_NULL;
    if (data == NULL)
        return eos_ERROR_PARAM_NULL;

    PQueue queue = (PQueue) hQueue;

    eosResult result = eos_RESULT_SUCCESS;

    eosDisableInterrupts();

	if (queue->count < queue->length) {

        memcpy(queue->head, data, queue->size);
	    queue->head = queue->head + queue->size;
	    if (queue->head >= queue->end)
	        queue->head = queue->start;
		queue->count++;
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
 *               eosHandle hQueue,
 *               void* data)
 *
 *       Entrada:
 *           hQueue     : Handler de la cua
 *           data       : Punter al buffer de l'element a exterure
 *
 *       Retorn:
 *           eos_RESULT_SUCCESS si tot es correcte
 *
 *************************************************************************/

eosResult eosQueueGet(eosHandle hQueue, void *data) {

    // Verifica els parametres
    //
    if (hQueue == NULL)
        return eos_ERROR_PARAM_NULL;
    if (data == NULL)
        return eos_ERROR_PARAM_NULL;

    PQueue queue = (PQueue) hQueue;

    eosResult result = eos_RESULT_SUCCESS;

    eosDisableInterrupts();

	if (queue->count > 0) {
	    memcpy(data, queue->tail, queue->size);
		queue->tail = queue->tail + queue->size;
	    if (queue->tail >= queue->end)
	        queue->tail = queue->start;
		queue->count--;
    }
	else
        result = eosQUEUE_ERROR_EMPTY;

    eosEnableInterrupts();

	return result;
}