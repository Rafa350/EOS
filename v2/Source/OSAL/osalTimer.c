#include "osal/osalTimer.h"
#include "eosAssert.h"
#include "FreeRTOS.h"
#include "timers.h"


/// ----------------------------------------------------------------------
/// \brief Crea un temporitzador.
/// \param info: Parametres d'inicialitzacio.
/// \return El handler del temporitzador
///
uint8_t osalTimerCreate(
	const TimerInitializeInfo *info,
	TimerHandler *handler) {

#ifdef OSAL_CHECK_PARAMETERS
	if (info == NULL)
		return OSAL_STATUS_ERROR_PARAMETER;
#endif

    *handler = xTimerCreate(
    	"",
		info->period / portTICK_PERIOD_MS,
		info->autoreload,
		info->context,
		info->callback);
    if (*handler == NULL)
    	return OSAL_STATUS_ERROR_RESOURCE;

    return OSAL_STATUS_OK;
}


/// ----------------------------------------------------------------------
/// \brief Destrueix el temporitzador.
/// \param timer: El handler del temporitzador.
/// \param time: Els temps maxim de bloqueig.
/// \return El resultat de l'operacio.
///
uint8_t osalTimerDestroy(
	TimerHandler handler,
	unsigned blockTime) {

#ifdef OSAL_CHECK_PARAMETERS
	if (handler == NULL)
		return OSAL_STATUS_ERROR_PARAMETER;
#endif

	if (xTimerDelete(handler, blockTime) != pdPASS)
		return OSAL_STATUS_ERROR_RESOURCE;

	return OSAL_STATUS_OK;
}


/// ----------------------------------------------------------------------
/// \brief Inicia el temporitzador.
/// \param handler: El handler del temporitzador.
/// \param blockTime: El temps maxim de bloqueig.
/// \return El resultat de l'operacio.
///
uint8_t osalTimerStart(
	TimerHandler handler,
	unsigned blockTime) {

#ifdef OSAL_CHECK_PARAMETERS
	if (handler == NULL)
		return OSAL_STATUS_ERROR_PARAMETER;
#endif

	if (xTimerStart(handler, blockTime) != pdPASS)
		return OSAL_STATUS_ERROR_TIMEOUT;

	return OSAL_STATUS_OK;
}


/// ----------------------------------------------------------------------
/// \brief Para el temporitzador.
/// \param handler: El handler del temporitzador.
/// \param blockTime: Temps maxim de bloqueig.
/// \return El resultat de l'operacio.
///
uint8_t osalTimerStop(
	TimerHandler handler,
	unsigned blockTime) {

#ifdef OSAL_CHECK_PARAMETERS
	if (handler == NULL)
		return OSAL_STATUS_ERROR_PARAMETER;
#endif

	if (xTimerStop(handler, blockTime) != pdPASS)
			return OSAL_STATUS_ERROR_TIMEOUT;

	return OSAL_STATUS_OK;
}
