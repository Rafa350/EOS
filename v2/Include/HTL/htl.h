#pragma once


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

	void initialize();
	void deinitialize();

	uint32_t getTick();
	void waitTicks(uint32_t ticks);
}

