#ifndef __EOS_TIMER_H
#define	__EOS_TIMER_H


#include "eos.hpp"
#include "System/eosCallbacks.hpp"
#include "System/eosList.hpp"


#define EV_Timer_onTimeout(cls, instance, method) \
    new eos::CallbackP1<cls, eos::Timer*>(instance, method)


namespace eos {
    
    class Timer;

    typedef List<Timer*> TimerList;
    typedef ListIterator<Timer*> TimerListIterator;
    typedef ICallbackP1<Timer*> ITimerEvent;
    
    class TimerService {
        private:
            TimerList timers;

        public:
            TimerService();
            void add(Timer *timer);
    };
    
    class Timer {
        private:
            void *handler;     
            ITimerEvent *onTimeout;
            
        public:
            Timer(unsigned period, bool autoreload);
            Timer(TimerService *service, unsigned period, bool autoreload);
            void start(unsigned timeout);
            void stop(unsigned timeout);
            void restart(unsigned timeout);
            inline void setOnTimeout(ITimerEvent *event) { onTimeout = event; }
        private:
            static void timerCallback(void *handler);
    };
}


#endif	

