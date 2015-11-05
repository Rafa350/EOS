#include "System/eosQueue.hpp"
#include "FreeRTOS.h"
#include "queue.h"


/*************************************************************************
 *
 *       Constructor
 *
 *       Funcio:
 *           eos::GenericQueue::GenericQueue(
 *               unsigned size,
 *               unsigned capacity)
 *
 *       Entrada:
 *           size    : Tamany de cada item
 *           capacity: Numero maxim d'items en la cua
 *
 *************************************************************************/

eos::GenericQueue::GenericQueue(
    unsigned size,
    unsigned capacity) {
    
    handle = xQueueCreate(capacity, size);
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
 *               void *element,
 *               unsigned blockTime)
 *
 *       Entrada:
 *           element  : Punter al element a afeigit
 *           blockTime: Temps maxim de bloqueig
 *
 *       Retorn:
 *           true si tot es correcte
 *
 *************************************************************************/

bool eos::GenericQueue::put(
    void *element,
    unsigned blockTime) {
    
    return xQueueSendToBack(handle, element, blockTime) == pdPASS;
}


/*************************************************************************
 *
 *       Extreu un element en la cua
 *
 *       Funcio:
 *           bool eos::GenericQueue::get(
 *               void *element,
 *               unsigned blockTime)
 *
 *       Entrada:
 *           element  : Punter al element a exterure
 *           blockTime: Temps maxim de bloqueig
 *
 *       Retorn:
 *           True si tot es correcte
 *
 *************************************************************************/

bool eos::GenericQueue::get(
    void *element,
    unsigned blockTime) {

    return xQueueReceive(handle, element, blockTime) == pdPASS;
}


bool eos::GenericQueue::putISR(void *element) {
    
}


bool eos::GenericQueue::getISR(void *element) {
    
}
