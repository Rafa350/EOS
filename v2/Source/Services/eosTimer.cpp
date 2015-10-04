#include "eos.hpp"
#include "Services/eosTimer.hpp"
#include "FreeRTOS.h"
#include "timers.h"


/*************************************************************************
 *
 *       Contructor
 * 
 *       Funcio:
 *           eos::TimerService::TimerService() 
 *
 *************************************************************************/

eos::TimerService::TimerService() {
}


void eos::TimerService::add(Timer *timer) {
    
    timers.add(timer);
}


eos::Timer::Timer(
    unsigned period,
    bool autoreload) :
    Timer(nullptr, period, autoreload) {
}


eos::Timer::Timer(
    eos::TimerService *service, 
    unsigned period,
    bool autoreload) {
    
    handler = xTimerCreate("", period, autoreload, (void*) this, timerCallback);
    
    if (service != nullptr)
        service->add(this);
}


void eos::Timer::start(
    unsigned timeout) {
    
    xTimerStart(handler, timeout);
}


void eos::Timer::stop(
    unsigned timeout) {
    
    xTimerStop(handler, timeout);
}


void eos::Timer::restart(
    unsigned timeout) {
    
    xTimerReset(handler, timeout);
}


void eos::Timer::timerCallback(
    void *handler) {
    
    eos::Timer *timer = (eos::Timer*) pvTimerGetTimerID(handler);
    if (timer->onTimeout != nullptr)
        timer->onTimeout->execute(timer);
}
