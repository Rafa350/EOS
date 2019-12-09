#include "eos.h"
#include "eosAssert.h"
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

    eosAssert(size != 0);
    eosAssert(capacity != 0);

    QueueInitializeInfo info;
    info.maxElements = capacity;
    info.elementSize = size;
    hQueue = osalQueueCreate(&info);
    eosAssert(hQueue != nullptr);
}


/// ----------------------------------------------------------------------
/// \brief Destructor
///
GenericQueue::~GenericQueue() {

    osalQueueDestroy(hQueue);
}


/// ----------------------------------------------------------------------
/// \brief Buida el contingut d'una cua.
///
void GenericQueue::clear() {

    osalQueueClear(hQueue);
}



/// ----------------------------------------------------------------------
/// \brief Afegeix un element en la cua.
/// \param element: Punter al element a afeigir.
/// \param blockTime: Temps maxim de bloqueig en milisegons.
/// \return True si tot es correcte.
///
bool GenericQueue::genericPut(
    const void *element,
    int blockTime) {

	return osalQueuePut(hQueue, element, blockTime);
}


/// ----------------------------------------------------------------------
/// \brief Extreu un element en la cua.
/// \param element: Punter al element a extreure.
/// \param blockTime: Temps maxim de bloqueig en milisegons.
/// \return True si tot es correcte.
///
bool GenericQueue::genericGet(
    void *element,
    int blockTime) {

	return osalQueueGet(hQueue, element, blockTime);
}


bool GenericQueue::genericPutISR(
    void *element) {

	return osalQueuePutISR(hQueue, element);
}


bool GenericQueue::genericGetISR(
    void *element) {

	return osalQueueGetISR(hQueue, element);
}
