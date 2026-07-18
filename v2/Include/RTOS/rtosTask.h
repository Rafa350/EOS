#pragma once
#ifndef __rtosTask__
#define __rtosTask__


#include "eos.h"
#include "eosCallbacks.h"


namespace eos {

	class Time;
}


namespace rtos {

	class Task final {
		public:
			enum class Priority {
				idle = 0,
				low,
				belowNormal,
				normal,
				aboveNormal,
				high,
				realTime
			};

			enum class State {
				ready,
				running,
				suspended,
				blocked,
				killed,
				unknown
			};

			struct EventArgs {
		    };
		    using IEvent = eos::ICallbackP2<Task*, EventArgs*>;
		    template <typename Instance_> using Event = eos::CallbackP2<Instance_, Task*, EventArgs*>;

		private:
			using Handler = void *;
			using Function = void(*)(void*);

		private:
			IEvent * const _event;
			Handler const _handler;
			uint32_t _lastWeakTick;

		private:
			Task(const Task&) = delete;
			Task(Task&&) = delete;
			Task& operator=(const Task&) = delete;
			Task& operator=(Task&&) = delete;

			static Handler createHandler(Task *task, Function function,
				uint32_t stackDepth, Priority priority, const char *name);
			static void destroyHandler(Handler handler);
            static void taskFunction(void *params);

		public:
			Task(uint32_t stackDepth, Priority priority, const char *name,
				IEvent &event);
			~Task();

		public:
			[[nodiscard]] static Task* getExecutingTask();
			[[nodiscard]] State getState() const;

            static void delay(eos::Time time);
            static void delayUntil(eos::Time time);

            static bool waitNotification(bool clear, eos::Time blockTime);
            void raiseNotification();
            void raiseNotificationISR();

            void suspend() const;
            void resume() const;
            void kill() const;

            [[nodiscard]] bool isAlive() const;

            void setPriority(Priority priority) const;
	};
}


#endif // __rtosTask__
