#include "System/eosQueue.h"
#include "FreeRTOS.h"
#include "queue.h"


/*************************************************************************
 *
 *       Crea una cua de tipus FIFO
 *
 *       Funcio:
 *           eosQueueHandle eosQueueCreate(
 *               unsigned itemSize,
 *               unsigned maxItems)
 *
 *       Entrada:
 *           itemSize: Tamany de cada item
 *           maxItems: Numero maxim d'items en la cua
 *
 *       Retorn:
 *           El handler de la cua. NULL en cas d'error
 *
 *************************************************************************/

eosQueueHandle eosQueueCreate(
    unsigned  itemSize,
    unsigned maxItems) {
    
    return xQueueCreate(maxItems, itemSize);
}


void eosQueueClear(
    eosQueueHandle hQueue) {

    xQueueReset(hQueue);
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
    
    return xQueueSendToBack(hQueue, data, timeout) == pdPASS;
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

    return xQueueReceive(hQueue, data, timeout) == pdPASS;
}


bool eosQueueISRPut(eosQueueHandle hQueue, void *data) {
    
}


bool eosQueueISRGet(eosQueueHandle hQueue, void *data) {
    
}
