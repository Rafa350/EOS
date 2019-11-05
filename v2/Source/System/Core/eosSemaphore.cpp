#include "eos.h"
#include "eosAssert.h"
#include "System/Core/eosSemaphore.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Contructor
///
BinarySemaphore::BinarySemaphore() {

    hSemaphore = osalSemaphoreCreate();
    eosAssert(hSemaphore != nullptr);
}


/// ----------------------------------------------------------------------
/// \brief Destructor.
///
BinarySemaphore::~BinarySemaphore() {

    osalSemaphoreDestroy(hSemaphore);
}


/// ----------------------------------------------------------------------
/// \brief Espera que s'alliveri el semaforo.
/// \param blockTime: Temps maxim de bloqueig en milisegons.
/// \return True si s'ha alliverat. False en cas contrari.
///
bool BinarySemaphore::wait(
    int blockTime) {

    return osalSemaphoreWait(hSemaphore, blockTime);
}


/// ----------------------------------------------------------------------
/// \brief Allivera un semaforo.
///
void BinarySemaphore::release() {

    osalSemaphoreRelease(hSemaphore);
}


/// ----------------------------------------------------------------------
/// \brief Allivera un semaforo. Versio per cridar des d'una interrupcio.
///
void BinarySemaphore::releaseISR() {

    osalSemaphoreReleaseISR(hSemaphore);
}
