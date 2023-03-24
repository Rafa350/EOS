#pragma once
#ifndef __STM32_htlClock__
#define __STM32_htlClock__


#include "HTL/htl.h"


#if defined(EOS_PLATFORM_STM32F0)
    #include "HTL/STM32/F0/htlClock.h"
#elif defined(EOS_PLATFORM_STM32F1)
    #include "HTL/STM32/F1/htlClock.h"
#elif defined(EOS_PLATFORM_STM32F4)
    #include "HTL/STM32/F4/htlClock.h"
#elif defined(EOS_PLATFORM_STM32F7)
    #include "HTL/STM32/F7/htlClock.h"
#elif defined(EOS_PLATFORM_STM32G0)
    #include "HTL/STM32/G0/htlClock.h"
#else
	#error "Unknown platform"
#endif



#endif // __STM32_htlClock__
