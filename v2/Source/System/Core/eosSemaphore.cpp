#include "eosAssert.h"
#include "System/Core/eosSemaphore.h"

#include "FreeRTOS.h"
#include "semphr.h"


/// ----------------------------------------------------------------------
/// \brief Contructor
///
eos::BinarySemaphore::BinarySemaphore() {

    handle = xSemaphoreCreateBinary();
    eosAssert(handle != nullptr);
}


/// ----------------------------------------------------------------------
/// \brief Destructor.
///
eos::BinarySemaphore::~BinarySemaphore() {

    vSemaphoreDelete(handle);
}


/// ----------------------------------------------------------------------
/// \brief Espera que s'alliveri el semaforo.
/// \param blockTime: Temps maxim de bloqueig en milisegons.
/// \return True si s'ha alliverat. False en cas contrari.
///
bool eos::BinarySemaphore::take(
    unsigned blockTime) {

    TickType_t ticks = blockTime == -1 ? portMAX_DELAY : blockTime / portTICK_PERIOD_MS;
    return xSemaphoreTake(handle, ticks);
}


/// ----------------------------------------------------------------------
/// \brief Allivera un semaforo.
///
bool eos::BinarySemaphore::give() {

    return xSemaphoreGive(handle);
}


/// ----------------------------------------------------------------------
/// \brief Allivera un semaforo. Versio per cridar des d'una interrupcio.
///
void eos::BinarySemaphore::giveISR() {

    xSemaphoreGiveFromISR(handle, NULL);
}
