#pragma once
#ifndef __rtosKernel__
#define __rtosKernel__


#include "eos.h"


namespace rtos {

	class Time;

	class Kernel final {
		public:
			enum class State {
				stopped,
				running,
				suspended
			};

		private:
			static void tickHandler();

		public:
			static void startScheduler();
			static void stopScheduler();

			static void suspendAll();
			static void resumeAll();

			static uint32_t getTickCount();
			static Time getTickTime();

			static State getState();
			inline static bool isRunning() {
				return  getState() == State::running;
			}
	};
}


#endif // __rtosKernel__
