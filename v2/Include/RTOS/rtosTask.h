#pragma once


#include "eos.h"
#include "System/eosCallbacks.h"


namespace rtos {

	class Time;
	class Task;

    struct TaskEventArgs {
    };
    using ITaskEvent = eos::ICallbackP2<Task*, TaskEventArgs*>;
    template <typename Instance_> using TaskEvent = eos::CallbackP2<Instance_, Task*, TaskEventArgs*>;

	class Task final {
		public:
			enum class Priority {
				idle = 0,
				low,
				belowNormal,
				normal,
				aboveNormal,
				hight,
				realTime
			};

		private:
			using Handler = void *;
			using Function = void(*)(void*);

		private:
			ITaskEvent * const _taskEvent;
			void * const _handler;
			uint32_t _lastWeakTick;

		private:
			static Handler createHandler(Function function, Task *task,
				uint32_t stackDepth, Priority priority, const char *name);
			static void destroyHandler(Handler handler);
            static void taskFunction(void *params);

		public:
			Task(uint32_t stackDepth, Priority priority, const char *name,
				ITaskEvent &taskEvent);
			~Task();

		public:
            static Task* getExecutingTask();

            static void delay(Time time);
            static void delayUntil(Time time);

            static void enterCriticalSection();
            static void exitCriticalSection();

            static bool waitNotification(bool clear, Time blockTime);
            void raiseNotification();
            void raiseNotificationISR();

            void suspend() const;
            void resume() const;

            void setPriority(Priority priority) const;
	};
}
