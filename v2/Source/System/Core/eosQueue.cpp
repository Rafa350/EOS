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

    _hQueue = osalQueueCreate(capacity, size);
    eosAssert(_hQueue != nullptr);
}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
GenericQueue::~GenericQueue() {

    osalQueueDestroy(_hQueue);
}


/// ----------------------------------------------------------------------
/// \brief    Buida el contingut d'una cua.
///
void GenericQueue::clear() {

    osalQueueClear(_hQueue);
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un element en la cua.
/// \param    element: Punter al element a afeigir.
/// \param    blockTime: Temps maxim de bloqueig en milisegons.
/// \return   True si tot es correcte.
///
bool GenericQueue::genericPut(
    const void *element,
    unsigned blockTime) {

	return osalQueuePut(_hQueue, element, blockTime);
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un element en la cua des d'una interrupcio.
/// \param    element: Punter al element a afeigir.
/// \return   True si tot es correcte.
///
bool GenericQueue::genericPutISR(
    void *element) {

	return osalQueuePutISR(_hQueue, element);
}


/// ----------------------------------------------------------------------
/// \brief    Extreu un element en la cua.
/// \param    element: Punter al element a extreure.
/// \param    blockTime: Temps maxim de bloqueig en milisegons.
/// \return   True si tot es correcte.
///
bool GenericQueue::genericGet(
    void *element,
    unsigned blockTime) {

	return osalQueueGet(_hQueue, element, blockTime);
}


/// ----------------------------------------------------------------------
/// \brief    Obte un element en la cua.
/// \param    element: Punter a l'element.
/// \param    blockTime: Temps maxim de bloqueig en milisegons.
/// \return   True si tot es correcte.
///
bool GenericQueue::genericPeek(
    void *element,
    unsigned blockTime) {

	return osalQueuePeek(_hQueue, element, blockTime);
}

/// ----------------------------------------------------------------------
/// \brief    Extreu un element en la cua d'ins d'una interrupcio.
/// \param    element: Punter al element a extreure.
/// \return   True si tot es correcte.
///
bool GenericQueue::genericGetISR(
    void *element) {

	return osalQueueGetISR(_hQueue, element);
}
