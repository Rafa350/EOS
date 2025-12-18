#pragma once
#ifndef __eosTimer__
#define	__eosTimer__


// EOS includes
//
#include "eos.h"
#include "osal/osalTimer.h"
#include "System/eosEvents.h"


namespace eos {

	class Timer {
        public:
            struct TimerEventArgs {
            };

        public:
            using TimerEventRaiser = EventRaiser<Timer, TimerEventArgs>;
            using ITimerEvent = TimerEventRaiser::IEvent;
            template <typename Instance_> using TimerEvent = TimerEventRaiser::Event<Instance_>;

        private:
            HTimer _hTimer;
            bool _autoreload;
            TimerEventRaiser _erTimerEvent;

        private:
            static void timerFunction(HTimer hTimer);

        public:
            Timer();
            Timer(bool autoreload);
            Timer(bool autoreload, ITimerEvent &timerEvent);
            ~Timer();

            void start(unsigned time, unsigned blockTime);
            void stop(unsigned blockTime);

            bool isActive() const;
    };

}


#endif

