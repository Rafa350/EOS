#include "System/eosQueue.hpp"
#include "FreeRTOS.h"
#include "queue.h"


using namespace eos;


/*************************************************************************
 *
 *       Constructor
 *
 *       Funcio:
 *           GenericQueue::GenericQueue(
 *               unsigned size,
 *               unsigned capacity)
 *
 *       Entrada:
 *           size    : Tamany de cada item
 *           capacity: Numero maxim d'items en la cua
 *
 *************************************************************************/

GenericQueue::GenericQueue(
    unsigned size,
    unsigned capacity) {
    
    handle = xQueueCreate(capacity, size);
}


/*************************************************************************
 *
 *       Destructor
 * 
 *       Funcio:
 *           GenericQueue::~GenericQueue() 
 *
 *************************************************************************/

GenericQueue::~GenericQueue() {
    
    vQueueDelete(handle);
}


/*************************************************************************
 *
 *       Buida el contingut d'una cua
 * 
 *       Funcio:
 *         void GenericQueue::clear()
 *
 *************************************************************************/

void GenericQueue::clear() {

    xQueueReset(handle);
}


/*************************************************************************
 *
 *       Afegeix un element en la cua
 *
 *       Funcio:
 *           bool GenericQueue::put(
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

bool GenericQueue::put(
    void *element,
    unsigned blockTime) {
    
    return xQueueSendToBack(handle, element, blockTime) == pdPASS;
}


/*************************************************************************
 *
 *       Extreu un element en la cua
 *
 *       Funcio:
 *           bool GenericQueue::get(
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

bool GenericQueue::get(
    void *element,
    unsigned blockTime) {

    return xQueueReceive(handle, element, blockTime) == pdPASS;
}


bool GenericQueue::putISR(void *element) {
    
}


bool GenericQueue::getISR(void *element) {
    
}
