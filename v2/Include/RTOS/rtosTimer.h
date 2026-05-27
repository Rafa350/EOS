#pragma once


#include "eos.h"
#include "System/eosCallbacks.h"


namespace rtos {

	class Time;
	class Timer;

	struct TimerCallbackArgs {
    };
    using ITimerCallback = eos::ICallbackP2<Timer*, TimerCallbackArgs&>;
    template <typename Instance_> using TimerCallback = eos::CallbackP2<Instance_, Timer*, TimerCallbackArgs&>;

    class Timer final {
    	public:
    		enum class Mode {
    			oneShot,
				autoRestart
    		};

    	private:
    		using Handler = void*;
    		using Function = void (*)(Handler);

		private:
			ITimerCallback * const _callback;
			Handler const _handler;

		private:
			static Handler createHandler(Function function, Timer *timer, Mode mode, const char *name);
			static void destroyHandler(Handler handler);
			static void timerFunction(Handler handler);

		public:
			Timer(Mode mode, const char *name, ITimerCallback &callback);
			~Timer();

			bool start(Time interval, Time blockTime) const;
			bool startISR(Time interval) const;
			bool restart(Time blockTime) const;
			bool restartISR() const;
			bool stop(Time blockTime) const;

			bool isActive() const;
	};
}
