#include "eos.h"
#include "eosAssert.h"
#include "OSAL/osalSemaphore.h"
#include "System/Core/eosSemaphore.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Contructor.
///
Semaphore::Semaphore() {

    _hSemaphore = osalSemaphoreCreate(0);
    eosAssert(_hSemaphore != nullptr);
}


/// ----------------------------------------------------------------------
/// \brief Contructor.
///
Semaphore::Semaphore(
    unsigned maxCount) {

    _hSemaphore = osalSemaphoreCreate(maxCount);
    eosAssert(_hSemaphore != nullptr);
}


/// ----------------------------------------------------------------------
/// \brief Destructor.
///
Semaphore::~Semaphore() {

    osalSemaphoreDestroy(_hSemaphore);
}


/// ----------------------------------------------------------------------
/// \brief    Espera que s'alliveri el semaforo.
/// \param    blockTime: Temps maxim de bloqueig en milisegons.
/// \return   True si s'ha alliverat. False en cas contrari.
///
bool Semaphore::wait(
    unsigned blockTime) const {

    return osalSemaphoreWait(_hSemaphore, blockTime);
}


/// ----------------------------------------------------------------------
/// \brief    Allivera un semaforo.
///
void Semaphore::release() const {

	osalSemaphoreRelease(_hSemaphore);
}


/// ----------------------------------------------------------------------
/// \brief    Allivera un semaforo.
///
void Semaphore::releaseISR() const {

	osalSemaphoreReleaseISR(_hSemaphore);
}

