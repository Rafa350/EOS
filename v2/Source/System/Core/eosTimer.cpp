#include "eos.h"
#include "eosAssert.h"
#include "OSAL/osalTimer.h"
#include "System/Core/eosTimer.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    autoreload: Indica si repeteix el cicle continuament.
///
Timer::Timer(
    bool autoreload) :

    _hTimer {nullptr},
    _autoreload {autoreload},
    _timerEvent {nullptr},
    _param {nullptr} {
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    autoreload: Indica si repeteix el cicle continuament.
///
Timer::Timer(
    bool autoreload,
    ITimerEvent &event,
    void *param) :

    _hTimer {nullptr},
    _autoreload {autoreload},
    _timerEvent {&event},
    _param {param} {
}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
Timer::~Timer() {

    if (_hTimer != nullptr)
        osalTimerDestroy(_hTimer, 10);
}


/// ----------------------------------------------------------------------
/// \brief    Inicia el temporitzador.
/// \param    timeout: Temps de cicle.
/// \param    blockTime: Temps maxim de bloqueix en milisegons.
///
void Timer::start(
    unsigned time,
    unsigned blockTime) {

    if (_hTimer == nullptr) {

    	TimerInitializeInfo info;
    	info.options = 0;
    	info.options |= _autoreload ? OSAL_TIMER_AUTO_ON : OSAL_TIMER_AUTO_OFF;
    	info.callback = timerFunction;
    	info.param = this;
    	_hTimer = osalTimerCreate(&info);
    }

    osalTimerStart(_hTimer, time, blockTime);
}


/// ----------------------------------------------------------------------
/// \brief    Para el temporitzador.
/// \param    blockTime: Temps maxim de bloqueig en milisegons.
///
void Timer::stop(
    unsigned blockTime) {

    if (_hTimer != nullptr)
    	osalTimerStop(_hTimer, blockTime);
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el temporitzador esta actiu.
/// \return   True si esta actiu.
///
bool Timer::isActive() const {

    if (_hTimer != nullptr)
		return osalTimerIsActive(_hTimer);
    else
    	return false;
}


/// ----------------------------------------------------------------------
/// \brief    Executa el callback al final del cicle.
/// \param    hTimer: El handler del temporitzador.
///
void Timer::timerFunction(
    HTimer hTimer) {

    Timer *timer = static_cast<Timer*>(osalTimerGetContext(hTimer));
    if ((timer != nullptr) && (timer->_timerEvent != nullptr)) {

        TimerEventArgs args {
        	.timer = timer,
        	.param = timer->_param
        };

        timer->_timerEvent->execute(args);
    }
}

