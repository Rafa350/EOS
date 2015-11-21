#include "System/eosQueue.hpp"
#include "FreeRTOS.h"
#include "queue.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param size: Tamany de cada item.
/// \param capacity: Numero maxim d'items en la cua.
///
GenericQueue::GenericQueue(
    unsigned size,
    unsigned capacity) {
    
    handle = xQueueCreate(capacity, size);
}


/// ----------------------------------------------------------------------
/// \brief Destructor
///
GenericQueue::~GenericQueue() {
    
    vQueueDelete(handle);
}


/// ----------------------------------------------------------------------
/// \brief Buida el contingut d'una cua.
///
void GenericQueue::clear() {

    xQueueReset(handle);
}


/// ----------------------------------------------------------------------
/// \brief Afegeix un element en la cua.
/// \param element: Punter al element a afeigir.
/// \param blockTime: Temps maxim de bloqueig.
/// \return True si tot es correcte
///
bool GenericQueue::genericPut(
    void *element,
    unsigned blockTime) {
    
    return xQueueSendToBack(handle, element, blockTime) == pdPASS;
}


/// ----------------------------------------------------------------------
/// \brief Extreu un element en la cua.
/// \param element: Punter al element a exterure.
/// \param blockTime: Temps maxim de bloqueig
///
bool GenericQueue::genericGet(
    void *element,
    unsigned blockTime) {

    return xQueueReceive(handle, element, blockTime) == pdPASS;
}


bool GenericQueue::putISR(void *element) {
    
}


bool GenericQueue::getISR(void *element) {
    
}
