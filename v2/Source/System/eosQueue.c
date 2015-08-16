#include "System/eosQueue.h"
#include "System/eosMemory.h"
#include "FreeRTOS.h"
#include "queue.h"


typedef struct __eosQueue {            
    QueueHandle_t rtosHandle;
} eosQueue;


/*************************************************************************
 *
 *       Crea una cua de tipus FIFO
 *
 *       Funcio:
 *           eosQueueHandle eosQueueCreate(
 *               eosQueueParams *params)
 *
 *       Entrada:
 *           params: Parametres d'inicialitzacio de la cua
 *
 *       Retorn:
 *           El handler de la cua. NULL en cas d'error
 *
 *************************************************************************/

eosQueueHandle eosQueueCreate(
    eosQueueParams *params) {
    
    eosQueueHandle hQueue = eosAlloc(sizeof(eosQueue));
    if (hQueue != NULL) {
        
        hQueue->rtosHandle = xQueueCreate(params->maxItems, params->itemSize);
        if (hQueue->rtosHandle == NULL) {
            
            eosFree(hQueue);
            hQueue = NULL;
        }
    }
    return hQueue;
}


/*************************************************************************
 *
 *       Afegeix un element en la cua
 *
 *       Funcio:
 *           bool eosQueuePut(
 *               eosQueueHandle hQueue,
 *               void* data,
 *               unsigned timeout)
 *
 *       Entrada:
 *           hQueue : Handler de la cua
 *           data   : Punter al buffer de l'element a afeigit
 *           timeout: Temps maxim d'espera
 *
 *       Retorn:
 *           true si tot es correcte
 *
 *************************************************************************/

bool eosQueuePut(
    eosQueueHandle hQueue,
    void* data,
    unsigned timeout) {
    
    return xQueueSend(hQueue, data, timeout / portTICK_PERIOD_MS) == pdPASS;
}


/*************************************************************************
 *
 *       Extreu un element en la cua
 *
 *       Funcio:
 *           bool eosQueueGet(
 *               eosQueueHandle hQueue,
 *               void* data,
 *               unsigned timeout)
 *
 *       Entrada:
 *           hQueue : Handler de la cua
 *           data   : Punter al buffer de l'element a exterure
 *           timeout: Temps maxim d'espera
 *
 *       Retorn:
 *           True si tot es correcte
 *
 *************************************************************************/

bool eosQueueGet(
    eosQueueHandle hQueue,
    void *data,
    unsigned timeout) {

    return xQueueReceive(hQueue, data, timeout / portTICK_PERIOD_MS) == pdPASS;
}


bool eosQueueISRPut(eosQueueHandle hQueue, void *data) {
    
}


bool eosQueueISRGet(eosQueueHandle hQueue, void *data) {
    
}
