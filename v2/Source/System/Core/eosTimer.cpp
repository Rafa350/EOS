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

    handler(nullptr),
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

    if (handler != nullptr)
        osalTimerDestroy(handler, 10);
}


/// ----------------------------------------------------------------------
/// \brief Inicia el temporitzador.
/// \param: timeout: Temps de cicle.
/// \param blockTime: Temps maxim de bloqueix en milisegons.
///
void Timer::start(
    unsigned time,
    unsigned blockTime) {

    if (handler == nullptr) {

    	TimerInitializeInfo info;
    	info.autoreload = autoreload;
    	info.callback = timerCallback;
    	info.context = this;
    	osalTimerCreate(&info, &handler);
    }

    osalTimerStart(handler, time, blockTime);
}


/// ----------------------------------------------------------------------
/// \brief Para el temporitzador.
/// \param blockTime: Temps maxim de bloqueig en milisegons.
///
void Timer::stop(
    unsigned blockTime) {

    if (handler != nullptr)
    	osalTimerStop(handler, blockTime);
}


/// ----------------------------------------------------------------------
/// \brief Comprova si el temporitzador esta actiu.
/// \return True si esta actiu.
///
bool Timer::isActive() const {

    if (handler != nullptr)
		return osalTimerIsActive(handler) == OSAL_STATUS_TRUE;
    else
    	return false;
}


/// ----------------------------------------------------------------------
/// \brief Crida a la funcio 'onTimeout' al final del cicle
/// \param handler: El handler del temporitzador.
///
void Timer::timerCallback(
    void *handler) {

    Timer *timer;
    if (osalTimerGetContext(handler, (void**) &timer) == OSAL_STATUS_OK) {
    	if (timer->evTimeout != nullptr)
    		timer->evTimeout->execute(timer);
    }
}

