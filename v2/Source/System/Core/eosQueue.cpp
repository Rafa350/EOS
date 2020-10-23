#include "eos.h"
#include "eosAssert.h"
#include "OSAL/osalQueue.h"
#include "System/Core/eosQueue.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    size: Tamany de cada item.
/// \param    capacity: Numero maxim d'items en la cua.
///
GenericQueue::GenericQueue(
    unsigned size,
    unsigned capacity) {

    eosAssert(size > 0);
    eosAssert(capacity > 0);

    hQueue = osalQueueCreate(capacity, size);
    eosAssert(hQueue != nullptr);
}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
GenericQueue::~GenericQueue() {

    osalQueueDestroy(hQueue);
}


/// ----------------------------------------------------------------------
/// \brief    Buida el contingut d'una cua.
///
void GenericQueue::clear() {

    osalQueueClear(hQueue);
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un element en la cua.
/// \param    element: Punter al element a afeigir.
/// \param    blockTime: Temps maxim de bloqueig en milisegons.
/// \return   True si tot es correcte.
///
bool GenericQueue::genericPut(
    const void* element,
    unsigned blockTime) {

	return osalQueuePut(hQueue, element, blockTime);
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un element en la cua des d'una interrupcio.
/// \param    element: Punter al element a afeigir.
/// \return   True si tot es correcte.
///
bool GenericQueue::genericPutISR(
    void* element) {

	return osalQueuePutISR(hQueue, element);
}


/// ----------------------------------------------------------------------
/// \brief    Extreu un element en la cua.
/// \param    element: Punter al element a extreure.
/// \param    blockTime: Temps maxim de bloqueig en milisegons.
/// \return   True si tot es correcte.
///
bool GenericQueue::genericGet(
    void* element,
    unsigned blockTime) {

	return osalQueueGet(hQueue, element, blockTime);
}


bool GenericQueue::genericGetISR(
    void* element) {

	return osalQueueGetISR(hQueue, element);
}
