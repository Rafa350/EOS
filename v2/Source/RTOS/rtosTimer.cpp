#include "RTOS/rtosMiliseconds.h"
#include "RTOS/rtosTicks.h"
#include "RTOS/rtosTimer.h"

#include "FreeRTOS.h"
#include "timers.h"


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    timerCallback: Funcio callback.
/// \params   timerParams: Parametres de la funcio callback.
/// \param    mode: Modus de funcionament
///
rtos::Timer::Timer(
	ITimerCallback *callback,
	void *params,
	Mode mode):

	_callback {callback},
	_params {params} {

	_handler = xTimerCreate(
		(const char*)"",
		1,
		mode == Mode::autoRestart ? pdTRUE : pdFALSE,
		this,
		reinterpret_cast<TimerCallbackFunction_t>(timerFunction));

	// Para el temporitzador, per que FreeRTOS el crea en marxa.
    //
    xTimerStop(static_cast<TimerHandle_t>(_handler), 0);
}


/// ----------------------------------------------------------------------
/// \brief    Descructor.
///
rtos::Timer::~Timer() {

	xTimerDelete(static_cast<TimerHandle_t>(_handler), rtos::Miliseconds(0));
}


/// ----------------------------------------------------------------------
/// \brief    Inicia el temporitzador.
/// \param    interval: El temps en milisegons.
/// \param    blockTime: Temps maxim de bloqueig.
/// \return   TRue si tot es correcte.
///
bool rtos::Timer::start(
	rtos::Miliseconds interval,
	rtos::Miliseconds blockTime) {

    if (interval == 0)
        return xTimerStart(static_cast<TimerHandle_t>(_handler),
        	blockTime.asTicks()) == pdPASS;
    else
        return xTimerChangePeriod(static_cast<TimerHandle_t>(_handler),
        	interval.asTicks(), blockTime.asTicks()) == pdPASS;
}


/// ----------------------------------------------------------------------
/// \brief    Inicia el temporitzador d'ind d'un ISR
/// \param    interval: El temps en milisegons.
/// \return   TRue si tot es correcte.
///
bool rtos::Timer::startISR(
	rtos::Miliseconds interval) {

	bool result;

    portBASE_TYPE task = pdFALSE;
    if (interval == 0)
        result = xTimerStartFromISR(static_cast<TimerHandle_t>(_handler),
        	&task) == pdPASS;
    else
        result = xTimerChangePeriodFromISR(static_cast<TimerHandle_t>(_handler),
        	interval.asTicks(), &task) == pdPASS;
    portEND_SWITCHING_ISR(task);

    return result;
}


/// ----------------------------------------------------------------------
/// \brief    Para el tempositzador
/// \param    blockTime: Tampos maxim de bloqueig.
/// \return   TRue si tot es correcte.
///
bool rtos::Timer::stop(
	rtos::Miliseconds blockTime) {

	return xTimerStop(static_cast<TimerHandle_t>(_handler),
		blockTime.asTicks()) == pdPASS;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el temporitzador es actiu.
/// \return   True si es actiu. False en cas contrari.
///
bool rtos::Timer::isActive() const {

	return xTimerIsTimerActive(static_cast<TimerHandle_t>(_handler)) == pdTRUE;
}


/// ----------------------------------------------------------------------
/// \brief    Funcio callback del temporitzador.
/// \param    hTimer: Handler del timer.
///
void rtos::Timer::timerFunction(
	void *hTimer) {

	rtos::Timer *timer = static_cast<rtos::Timer*>(
		pvTimerGetTimerID(static_cast<TimerHandle_t>(hTimer)));

	TimerCallbackArgs args = {
		.timer = timer,
		.params = timer->_params
	};

	timer->_callback->execute(args);
}
