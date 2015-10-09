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


void TimerService::add(Timer *timer) {
    
    timers.add(timer);
}


Timer::Timer(
    unsigned period,
    bool autoreload) :
    Timer(nullptr, period, autoreload) {
}


Timer::Timer(
    TimerService *service, 
    unsigned period,
    bool autoreload) {
    
    handler = xTimerCreate("", period, autoreload, (void*) this, timerCallback);
    
    if (service != nullptr)
        service->add(this);
}


void Timer::start(
    unsigned timeout) {
    
    xTimerStart(handler, timeout);
}


void Timer::stop(
    unsigned timeout) {
    
    xTimerStop(handler, timeout);
}


void Timer::restart(
    unsigned timeout) {
    
    xTimerReset(handler, timeout);
}


void Timer::timerCallback(
    void *handler) {
    
    Timer *timer = (Timer*) pvTimerGetTimerID(handler);
    if (timer->onTimeout != nullptr)
        timer->onTimeout->execute(timer);
}
