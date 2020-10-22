#include "eos.h"
#include "eosAssert.h"
#include "OSAL/osalMutex.h"
#include "FreeRTOS.h"
#include "semphr.h"


/// ----------------------------------------------------------------------
/// \brief    Crea un mutex.
/// \return   El handler del mutex.
///
HMutex osalMutexCreate() {

    return (HMutex) xSemaphoreCreateMutex();
}


/// ----------------------------------------------------------------------
/// \brief    Destrueix un mutex.
/// \param   hMutex: El handler del mutex.
///
void osalMutexDestroy(
    HMutex hMutex) {

	eosAssert(hMutex != NULL);

	vSemaphoreDelete((SemaphoreHandle_t) hMutex);
}


/// ----------------------------------------------------------------------
/// \brief    Bloqueja el mutex, o espera que es pugui fer.
/// \param    hMutes: El handler del mutes.
/// \param    blockTime: Temps maxim de bloqueig.
/// \return   True si tot es correcte.
///
bool osalMutexWait(
    HMutex hMutex,
    unsigned blockTime) {

	eosAssert(hMutex != NULL);

	TickType_t blockTicks = (blockTime == ((unsigned)-1)) ? portMAX_DELAY : blockTime / portTICK_PERIOD_MS;
	return xSemaphoreTake((SemaphoreHandle_t) hMutex, blockTicks) == pdTRUE;
}


/// ----------------------------------------------------------------------
/// \brief    Desbloqueja un mutex.
/// \param    hMutex: Handler del mutex.
///
bool osalMutexRelease(
    HMutex hMutex) {

	eosAssert(hMutex != NULL);

    return xSemaphoreGive((SemaphoreHandle_t) hMutex)  == pdTRUE;
}
