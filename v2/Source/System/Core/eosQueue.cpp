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

    // Precondicions
    //
    eosAssert(size != 0);
    eosAssert(capacity != 0);

    // Crea la cua
    //
    MsgQueueInitializeInfo info;
    info.maxElements = capacity;
    info.elementSize = size;
    hQueue = osalMsgQueueCreate(&info);
    eosAssert(hQueue != nullptr);
}


/// ----------------------------------------------------------------------
/// \brief Destructor
///
GenericQueue::~GenericQueue() {

    osalMsgQueueDestroy(hQueue);
}


/// ----------------------------------------------------------------------
/// \brief Buida el contingut d'una cua.
///
void GenericQueue::clear() {

    osalMsgQueueClear(hQueue);
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

	return osalMsgQueuePut(hQueue, element, blockTime);
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

	return osalMsgQueueGet(hQueue, element, blockTime);
}


bool GenericQueue::genericPutISR(
    void *element) {

	return osalMsgQueuePutISR(hQueue, element);
}


bool GenericQueue::genericGetISR(
    void *element) {

	return osalMsgQueueGetISR(hQueue, element);
}
