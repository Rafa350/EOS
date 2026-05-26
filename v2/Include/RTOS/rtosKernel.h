#pragma once


#include "eos.h"


namespace rtos {

	class Miliseconds;
	class Ticks;

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

			static Ticks getTickCount();
			static Miliseconds getTickTime();

			static void enterCritical();
			static void exitCritical();

			static State getState();
			inline static bool isRunning() {
				return  getState() == State::running;
			}
	};
}
