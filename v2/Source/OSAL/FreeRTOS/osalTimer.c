#include "eos.h"
#include "eosAssert.h"
#include "OSAL/osalTimer.h"
#include "FreeRTOS.h"
#include "timers.h"
#include "stddef.h"


static int inISR() {
#ifdef STM32
	return __get_IPSR() != 0;
#else
    return 0;
#endif
}


/// ----------------------------------------------------------------------
/// \brief    Crea un temporitzador.
/// \param    info: Parametres d'inicialitzacio.
/// \return   El handler del timer. NULL en cas d'error.
///
HTimer osalTimerCreate(
	const TimerInitializeInfo *info) {

	eosAssert(info != NULL);

	// Crea el temporitzador
	//
    HTimer hTimer = xTimerCreate(
    	(const char*)"",
		1,
		(info->options & OSAL_TIMER_AUTO_MASK) == OSAL_TIMER_AUTO_ON ? pdTRUE : pdFALSE,
		(void* const) info->context,
		(void*) info->callback);
    if (hTimer == NULL)
    	return NULL;

    // Para el temporitzador, per que FreeRTOS el crea en marxa.
    //
    xTimerStop(hTimer, 0);

    // Tot correcte. Retorna el handler.
    //
    return hTimer;
}


/// ----------------------------------------------------------------------
/// \brief    Destrueix el temporitzador.
/// \param    hTimer: El handler del temporitzador.
/// \param    waitTime: Els temps maxim d'espera.
/// \return   True si tot es correcte. False en cas contrari.
/// \remarks  En cas d'error no s'allibera la memoria, ja que el temporitzador,
///           pot estar pendent de destruccio.
///
bool osalTimerDestroy(
	HTimer hTimer,
	int waitTime) {

	eosAssert(hTimer != NULL);

	return xTimerDelete(hTimer, waitTime / portTICK_PERIOD_MS) == pdPASS;
}


/// ----------------------------------------------------------------------
/// \brief    Inicia el temporitzador.
/// \param    hTimer: El handler del temporitzador.
/// \param    time: El temps del temporitzador. Si es zero, el temps es el
///           mateix que tenia en el cicle anterior.
/// \param    waitTime: El temps maxim de bloqueig.
/// \return   True si tot es correcte. False en cas contrari.
///
bool osalTimerStart(
	HTimer hTimer,
	int time,
	int waitTime) {

	eosAssert(hTimer != NULL);

	// Comprova si es dins d'una interrupcio
	//
	if (inISR())  {

		bool result;

		portBASE_TYPE task = pdFALSE;
		if (time == 0)
			result = xTimerStartFromISR(hTimer, &task) == pdPASS;
		else
			result = xTimerChangePeriodFromISR(hTimer, time / portTICK_PERIOD_MS, &task) == pdPASS;
	    portEND_SWITCHING_ISR(task);

	    return result;
	}

	else {
		if (time == 0)
			return xTimerStart(hTimer, waitTime / portTICK_PERIOD_MS) == pdPASS;
		else
			return xTimerChangePeriod(hTimer, time / portTICK_PERIOD_MS, waitTime / portTICK_PERIOD_MS) == pdPASS;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Para el temporitzador.
/// \param    hTimer: El handler del temporitzador.
/// \param    waitTime: Temps maxim de bloqueig.
///
bool osalTimerStop(
	HTimer hTimer,
	int waitTime) {

	eosAssert(hTimer != NULL);

	return xTimerStop(hTimer, waitTime / portTICK_PERIOD_MS) == pdPASS;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el temporitzador es actiu.
/// \param    hTimer: El handler del temporitzador.
/// \return   True si es actiu, false en cas contrari.
///
bool osalTimerIsActive(
	HTimer hTimer) {

	eosAssert(hTimer != NULL);

	return xTimerIsTimerActive(hTimer) == pdTRUE;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el context del temporitzador.
/// \param    hTimer: El handler del temporitzador.
/// \return   El context. NULL en cas d'error.
///
void *osalTimerGetContext(
	HTimer hTimer) {

	eosAssert(hTimer != NULL);

	return pvTimerGetTimerID(hTimer);
}
