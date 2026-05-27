#include "RTOS/rtosTime.h"
#include "RTOS/rtosTimer.h"

#include "FreeRTOS.h"
#include "timers.h"


static constexpr const char *defaultName = "Timer";


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    mode: Modus de funcionament.
/// \param    name: Nom del temporitzador.
/// \param    timerEvent: El event 'Timer'.
///
rtos::Timer::Timer(
	Mode mode,
	const char *name,
	ITimerEvent &timerEvent):

	_timerEvent {&timerEvent},
	_handler {createHandler(timerFunction, this, mode, name)} {
}


/// ----------------------------------------------------------------------
/// \brief    Descructor.
///
rtos::Timer::~Timer() {

	destroyHandler(_handler);
}


/// ----------------------------------------------------------------------
/// \brief    Inicia el temporitzador.
/// \param    interval: El temps en milisegons. Si es zero, es mante
///           el interval actual
/// \param    blockTime: Temps maxim de bloqueig.
/// \return   TRue si tot es correcte.
///
bool rtos::Timer::start(
	rtos::Time interval,
	rtos::Time blockTime) const {

    if (interval.isZero())
        return xTimerStart(static_cast<TimerHandle_t>(_handler),
        	blockTime.toTicks()) == pdPASS;
    else
        return xTimerChangePeriod(static_cast<TimerHandle_t>(_handler),
        	interval.toTicks(), blockTime.toTicks()) == pdPASS;
}


/// ----------------------------------------------------------------------
/// \brief    Inicia el temporitzador d'ind d'un ISR
/// \param    interval: El temps en milisegons. Si es zero, es mante
///           el interval actual.
/// \return   Tuue si tot es correcte.
///
bool rtos::Timer::startISR(
	rtos::Time interval) const {

	bool result;

    portBASE_TYPE task = pdFALSE;
    if (interval.isZero())
        result = xTimerStartFromISR(static_cast<TimerHandle_t>(_handler),
        	&task) == pdPASS;
    else
        result = xTimerChangePeriodFromISR(static_cast<TimerHandle_t>(_handler),
        	interval.toTicks(), &task) == pdPASS;
    portEND_SWITCHING_ISR(task);

    return result;
}


/// ----------------------------------------------------------------------
/// \brief    Para el tempositzador
/// \param    blockTime: Tampos maxim de bloqueig.
/// \return   TRue si tot es correcte.
///
bool rtos::Timer::stop(
	rtos::Time blockTime) const {

	return xTimerStop(static_cast<TimerHandle_t>(_handler),
		blockTime.toTicks()) == pdPASS;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el temporitzador es actiu.
/// \return   True si es actiu. False en cas contrari.
///
bool rtos::Timer::isActive() const {

	return xTimerIsTimerActive(static_cast<TimerHandle_t>(_handler)) == pdTRUE;
}


/// ----------------------------------------------------------------------
/// \brief    Funcio auxiliar per crear el handler del timer.
/// \param    function: La funcio callback.
/// \param    timer: El temporitzador que s'esta creant.
/// \param    mode: El modus de treball.
///
rtos::Timer::Handler rtos::Timer::createHandler(
	Function function,
	Timer *timer,
	Mode mode,
	const char *name) {

	return xTimerCreate(
		name == nullptr ? defaultName : name,
		1,
		mode == rtos::Timer::Mode::autoRestart ? pdTRUE : pdFALSE,
		timer,
		reinterpret_cast<TimerCallbackFunction_t>(function));
}


/// ----------------------------------------------------------------------
/// \brief    Destrueix el handler del timer.
///
void rtos::Timer::destroyHandler(
	Handler handler) {

	xTimerDelete(static_cast<TimerHandle_t>(handler), 0);
}


/// ----------------------------------------------------------------------
/// \brief    Funcio callback del temporitzador.
/// \param    handler: Handler del timer.
///
void rtos::Timer::timerFunction(
	Handler handler) {

	rtos::Timer *timer = static_cast<rtos::Timer*>(
		pvTimerGetTimerID(static_cast<TimerHandle_t>(handler)));

	if (timer->_timerEvent != nullptr) {
		TimerEventArgs args = {
		};
		timer->_timerEvent->execute(timer, &args);
	}
}
