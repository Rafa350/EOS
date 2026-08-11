#pragma once
#ifndef __htl__
#define __htl__


#include "eos.h"


#if defined(EOS_PLATFORM_PIC32MX) || \
    defined(EOS_PLATFORM_PIC32MZ)
    #include "HTL/PIC32/htl.h"

#elif defined(EOS_PLATFORM_STM32)
	#include "HTL/STM32/htl.h"

#else
	#error "Unknown platform"

#endif


namespace htl {

	void initialize();
	void deinitialize();

	unsigned getTick();
	void waitTicks(uint32_t ticks);
	void waitToTick(uint32_t tick);
	bool hasTickExpired(uint32_t tick);
}


#endif // __htl__
