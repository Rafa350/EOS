#include "System/eosTimer.hpp"
#include "FreeRTOS.h"
#include "timers.h"


using namespace eos;


static const char *defaultTimerName = "";


Timer::Timer(
    bool autoreload) {
    
    this->autoreload = autoreload;
    handler = nullptr;
}

Timer::~Timer() {
    
    //if (onTimeout != nullptr)
    //    delete onTimeout;
    
    if (handler != nullptr)
        xTimerDelete(handler, 100);
}


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


void Timer::stop(
    unsigned blockTime) {
    
    if (handler != nullptr)
        xTimerStop(handler, blockTime);
}


bool Timer::isActive() const {
    
    return handler == nullptr ? false : xTimerIsTimerActive(handler) != pdFALSE;
}


void Timer::timerCallback(
    void *handler) {
    
    Timer *timer = (Timer*) pvTimerGetTimerID(handler);
    if (timer->onTimeout != nullptr)
        timer->onTimeout->execute(timer);
}
