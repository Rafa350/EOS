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
            bool autoreload;
            ITimerEvent *onTimeout;
            
        public:
            Timer(TimerService *service, bool autoreload);
            ~Timer();
            void start(unsigned timeout, unsigned blockTime);
            void stop(unsigned blockTime);
            inline void setOnTimeout(ITimerEvent *event) { onTimeout = event; }
        private:
            static void timerCallback(void *handler);
    };
}


#endif	

