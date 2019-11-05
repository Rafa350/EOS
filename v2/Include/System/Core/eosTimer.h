#ifndef __eosTimer__
#define	__eosTimer__


// EOS includes
//
#include "eos.h"
#include "osal/osalTimer.h"
#include "System/eosCallbacks.h"


namespace eos {
    
    class Timer;
    
    struct TimerEventArgs {
        Timer* timer;
    };    

    class Timer {
        private:
            typedef ICallbackP1<const TimerEventArgs&> ITimerEventCallback;

        private:
            HTimer hTimer;
            bool autoreload;
            void *tag;
            ITimerEventCallback *timerEventCallback;

        public:
            Timer(bool autoreload = false);
            ~Timer();
            void start(int time, int blockTime);
            void stop(int blockTime);

            template <class cls>
            inline void setTimerEventCallback(CallbackP1<cls, const TimerEventArgs&> *callback) {
                timerEventCallback = callback;
            }

            inline void setTag(void *tag) { this->tag = tag; }
            inline void *getTag() const { return tag; }
            bool isActive() const;

        private:
            static void timerCallback(HTimer hTimer);
    };
}


#endif

