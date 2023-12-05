#pragma once
#ifndef __htl__
#define __htl__


#include "eos.h"
#include "System/eosCallbacks.h"


#if defined(EOS_PLATFORM_PIC32MX) || \
    defined(EOS_PLATFORM_PIC32MZ)
    #include "HTL/PIC32/htl.h"

#elif defined(EOS_PLATFORM_STM32G0) || \
	defined(EOS_PLATFORM_STM32F0) || \
	defined(EOS_PLATFORM_STM32F1) || \
	defined(EOS_PLATFORM_STM32F4) || \
	defined(EOS_PLATFORM_STM32F7)
	#include "HTL/STM32/htl.h"

#else
	#error "Unknown platform"

#endif


namespace htl {

    using Tick = uint32_t;

	void initialize();
	void deinitialize();

	Tick getTick();
	void waitTicks(Tick ticks);
	void waitToTick(Tick tick);
	bool hasTickExpired(Tick tick);
}


#endif // __htl__
