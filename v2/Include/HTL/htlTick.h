#pragma once
#ifndef __htlTick__
#define __htlTick__


#include "HTL/htl.h"


namespace htl {

	namespace tick {

		void initialize();
		void deinitialize();
		void interruptHandler();
	}
}

#endif // __htlTick__

