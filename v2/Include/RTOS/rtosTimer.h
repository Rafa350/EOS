#pragma once
#ifndef __rtosTimer__
#define __rtosTimer__


#include "eos.h"
#include "System/eosCallbacks.h"


namespace eos {

	class Time;
}


namespace rtos {

    class Timer final {
    	public:
    		enum class Mode {
    			oneShot,
				autoRestart
    		};

    		struct EventArgs {
    	    };
    	    using IEvent = eos::ICallbackP2<Timer*, EventArgs*>;
    	    template <typename Instance_> using Event = eos::CallbackP2<Instance_, Timer*, EventArgs*>;

    	private:
    		using Handler = void*;
    		using Function = void (*)(Handler);

		private:
			IEvent * const _event;
			Handler const _handler;
			volatile bool _destroying;
			volatile uint32_t _executingCallback;

		private:
			Timer(const Timer&) = delete;
			Timer(Timer&&) = delete;
			Timer& operator=(const Timer&) = delete;
			Timer& operator=(Timer&&) = delete;

			static Handler createHandler(Function function, Timer *timer, Mode mode, const char *name);
			static void timerFunction(Handler handler);

		public:
			Timer(Mode mode, const char *name, IEvent &event);
			~Timer();

			bool start(eos::Time interval, eos::Time blockTime) const;
			bool startISR(eos::Time interval) const;
			bool restart(eos::Time blockTime) const;
			bool restartISR() const;
			bool stop(eos::Time blockTime) const;
			bool stopISR() const;

			[[nodiscard]] bool isActive() const;
	};
}


#endif // __rtosTimer__
