#ifndef __EOS_TIMER_H
#define	__EOS_TIMER_H


#include "eos.hpp"
#include "System/eosCallbacks.hpp"
#include "System/eosList.hpp"


#define EV_Timer_onTimeout(cls, instance, method) \
    new eos::CallbackP1<cls, eos::Timer*>(instance, method)


namespace eos {
    
    class Timer;
    typedef Timer *TimerHandle;

    typedef ICallbackP1<TimerHandle> ITimerEvent;
    
    class Timer {
        private:
            void *handler;     
            bool autoreload;
            void *tag;
            ITimerEvent *onTimeout;
            
        public:
            Timer(bool autoreload = false);
            ~Timer();
            void start(unsigned timeout, unsigned blockTime);
            void stop(unsigned blockTime);
            inline void setOnTimeout(ITimerEvent *event) { onTimeout = event; }
            inline void setTag(void *tag) { this->tag = tag; }
            inline void *getTag() const { return tag; }
            bool isActive() const;
        private:
            static void timerCallback(void *handler);
    };
}


#endif	

