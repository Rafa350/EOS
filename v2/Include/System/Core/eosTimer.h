#pragma once
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
                void *param;
            };

        public:
            using ITimerEvent = ICallbackP2<const Timer*, const TimerEventArgs&>;
            template <typename Instance_> using TimerEvent = CallbackP2<Instance_, const Timer*, const TimerEventArgs&>;

        private:
            HTimer _hTimer;
            bool _autoreload;
            ITimerEvent *_timerEvent;
            bool _timerEventEnabled;
            void *_param;

        public:
            Timer();
            Timer(bool autoreload = false);
            Timer(bool autoreload, ITimerEvent &event, void *param);
            ~Timer();

            void setTimerEvent(ITimerEvent &event, bool enabled = true);
            inline void enableTimerEvent() {
                _timerEventEnabled = _timerEvent != nullptr;
            }
            inline void disableTimerEvent() {
                _timerEventEnabled = false;
            }
            void start(unsigned time, unsigned blockTime);
            void stop(unsigned blockTime);

            bool isActive() const;

        private:
            static void timerFunction(HTimer hTimer);
    };

}


#endif

