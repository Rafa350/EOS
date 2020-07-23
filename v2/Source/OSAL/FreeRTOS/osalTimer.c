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
	const TimerInitializeInfo* info) {

	eosAssert(info != NULL);

	// Crea el temporitzador
	//
    HTimer hTimer = (HTimer) xTimerCreate(
    	(const char*)"",
		1,
		(info->options & OSAL_TIMER_AUTO_MASK) == OSAL_TIMER_AUTO_ON ? pdTRUE : pdFALSE,
		(void* const) info->param,
		(void*) info->callback);
    if (hTimer == NULL)
    	return NULL;

    // Para el temporitzador, per que FreeRTOS el crea en marxa.
    //
    xTimerStop((TimerHandle_t)hTimer, 0);

    // Tot correcte. Retorna el handler.
    //
    return hTimer;
}


/// ----------------------------------------------------------------------
/// \brief    Destrueix el temporitzador.
/// \param    hTimer: El handler del temporitzador.
/// \param    blockTime: Els temps maxim de bloqueig en ms.
/// \return   True si tot es correcte. False en cas contrari.
/// \remarks  En cas d'error no s'allibera la memoria, ja que el temporitzador,
///           pot estar pendent de destruccio.
///
bool osalTimerDestroy(
	HTimer hTimer,
	unsigned blockTime) {

	eosAssert(hTimer != NULL);
    
    TickType_t blockTicks = (blockTime == ((unsigned)-1)) ? portMAX_DELAY : blockTime / portTICK_PERIOD_MS;
	return xTimerDelete((TimerHandle_t)hTimer, blockTicks) == pdPASS;
}


/// ----------------------------------------------------------------------
/// \brief    Inicia el temporitzador.
/// \param    hTimer: El handler del temporitzador.
/// \param    time: El temps del temporitzador. Si es zero, el temps es el
///           mateix que tenia en el cicle anterior.
/// \param    blockTime: El temps maxim de bloqueig en ms.
/// \return   True si tot es correcte. False en cas contrari.
///
bool osalTimerStart(
	HTimer hTimer,
	unsigned time,
	unsigned blockTime) {

	eosAssert(hTimer != NULL);

	// Comprova si es dins d'una interrupcio
	//
	if (inISR())  {

		bool result;

		portBASE_TYPE task = pdFALSE;
		if (time == 0)
			result = xTimerStartFromISR((TimerHandle_t)hTimer, &task) == pdPASS;
		else
			result = xTimerChangePeriodFromISR((TimerHandle_t)hTimer, time / portTICK_PERIOD_MS, &task) == pdPASS;
	    portEND_SWITCHING_ISR(task);

	    return result;
	}

	else {
        TickType_t blockTicks = (blockTime == ((unsigned)-1)) ? portMAX_DELAY : blockTime / portTICK_PERIOD_MS;
		if (time == 0)
			return xTimerStart((TimerHandle_t)hTimer, blockTicks) == pdPASS;
		else
			return xTimerChangePeriod((TimerHandle_t)hTimer, time / portTICK_PERIOD_MS, blockTicks) == pdPASS;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Para el temporitzador.
/// \param    hTimer: El handler del temporitzador.
/// \param    blockTime: Temps maxim de bloqueig en ms.
///
bool osalTimerStop(
	HTimer hTimer,
	unsigned blockTime) {

	eosAssert(hTimer != NULL);

    TickType_t blockTicks = (blockTime == ((unsigned)-1)) ? portMAX_DELAY : blockTime / portTICK_PERIOD_MS;
	return xTimerStop((TimerHandle_t)hTimer, blockTicks) == pdPASS;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el temporitzador es actiu.
/// \param    hTimer: El handler del temporitzador.
/// \return   True si es actiu, false en cas contrari.
///
bool osalTimerIsActive(
	HTimer hTimer) {

	eosAssert(hTimer != NULL);

	return xTimerIsTimerActive((TimerHandle_t)hTimer) == pdTRUE;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el context del temporitzador.
/// \param    hTimer: El handler del temporitzador.
/// \return   El context. NULL en cas d'error.
///
void* osalTimerGetContext(
	HTimer hTimer) {

	eosAssert(hTimer != NULL);

	return pvTimerGetTimerID((TimerHandle_t)hTimer);
}
