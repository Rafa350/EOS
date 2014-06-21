#include "eosQueue.h"
#include "eosMemory.h"


typedef struct {        // Cua FIFO
    unsigned size;      // -Tamany de cada element
    unsigned length;    // -Numero maxim d'elements en la cua
    unsigned count;     // -Numero actual d'elements en la cua
    BYTE *start;        // -Punter al inici de la cua
    BYTE *end;          // -Punter al final de la cua
    BYTE *tail;         // -Punter a l'ultim element insertat
    BYTE *head;         // -punter al primer element per extreure
} Queue;


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

    Queue *q = eosAlloc(sizeof(Queue) + queueSize);
    if (q == NULL)
        return eos_ERROR_ALLOC;

    q->start = (BYTE*) q + sizeof(Queue);
    q->end = q->start + queueSize;
    q->size = params->size;
    q->length = params->length;
    q->count = 0;
	q->tail = q->start;
	q->head = q->start;

    *handle = (eosHandle*) q;

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

    Queue *q = (Queue*) handle;

    eosResult result = eos_RESULT_SUCCESS;

	//VOS_ENTER_CRITICAL_SECTION

	if (q->count < q->length) {

        memcpy(q->head, data, q->size);
	    q->head = q->head + q->size;
	    if (q->head >= q->end)
	        q->head = q->start;
		q->count++;
	}
    else
        result = eosQUEUE_ERROR_FULL;

	//VOS_EXIT_CRITICAL_SECTION

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

    Queue *q = (Queue*) handle;

    eosResult result = eos_RESULT_SUCCESS;

	//VOS_ENTER_CRITICAL_SECTION

	if (q->count > 0) {
	    memcpy(data, q->tail, q->size);
		q->tail = q->tail + q->size;
	    if (q->tail >= q->end)
	        q->tail = q->start;
		q->count--;
    }
	else
        result = eosQUEUE_ERROR_EMPTY;

	//VOS_EXIT_CRITICAL_SECTION

	return result;
}
