#pragma once


#include "eos.h"
#include "System/eosCallbacks.h"


namespace rtos {

	class Miliseconds;
	class Timer;

	struct TimerCallbackArgs {
        Timer *timer;
        void *params;
    };
    using ITimerCallback = eos::ICallbackP1<const TimerCallbackArgs&>;
    template <typename Instance_> using TimerCallback = eos::CallbackP1<Instance_, const TimerCallbackArgs&>;

    class Timer final {
    	public:
    		enum class Mode {
    			oneShot,
				autoRestart
    		};

		private:
			void * _handler;
			ITimerCallback * const _callback;
			void * const _params;

		private:
			static void timerFunction(void *hTimer);

		public:
			Timer(ITimerCallback *callback, void *pParams, Mode mode);
			~Timer();

			bool start(Miliseconds interval, Miliseconds blockTime);
			bool startISR(Miliseconds interval);
			bool stop(Miliseconds blockTime);

			bool isActive() const;
	};
}
