#include "osal/osalTimer.h"
#include "FreeRTOS.h"
#include "timers.h"


static int inISR() {

	return __get_IPSR() != 0;
}


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

    TimerHandler h = xTimerCreate(
    	(const char*)"",
		1,
		info->autoreload ? pdTRUE : pdFALSE,
		info->context,
		info->callback);
    if (h == NULL)
    	return OSAL_STATUS_ERROR_RESOURCE;
    xTimerStop(handler, 0);

    *handler = h;
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

	if (xTimerDelete(handler, blockTime / portTICK_PERIOD_MS) != pdPASS)
		return OSAL_STATUS_ERROR_TIMEOUT;

	return OSAL_STATUS_OK;
}


/// ----------------------------------------------------------------------
/// \brief Inicia el temporitzador.
/// \param handler: El handler del temporitzador.
/// \param time: El temps del temporitzador. Si es zero, el temps es el
///              mateix que tenia en el cicle anterior.
/// \param blockTime: El temps maxim de bloqueig.
/// \return El resultat de l'operacio.
///
uint8_t osalTimerStart(
	TimerHandler handler,
	unsigned time,
	unsigned blockTime) {

#ifdef OSAL_CHECK_PARAMETERS
	if (handler == NULL)
		return OSAL_STATUS_ERROR_PARAMETER;
#endif

	// Comprova si es dins d'una interrupcio
	//
	if (inISR())  {

		portBASE_TYPE task = pdFALSE;

		if (time == 0) {
			if (xTimerStartFromISR(handler, &task) != pdPASS)
				return OSAL_STATUS_ERROR_TIMEOUT;
		}
		else {
			if (xTimerChangePeriodFromISR(handler, time / portTICK_PERIOD_MS, &task) != pdPASS)
				return OSAL_STATUS_ERROR_TIMEOUT;
		}
	    portEND_SWITCHING_ISR(task);
	}

	else {
		if (time == 0) {
			if (xTimerStart(handler, blockTime / portTICK_PERIOD_MS) != pdPASS)
				return OSAL_STATUS_ERROR_TIMEOUT;
		}
		else {
			if (xTimerChangePeriod(handler, time / portTICK_PERIOD_MS, blockTime / portTICK_PERIOD_MS) != pdPASS)
				return OSAL_STATUS_ERROR_TIMEOUT;
		}
	}

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

	if (xTimerStop(handler, blockTime / portTICK_PERIOD_MS) != pdPASS)
		return OSAL_STATUS_ERROR_TIMEOUT;

	return OSAL_STATUS_OK;
}


/// ----------------------------------------------------------------------
/// \brief Comprova si el temporitzador es actiu.
/// \param handler: El handler del temporitzador.
/// \return OSAL_STATUS_TRUE si es actiu.
///
uint8_t osalTimerIsActive(
	TimerHandler handler) {

#ifdef OSAL_CHECK_PARAMETERS
	if (handler == NULL)
		return OSAL_STATUS_ERROR_PARAMETER;
#endif

	if (xTimerIsTimerActive(handler) == pdTRUE)
		return OSAL_STATUS_TRUE;
	else
		return OSAL_STATUS_FALSE;
}


/// ----------------------------------------------------------------------
/// \brief Obte el context del temporitzador.
/// \param handler: El handler del temporitzador.
/// \param context: El context obtingut.
/// \return El resultat de l'operacio.
///
uint8_t osalTimerGetContext(
	TimerHandler handler,
	void **context) {

#ifdef OSAL_CHECK_PARAMETERS
	if (handler == NULL)
		return OSAL_STATUS_ERROR_PARAMETER;
	if (context == NULL)
		return OSAL_STATUS_ERROR_PARAMETER;
#endif

	 *context = pvTimerGetTimerID(handler);

	 return OSAL_STATUS_OK;
}
