#pragma once
#ifndef __rtosCriticalSection__
#define __rtosCriticalSection__


#include "eos.h"


namespace rtos {

	class CriticalSection final {
		public:
			static void enter();
			static void exit();
	};
}


#endif // __rtosCriticalSection__
