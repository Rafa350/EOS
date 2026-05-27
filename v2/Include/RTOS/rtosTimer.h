#pragma once


#include "eos.h"
#include "System/eosCallbacks.h"


namespace rtos {

	class Time;
	class Timer;

	struct TimerEventArgs {
    };
    using ITimerEvent = eos::ICallbackP2<Timer*, TimerEventArgs*>;
    template <typename Instance_> using TimerEvent = eos::CallbackP2<Instance_, Timer*, TimerEventArgs*>;

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
			ITimerEvent * const _timerEvent;
			Handler const _handler;

		private:
			static Handler createHandler(Function function, Timer *timer, Mode mode, const char *name);
			static void destroyHandler(Handler handler);
			static void timerFunction(Handler handler);

		public:
			Timer(Mode mode, const char *name, ITimerEvent &timerEvent);
			~Timer();

			bool start(Time interval, Time blockTime) const;
			bool startISR(Time interval) const;
			bool restart(Time blockTime) const;
			bool restartISR() const;
			bool stop(Time blockTime) const;

			bool isActive() const;
	};
}
