#include "eos.hpp"
#include "System/Core/eosTimer.hpp"

#include "FreeRTOS.h"
#include "timers.h"


using namespace eos;


static const char *defaultTimerName = "";


/// ----------------------------------------------------------------------
/// \brief Constructor
/// \param autoreload: Indica si repeteix el cicle continuament
///
Timer::Timer(
    bool _autoreload) :
    autoreload(_autoreload),
    handler(nullptr),
    evTimeout(nullptr) {
}


/// ----------------------------------------------------------------------
/// \brief Destructor
///
Timer::~Timer() {
    
    if (evTimeout != nullptr)
        delete evTimeout;
    
    if (handler != nullptr)
        xTimerDelete(handler, 100);
}


/// ----------------------------------------------------------------------
/// \brief Inicia el temporitzador.
/// \param: timeout: Temps de cicle.
/// \param blockTime: Temps maxim de bloqueix
///
void Timer::start(
    unsigned timeout,
    unsigned blockTime) {

    if (handler == nullptr) {
        handler = xTimerCreate(defaultTimerName, timeout, autoreload, (void*) this, timerCallback);
        xTimerStart(handler, blockTime);
    }
    else 
        xTimerChangePeriod(handler, timeout, blockTime);
}


/// ----------------------------------------------------------------------
/// \brief Para el temporitzador.
/// \param blockTime: Temps maxim de bloqueig
///
void Timer::stop(
    unsigned blockTime) {
    
    if (handler != nullptr)
        xTimerStop(handler, blockTime);
}


/// ----------------------------------------------------------------------
/// \brief Comprova si el temporitzador esta actiu.
/// \return True si esta actiu.
///
bool Timer::isActive() const {
    
    return handler == nullptr ? false : xTimerIsTimerActive(handler) != pdFALSE;
}


/// ----------------------------------------------------------------------
/// \brief Crida a la funcio 'onTimeout' al final del cicle
/// \param handler: El handler del temporitzador.
///
void Timer::timerCallback(
    void *handler) {
    
    Timer *timer = (Timer*) pvTimerGetTimerID(handler);
    if (timer->evTimeout != nullptr)
        timer->evTimeout->execute(timer);
}

