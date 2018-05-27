#include "eos.h"
#include "System/Core/eosTimer.h"
#include "osal/osalTimer.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Constructor
/// \param autoreload: Indica si repeteix el cicle continuament
///
Timer::Timer(
    bool autoreload) :

    hTimer(nullptr),
    autoreload(autoreload),
	tag(nullptr),
    evTimeout(nullptr) {
}


/// ----------------------------------------------------------------------
/// \brief Destructor
///
Timer::~Timer() {

    if (evTimeout != nullptr)
        delete evTimeout;

    if (hTimer != nullptr)
        osalTimerDestroy(hTimer, 10);
}


/// ----------------------------------------------------------------------
/// \brief Inicia el temporitzador.
/// \param: timeout: Temps de cicle.
/// \param blockTime: Temps maxim de bloqueix en milisegons.
///
void Timer::start(
    unsigned time,
    unsigned blockTime) {

    if (hTimer == nullptr) {

    	TimerInitializeInfo info;
    	info.options = 0;
    	info.options |= autoreload ? OSAL_TIMER_AUTO_ON : OSAL_TIMER_AUTO_OFF;
    	info.callback = timerCallback;
    	info.context = this;
    	hTimer = osalTimerCreate(&info);
    }

    osalTimerStart(hTimer, time, blockTime);
}


/// ----------------------------------------------------------------------
/// \brief Para el temporitzador.
/// \param blockTime: Temps maxim de bloqueig en milisegons.
///
void Timer::stop(
    unsigned blockTime) {

    if (hTimer != nullptr)
    	osalTimerStop(hTimer, blockTime);
}


/// ----------------------------------------------------------------------
/// \brief Comprova si el temporitzador esta actiu.
/// \return True si esta actiu.
///
bool Timer::isActive() const {

    if (hTimer != nullptr)
		return osalTimerIsActive(hTimer);
    else
    	return false;
}


/// ----------------------------------------------------------------------
/// \brief Crida a la funcio 'onTimeout' al final del cicle
/// \param handler: El handler del temporitzador.
///
void Timer::timerCallback(
    HTimer hTimer) {

    Timer *timer = (Timer*) osalTimerGetContext(hTimer);
    if ((timer != nullptr) && (timer->evTimeout != nullptr))
  		timer->evTimeout->execute(timer);
}

