#include "System/eosQueue.hpp"
#include "FreeRTOS.h"
#include "queue.h"


/*************************************************************************
 *
 *       Constructor
 *
 *       Funcio:
 *           eos::GenericQueue::GenericQueue(
 *               unsigned itemSize,
 *               unsigned maxItems)
 *
 *       Entrada:
 *           itemSize: Tamany de cada item
 *           maxItems: Numero maxim d'items en la cua
 *
 *************************************************************************/

eos::GenericQueue::GenericQueue(
    unsigned itemSize,
    unsigned maxItems) {
    
    handle = xQueueCreate(maxItems, itemSize);
}


/*************************************************************************
 *
 *       Buida el contingut d'una cua
 * 
 *       Funcio:
 *         void eos::GenericQueue::clear()
 *
 *************************************************************************/

void eos::GenericQueue::clear() {

    xQueueReset(handle);
}


/*************************************************************************
 *
 *       Afegeix un element en la cua
 *
 *       Funcio:
 *           bool eos::GenericQueue::put(
 *               void* data,
 *               unsigned timeout)
 *
 *       Entrada:
 *           data   : Punter al buffer de l'element a afeigit
 *           timeout: Temps maxim d'espera
 *
 *       Retorn:
 *           true si tot es correcte
 *
 *************************************************************************/

bool eos::GenericQueue::put(
    void* data,
    unsigned timeout) {
    
    return xQueueSendToBack(handle, data, timeout) == pdPASS;
}


/*************************************************************************
 *
 *       Extreu un element en la cua
 *
 *       Funcio:
 *           bool eos::GenericQueue::get(
 *               void* data,
 *               unsigned timeout)
 *
 *       Entrada:
 *           data   : Punter al buffer de l'element a exterure
 *           timeout: Temps maxim d'espera
 *
 *       Retorn:
 *           True si tot es correcte
 *
 *************************************************************************/

bool eos::GenericQueue::get(
    void *data,
    unsigned timeout) {

    return xQueueReceive(handle, data, timeout) == pdPASS;
}


bool eos::GenericQueue::putISR(void *data) {
    
}


bool eos::GenericQueue::getISR(void *data) {
    
}
