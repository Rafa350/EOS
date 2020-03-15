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
    
    return xSemaphoreCreateMutex();
}


/// ----------------------------------------------------------------------
/// \brief    Destrueix un mutex.
/// \param   hMutex: El handler del mutex.
///
void osalMutextDestroy(
    HMutex hMutex) {
    
	eosAssert(hMutex != NULL);

	vSemaphoreDelete(hMutex);
}


bool osalMutexLock(
    HMutex hMutex, 
    unsigned blockTime) {

	eosAssert(hMutex != NULL);

	TickType_t blockTicks = (blockTime == ((unsigned)-1)) ? portMAX_DELAY : blockTime / portTICK_PERIOD_MS;
	return xSemaphoreTake(hMutex, blockTicks) == pdTRUE;   
}


bool osalMutexUnlock(
    HMutex hMutex) {

	eosAssert(hMutex != NULL);

    xSemaphoreGive(hMutex);
}
