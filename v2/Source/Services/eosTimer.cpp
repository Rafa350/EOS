#include "eos.hpp"
#include "Services/eosTimer.hpp"
#include "FreeRTOS.h"
#include "timers.h"


using namespace eos;


/*************************************************************************
 *
 *       Contructor
 * 
 *       Funcio:
 *           TimerService::TimerService() 
 *
 *************************************************************************/

TimerService::TimerService() {
}


/*************************************************************************
 *
 *       Afegeix un temporitzador al servei
 * 
 *       Funcio:
 *           void TimerService::add(
 *               Timer *timer) 
 * 
 *       Entrada:
 *           timer: El temporitzado a afeigir
 *
 *************************************************************************/

void TimerService::add(
    Timer *timer) {
    
    timers.add(timer);
}


Timer::Timer(
    TimerService *service, 
    bool autoreload) {
    
    this->autoreload = autoreload;
    handler = nullptr;
    
    service->add(this);
}

Timer::~Timer() {
    
    if (handler != nullptr)
        xTimerDelete(handler, 100);
}


void Timer::start(
    unsigned timeout,
    unsigned blockTime) {

    if (handler == nullptr) {
        handler = xTimerCreate("", timeout, autoreload, (void*) this, timerCallback);
        xTimerStart(handler, blockTime);
    }
    else {
        xTimerChangePeriod(handler, timeout, blockTime);
    }
}


void Timer::stop(
    unsigned blockTime) {
    
    if (handler != nullptr)
        xTimerStop(handler, blockTime);
}


void Timer::timerCallback(
    void *handler) {
    
    Timer *timer = (Timer*) pvTimerGetTimerID(handler);
    if (timer->onTimeout != nullptr)
        timer->onTimeout->execute(timer);
}
