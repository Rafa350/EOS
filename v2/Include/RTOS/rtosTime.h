#pragma once
#ifndef __rtosTime__
#define __rtosTime__


#include "eos.h"


namespace eos {

	class Time;
}


namespace rtos {

	uint32_t toTicks(eos::Time time);
}


#endif // __rtosTime__
