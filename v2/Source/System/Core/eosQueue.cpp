#include "eos.hpp"
#include "System/Core/eosQueue.hpp"

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
    
    eosAssert(size != 0, 0, "[GenericQueue::ctor] size != 0");
    eosAssert(capacity != 0, 0, "[GenericQueue::ctor] capacity != 0");
    
    handle = xQueueCreate(capacity, size);
    eosAssert(handle != nullptr, 0, "[GenericQueue::ctor] handle != nullptr");
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
/// \param blockTime: Temps maxim de bloqueig en milisegons.
/// \return True si tot es correcte.
///
bool GenericQueue::genericPut(
    const void *element,
    unsigned blockTime) {
    
    eosAssert(element != nullptr, 0, "[GenericQueue::genericPut] element != nullptr");

    TickType_t ticks = blockTime == -1 ? portMAX_DELAY : blockTime / portTICK_PERIOD_MS;
    return xQueueSendToBack(handle, element,  ticks) == pdPASS;
}


/// ----------------------------------------------------------------------
/// \brief Extreu un element en la cua.
/// \param element: Punter al element a extreure.
/// \param blockTime: Temps maxim de bloqueig en milisegons.
/// \return True si tot es correcte. 
///
bool GenericQueue::genericGet(
    void *element,
    unsigned blockTime) {

    eosAssert(element != nullptr, 0, "[GenericQueue::genericGet] element != nullptr");

    TickType_t ticks = blockTime == -1 ? portMAX_DELAY : blockTime / portTICK_PERIOD_MS;
    return xQueueReceive(handle, element, ticks) == pdPASS;
}


bool GenericQueue::genericPutISR(
    void *element) {
    
    eosAssert(element != nullptr, 0, "[GenericQueue::genericPutISR] element != nullptr");
}


bool GenericQueue::genericGetISR(
    void *element) {
    
    eosAssert(element != nullptr, 0, "[GenericQueue::genericGetISR] element != nullptr");
}
