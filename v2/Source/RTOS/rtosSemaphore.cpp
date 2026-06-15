#include "eos.h"
#include "RTOS/rtosTime.h"
#include "RTOS/rtosSemaphore.h"
#include "System/eosTime.h"

#include "FreeRTOS.h"
#include "semphr.h"


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
rtos::Semaphore::Semaphore():
	_handler {xSemaphoreCreateBinary()} {

}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
rtos::Semaphore::~Semaphore() {

	vSemaphoreDelete(static_cast<SemaphoreHandle_t>(_handler));
}


/// ----------------------------------------------------------------------
/// \brief    Espera el semaforo.
/// \param    blockTime: Tamps de bloqueig en ms.
/// \return   True si es correcte. False en cas d'error o timeout.
///
bool rtos::Semaphore::wait(
	eos::Time blockTime) const {

	return xSemaphoreTake(static_cast<SemaphoreHandle_t>(_handler),
		rtos::toTicks(blockTime)) == pdTRUE;
}


/// ----------------------------------------------------------------------
/// \brief    Allivera el semaforo.
///
void rtos::Semaphore::release() const {

	xSemaphoreGive(static_cast<SemaphoreHandle_t>(_handler));
}


/// ----------------------------------------------------------------------
/// \brief    Allivera el semaforo d'ins d'una funcio ISR.
///
void rtos::Semaphore::releaseISR() const {

	portBASE_TYPE taskWoken = pdFALSE;
	if (xSemaphoreGiveFromISR(static_cast<SemaphoreHandle_t>(_handler),
			&taskWoken) == pdPASS)
		portEND_SWITCHING_ISR(taskWoken);
}
