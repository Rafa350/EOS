#pragma once
#ifndef __rtosTime__
#define __rtosTime__


#include "eos.h"
#include "eosTime.h"


namespace rtos {

	uint32_t toTicks(eos::Time time);
}


#endif // __rtosTime__
