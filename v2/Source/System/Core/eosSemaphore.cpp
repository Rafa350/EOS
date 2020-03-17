#include "eos.h"
#include "eosAssert.h"
#include "OSAL/osalSemaphore.h"
#include "System/Core/eosSemaphore.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Contructor
///
Semaphore::Semaphore() {

    hSemaphore = osalSemaphoreCreate(0);
    eosAssert(hSemaphore != nullptr);
}


/// ----------------------------------------------------------------------
/// \brief Contructor
///
Semaphore::Semaphore(
    unsigned maxCount) {

    hSemaphore = osalSemaphoreCreate(maxCount);
    eosAssert(hSemaphore != nullptr);
}


/// ----------------------------------------------------------------------
/// \brief Destructor.
///
Semaphore::~Semaphore() {

    osalSemaphoreDestroy(hSemaphore);
}


/// ----------------------------------------------------------------------
/// \brief    Espera que s'alliveri el semaforo.
/// \param    blockTime: Temps maxim de bloqueig en milisegons.
/// \return   True si s'ha alliverat. False en cas contrari.
///
bool Semaphore::wait(
    unsigned blockTime) const {

    return osalSemaphoreWait(hSemaphore, blockTime);
}


/// ----------------------------------------------------------------------
/// \brief    Allivera un semaforo.
///
void Semaphore::release() const {

    osalSemaphoreRelease(hSemaphore);
}


/// ----------------------------------------------------------------------
/// \brief    Allivera un semaforo. Versio per cridar des d'una interrupcio.
///
void Semaphore::releaseISR() const {

    osalSemaphoreReleaseISR(hSemaphore);
}
