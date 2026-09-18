module;


#include "eos.h"
#include "eosCallbacks.h"

#include "FreeRTOS.h"
#include "timers.h"
#include "atomic.h"


export module Eos.System.Core.Timer;


import Eos.Ticks;
import Eos.System.Core.RTOSUtils;


export namespace eos {

    class Timer final {
    	public:
    		enum class Mode {
    			oneShot,
				autoRestart
    		};

    		struct EventArgs {
    	    };
    	    using IEvent = ICallbackP2<Timer*, EventArgs*>;
    	    template <typename Instance_> using Event = CallbackP2<Instance_, Timer*, EventArgs*>;

		private:
			static constexpr const char *_defaultName = "Timer";

		private:
			IEvent * const _event;
			TimerHandle_t _handler;
#if (configSUPPORT_STATIC_ALLOCATION == 1)
			StaticTimer_t _data;
#endif
			volatile bool _destroying;
			volatile uint32_t _executingCallback;

		private:
			[[nodiscard]] TimerHandle_t createHandler(Mode mode, const char *name);
			static void timerFunction(TimerHandle_t handler);

		public:
			Timer(Mode mode, const char *name, IEvent &event);
			Timer(const Timer&) = delete;
			Timer(Timer&&) = delete;
			~Timer();

			Timer& operator=(const Timer&) = delete;
			Timer& operator=(Timer&&) = delete;

			bool start(Ticks interval, Ticks blockTime) const;
			bool startISR(Ticks interval) const;
			bool restart(Ticks blockTime) const;
			bool restartISR() const;
			bool stop(Ticks blockTime) const;
			bool stopISR() const;

			[[nodiscard]] bool isActive() const;
	};
}


/// ---------------------------------------------------------------------------
/// @brief    Constructor.
/// @param    mode: Modus de funcionament.
/// @param    name: Nom del temporitzador.
/// @param    event: El event 'Timer'.
///
eos::Timer::Timer(
	Mode mode,
	const char *name,
	IEvent &event):

	_event {&event},
	_handler {createHandler(mode, name)},
	_destroying {false},
	_executingCallback {0} {
}


/// ---------------------------------------------------------------------------
/// @brief    Descructor.
///
eos::Timer::~Timer() {

	_destroying = true;

	xTimerStop(_handler, 0);

	while (_executingCallback != 0)
		taskYIELD();

	xTimerDelete(_handler, 0);
}


/// ---------------------------------------------------------------------------
/// @brief    Inicia el temporitzador.
/// @param    interval: El interval. Si es zero, es mante l'actual.
/// @param    blockTime: Temps maxim de bloqueig.
/// @return   True si tot es correcte.
///
bool eos::Timer::start(
	Ticks interval,
	Ticks blockTime) const {

    if (interval.isZero())
        return xTimerStart(
			_handler,
			static_cast<TickType_t>(blockTime)) == pdPASS;
    else
        return xTimerChangePeriod(
			_handler,
			static_cast<TickType_t>(interval),
			static_cast<TickType_t>(blockTime)) == pdPASS;
}


/// ---------------------------------------------------------------------------
/// @brief    Inicia el temporitzador dins d'un ISR
/// @param    interval: El interval. Si es zero, es mante l'actual.
/// @return   Tuue si tot es correcte.
///
bool eos::Timer::startISR(
	Ticks interval) const {

	bool result;

    portBASE_TYPE task = pdFALSE;
    if (interval.isZero())
        result = xTimerStartFromISR(
			_handler,
			&task) == pdPASS;
    else
        result = xTimerChangePeriodFromISR(
			_handler,
			static_cast<TickType_t>(interval),
			&task) == pdPASS;
    portEND_SWITCHING_ISR(task);

    return result;
}


/// ---------------------------------------------------------------------------
/// @brief    Para el tempositzador
/// @param    blockTime: Tamps maxim de bloqueig.
/// @return   TRue si tot es correcte.
///
bool eos::Timer::stop(
	Ticks blockTime) const {

    return xTimerStop(
		_handler,
		static_cast<TickType_t>(blockTime)) == pdPASS;
}


/// ---------------------------------------------------------------------------
/// @brief    Comprova si el temporitzador es actiu.
/// @return   True si es actiu. False en cas contrari.
///
bool eos::Timer::isActive() const {

    return xTimerIsTimerActive(_handler) == pdTRUE;
}


/// ---------------------------------------------------------------------------
/// @brief    Funcio auxiliar per crear el handler del timer.
/// @param    mode: El modus de treball.
/// @param    name: El nom del temporitzador.
///
TimerHandle_t eos::Timer::createHandler(
	Mode mode,
	const char *name) {

#if (configSUPPORT_STATIC_ALLOCATION == 1)
	TimerHandle_t handler =  xTimerCreateStatic(
		name == nullptr ? _defaultName : name,
		1,
		mode == Mode::autoRestart ? pdTRUE : pdFALSE,
		this,
		timerFunction,
		&_data);
#else
	TimerHandle_t handler =  xTimerCreate(
		name == nullptr ? _defaultName : name,
		1,
		mode == Mode::autoRestart ? pdTRUE : pdFALSE,
		this,
		timerFunction);
#endif

    return  handler;
}


/// ---------------------------------------------------------------------------
/// @brief    Funcio callback del temporitzador.
/// @param    handler: Handler del timer.
///
void eos::Timer::timerFunction(
	TimerHandle_t handler) {

	Timer *timer = static_cast<Timer*>(pvTimerGetTimerID(handler));

	if (!timer->_destroying) {

		Atomic_Increment_u32(&timer->_executingCallback);

		if (timer->_event != nullptr) {
			EventArgs args = {
			};
			timer->_event->execute(timer, &args);
		}

		Atomic_Decrement_u32(&timer->_executingCallback);
	}
}


#if (configSUPPORT_STATIC_ALLOCATION == 1)

static StaticTask_t timerTaskTCB;
static StackType_t timerTaskStack[configTIMER_TASK_STACK_DEPTH];

extern "C" void vApplicationGetTimerTaskMemory(
    StaticTask_t **ppxTimerTaskTCBBuffer,
    StackType_t **ppxTimerTaskStackBuffer,
    uint32_t *pulTimerTaskStackSize) {

    *ppxTimerTaskTCBBuffer = &timerTaskTCB;
    *ppxTimerTaskStackBuffer = timerTaskStack;
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}

#endif
