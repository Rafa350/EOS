#include "eosAssert.h"
#include "System/Core/eosQueue.h"

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
    
    eosArgumentIsNotZero(size);
    eosArgumentIsNotZero(capacity);
    
    handle = xQueueCreate(capacity, size);
    eosAssert(handle != nullptr);
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
    
    eosArgumentIsNotNull(element);

    TickType_t ticks = blockTime == ((unsigned) -1) ? portMAX_DELAY : blockTime / portTICK_PERIOD_MS;
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

    eosArgumentIsNotNull(element);

    TickType_t ticks = blockTime == ((unsigned) -1) ? portMAX_DELAY : blockTime / portTICK_PERIOD_MS;
    return xQueueReceive(handle, element, ticks) == pdPASS;
}


bool GenericQueue::genericPutISR(
    void *element) {
    
    eosArgumentIsNotNull(element);
    
    BaseType_t priority = pdFALSE;    
    return xQueueSendFromISR(handle, element, &priority) == pdPASS;
}


bool GenericQueue::genericGetISR(
    void *element) {
    
    eosArgumentIsNotNull(element);
    
    BaseType_t priority = pdFALSE;    
    return xQueueReceiveFromISR(handle, element, &priority) == pdPASS;
}
