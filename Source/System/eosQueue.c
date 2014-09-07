#include "System/eosQueue.h"
#include "System/eosMemory.h"


typedef struct {        // Cua FIFO
    unsigned size;      // -Tamany de cada element
    unsigned length;    // -Numero maxim d'elements en la cua
    unsigned count;     // -Numero actual d'elements en la cua
    BYTE *start;        // -Punter al inici de la cua
    BYTE *end;          // -Punter al final de la cua
    BYTE *tail;         // -Punter a l'ultim element insertat
    BYTE *head;         // -punter al primer element per extreure
} Queue, *PQueue;


/*************************************************************************
 *
 *       Crea una cua de tipus FIFO
 *
 *       Funcio:
 *           eosResult eosQueueCreate(
 *               eosQueueCreateParams *params,
 *               eosHandle *handle)
 *
 *       Entrada:
 *           params: Parametres d'inicialitzacio de la cua
 *
 *       Sortida:
 *           handle: El handler de la cua
 *
 *       Retorn:
 *           eos_RESULT_SUCCESS si tot es correxte
 *
 *************************************************************************/

eosResult eosQueueCreate(eosQueueCreateParams *params, eosHandle *handle) {

    // Verifica els parametres
    //
    if (handle == NULL)
        return eos_ERROR_PARAMS;
    if (params == NULL)
        return eos_ERROR_PARAMS;

    // Inicialitza la cua
    //
    int queueSize = params->length * params->size;

    PQueue pQueue = eosAlloc(sizeof(Queue) + queueSize);
    if (pQueue == NULL)
        return eos_ERROR_ALLOC;

    pQueue->start = (BYTE*) pQueue + sizeof(Queue);
    pQueue->end = pQueue->start + queueSize;
    pQueue->size = params->size;
    pQueue->length = params->length;
    pQueue->count = 0;
	pQueue->tail = pQueue->start;
	pQueue->head = pQueue->start;

    *handle = (eosHandle) pQueue;

    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Comprova si la cua es buida
 *
 *       Funcio:
 *           eosResult eosQueueGetIsEmpry(eosHandle handle, BOOL *isEmpry)
 *
 *       Entrada:
 *           handle: Handler de la cua
 *
 *       Sortida:
 *           isEmpty: TRUE si la cua es buida
 *
 *       Retorn:
 *           eos_RESULT_SUCCESS si tot es correcte
 *
 *************************************************************************/

eosResult eosQueueGetIsEmpty(eosHandle handle, BOOL *isEmpty) {

    // Verifica els parametres
    //
    if (handle == NULL)
        return eos_ERROR_PARAMS;
    if (isEmpty == NULL)
        return eos_ERROR_PARAMS;

    PQueue pQueue = (PQueue) handle;

    eosDisableInterrupts();
    
    *isEmpty = pQueue->count == 0;

    eosEnableInterrupts();

    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Afegeix un element en la cua
 *
 *       Funcio:
 *           eosResult eosQueuePut(eosHandle handle, void* data)
 *
 *       Entrada:
 *           handle: Handler de la cua
 *           data  : Punter al buffer de l'element a afeigit
 *
 *       Retorn:
 *           eos_RESULT_SUCCESS si tot es correcte
 *
 *************************************************************************/

eosResult eosQueuePut(eosHandle handle, void* data) {

    // Verifica els parametres
    //
    if (handle == NULL)
        return eos_ERROR_PARAMS;
    if (data == NULL)
        return eos_ERROR_PARAMS;

    PQueue pQueue = (PQueue) handle;

    eosResult result = eos_RESULT_SUCCESS;

    eosDisableInterrupts();

	if (pQueue->count < pQueue->length) {

        memcpy(pQueue->head, data, pQueue->size);
	    pQueue->head = pQueue->head + pQueue->size;
	    if (pQueue->head >= pQueue->end)
	        pQueue->head = pQueue->start;
		pQueue->count++;
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
 *           eosResult eosQueueGet(eosHandle handle, void* data)
 *
 *       Entrada:
 *           handle: Handler de la cua
 *           data  : Punter al buffer de l'element a exterure
 *
 *       Retorn:
 *           eos_RESULT_SUCCESS si tot es correcte
 *
 *************************************************************************/

eosResult eosQueueGet(eosHandle handle, void *data) {

    // Verifica els parametres
    //
    if (handle == NULL)
        return eos_ERROR_PARAMS;
    if (data == NULL)
        return eos_ERROR_PARAMS;

    PQueue pQueue = (PQueue) handle;

    eosResult result = eos_RESULT_SUCCESS;

    eosDisableInterrupts();

	if (pQueue->count > 0) {
	    memcpy(data, pQueue->tail, pQueue->size);
		pQueue->tail = pQueue->tail + pQueue->size;
	    if (pQueue->tail >= pQueue->end)
	        pQueue->tail = pQueue->start;
		pQueue->count--;
    }
	else
        result = eosQUEUE_ERROR_EMPTY;

    eosEnableInterrupts();

	return result;
}
