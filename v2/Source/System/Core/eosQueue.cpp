#include "eosAssert.h"
#include "OSAL/osalQueue.h"
#include "System/Core/eosQueue.h"


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

    QueueInitializeInfo info;
    info.maxElements = capacity;
    info.elementSize = size;
    handle = osalQueueCreate(&info);

    eosAssert(handle != nullptr);
}


/// ----------------------------------------------------------------------
/// \brief Destructor
///
GenericQueue::~GenericQueue() {

    osalQueueDestroy(handle);
}


/// ----------------------------------------------------------------------
/// \brief Buida el contingut d'una cua.
///
void GenericQueue::clear() {

    osalQueueClear(handle);
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

	return osalQueuePut(handle, element, blockTime);
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

	return osalQueueGet(handle, element, blockTime);
}


bool GenericQueue::genericPutISR(
    void *element) {

	return osalQueuePutISR(handle, element);
}


bool GenericQueue::genericGetISR(
    void *element) {

	return osalQueueGetISR(handle, element);
}
