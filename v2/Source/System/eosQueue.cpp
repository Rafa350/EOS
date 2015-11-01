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
 *       Destructor
 * 
 *       Funcio:
 *           eos::GenericQueue::~GenericQueue() 
 *
 *************************************************************************/

eos::GenericQueue::~GenericQueue() {
    
    vQueueDelete(handle);
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
 *               unsigned blockTime)
 *
 *       Entrada:
 *           data     : Punter al buffer de l'element a afeigit
 *           blockTime: Temps maxim de bloqueig
 *
 *       Retorn:
 *           true si tot es correcte
 *
 *************************************************************************/

bool eos::GenericQueue::put(
    void* data,
    unsigned blockTime) {
    
    return xQueueSendToBack(handle, data, blockTime) == pdPASS;
}


/*************************************************************************
 *
 *       Extreu un element en la cua
 *
 *       Funcio:
 *           bool eos::GenericQueue::get(
 *               void* data,
 *               unsigned blockTime)
 *
 *       Entrada:
 *           data     : Punter al buffer de l'element a exterure
 *           blockTime: Temps maxim de bloqueig
 *
 *       Retorn:
 *           True si tot es correcte
 *
 *************************************************************************/

bool eos::GenericQueue::get(
    void *data,
    unsigned blockTime) {

    return xQueueReceive(handle, data, blockTime) == pdPASS;
}


bool eos::GenericQueue::putISR(void *data) {
    
}


bool eos::GenericQueue::getISR(void *data) {
    
}
