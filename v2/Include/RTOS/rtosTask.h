#pragma once


#include "eos.h"
#include "System/eosCallbacks.h"


namespace rtos {

	class Miliseconds;
	class Task;
	class Ticks;

    struct TaskCallbackArgs {
        Task *task;
        void *params;
    };
    using ITaskCallback = eos::ICallbackP1<const TaskCallbackArgs&>;
    template <typename Instance_> using TaskCallback = eos::CallbackP1<Instance_, const TaskCallbackArgs&>;

	class Task final {
		public:
			enum class Priority {
				high,
				normal,
				low,
				idle
			};
		private:
			void * _handler;
			ITaskCallback * const _taskCallback;
			void * const _taskParams;

		private:
            static void taskFunction(void *params);

		public:
			Task(uint32_t stackDepth, Priority proirity, const char *name, ITaskCallback *taskCallback, void *taskParams);
			~Task();

		public:
            static Task* getExecutingTask();

            static void delay(Ticks ticks);
            static void delay(Miliseconds time);
            static void delay(Miliseconds time, unsigned& weakTime);

            static void enterCriticalSection();
            static void exitCriticalSection();

            static bool waitNotification(bool clear, unsigned waitTime);
            void raiseNotification();
            void raiseNotificationISR();
	};
}
