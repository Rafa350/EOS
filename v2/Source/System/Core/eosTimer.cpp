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

    hTimer(nullptr),
    autoreload(autoreload),
    eventCallback(nullptr),
    eventParam(nullptr) {
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    autoreload: Indica si repeteix el cicle continuament.
///
Timer::Timer(
    bool autoreload,
    IEventCallback* eventCallback,
    void* eventParam) :

    hTimer(nullptr),
    autoreload(autoreload),
    eventCallback(eventCallback),
    eventParam(eventParam) {
}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
Timer::~Timer() {

    if (hTimer != nullptr)
        osalTimerDestroy(hTimer, 10);
}


/// ----------------------------------------------------------------------
/// \brief    Inicia el temporitzador.
/// \param    timeout: Temps de cicle.
/// \param    blockTime: Temps maxim de bloqueix en milisegons.
///
void Timer::start(
    unsigned time,
    unsigned blockTime) {

    if (hTimer == nullptr) {

    	TimerInitializeInfo info;
    	info.options = 0;
    	info.options |= autoreload ? OSAL_TIMER_AUTO_ON : OSAL_TIMER_AUTO_OFF;
    	info.callback = timerFunction;
    	info.param = this;
    	hTimer = osalTimerCreate(&info);
    }

    osalTimerStart(hTimer, time, blockTime);
}


/// ----------------------------------------------------------------------
/// \brief    Para el temporitzador.
/// \param    blockTime: Temps maxim de bloqueig en milisegons.
///
void Timer::stop(
    unsigned blockTime) {

    if (hTimer != nullptr)
    	osalTimerStop(hTimer, blockTime);
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el temporitzador esta actiu.
/// \return   True si esta actiu.
///
bool Timer::isActive() const {

    if (hTimer != nullptr)
		return osalTimerIsActive(hTimer);
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
    if ((timer != nullptr) && (timer->eventCallback != nullptr)) {

        EventArgs args;
        args.timer = timer;
        args.param = timer->eventParam;

        timer->eventCallback->execute(args);
    }
}

