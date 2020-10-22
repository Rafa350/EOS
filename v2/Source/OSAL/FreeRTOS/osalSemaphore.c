#include "eos.h"
#include "eosAssert.h"
#include "OSAL/osalSemaphore.h"

#include "FreeRTOS.h"
#include "semphr.h"


/// ----------------------------------------------------------------------
/// \brief    Crea un semafor binari
/// \param    maxCount: Valor maxim del contador. 0 per semafor binari
/// \return   El handler del semafor.
///
HSemaphore osalSemaphoreCreate(
    unsigned maxCount) {

    if (maxCount == 0)
    	return (HSemaphore) xSemaphoreCreateBinary();
    else
        return (HSemaphore) xSemaphoreCreateCounting(maxCount, 0);

}


/// ----------------------------------------------------------------------
/// \brief    Destrueix un semafor.
/// \param    hSemaphore: El handler del semafor.
///
void osalSemaphoreDestroy(
	HSemaphore hSemaphore) {

	eosAssert(hSemaphore != NULL);

	vSemaphoreDelete((SemaphoreHandle_t) hSemaphore);
}


/// ----------------------------------------------------------------------
/// \brief    Espera en un semafor fins que s'alliveri, o fins el temps
///           maxim d'espera.
/// \param    hSemaphore: El handler del semaphor.
/// \param    blockTime: Temps maxim de bloqueig en ms.
///
bool osalSemaphoreWait(
	HSemaphore hSemaphore,
	unsigned blockTime) {

	eosAssert(hSemaphore != NULL);

	TickType_t blockTicks = (blockTime == ((unsigned) -1)) ? portMAX_DELAY : blockTime / portTICK_PERIOD_MS;

	bool result;
	if (__is_isr_code()) {
		BaseType_t taskWoken = pdFALSE;
	    result = xSemaphoreTakeFromISR((SemaphoreHandle_t) hSemaphore, &taskWoken);
    	portEND_SWITCHING_ISR(taskWoken)
	}
	else
		result = xSemaphoreTake((SemaphoreHandle_t) hSemaphore, blockTicks) == pdTRUE;
	return result;
}


/// ----------------------------------------------------------------------
/// \brief    Allivera un semafor.
/// \param    hSemaphore: El handler del semafor.
///
void osalSemaphoreRelease(
    HSemaphore hSemaphore) {

	eosAssert(hSemaphore != NULL);

	if (__is_isr_code()) {
		portBASE_TYPE taskWoken = pdFALSE;
		xSemaphoreGiveFromISR((SemaphoreHandle_t) hSemaphore, &taskWoken);
		portEND_SWITCHING_ISR(taskWoken)
	}
	else
		xSemaphoreGive((SemaphoreHandle_t) hSemaphore);
}


/// ----------------------------------------------------------------------
/// \brief    Allivera un semafor desde d'ins d'una interrupcio
/// \param    hSemaphore: El handler del semafor.
///
void osalSemaphoreReleaseISR(
	HSemaphore hSemaphore) {

	eosAssert(hSemaphore != NULL);

	portBASE_TYPE taskWoken = pdFALSE;
	xSemaphoreGiveFromISR((SemaphoreHandle_t) hSemaphore, &taskWoken);
	portEND_SWITCHING_ISR(taskWoken)
}
