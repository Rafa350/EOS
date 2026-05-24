#pragma once


#include "eos.h"


namespace rtos {

	class Miliseconds;
	class Ticks;

	class Kernel final {
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
	};
}
