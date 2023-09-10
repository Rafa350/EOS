#ifndef __eosTimer__
#define	__eosTimer__


// EOS includes
//
#include "eos.h"
#include "osal/osalTimer.h"
#include "System/eosCallbacks.h"


namespace eos {

	class Timer {
        public:
            struct TimerEventArgs {
                Timer *timer;
                void *param;
            };

        public:
            using ITimerEvent = ICallbackP1<const TimerEventArgs&>;
            template <typename instance_> using TimerEvent = CallbackP1<instance_, const TimerEventArgs&>;

        private:
            HTimer _hTimer;
            bool _autoreload;
            ITimerEvent *_timerEvent;
            void *_param;

        public:
            Timer(bool autoreload = false);
            Timer(bool autoreload, ITimerEvent &event, void *param);
            ~Timer();

            void start(unsigned time, unsigned blockTime);
            void stop(unsigned blockTime);

            bool isActive() const;

        private:
            static void timerFunction(HTimer hTimer);
    };

}


#endif

