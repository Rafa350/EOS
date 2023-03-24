#pragma once
#ifndef __htl__
#define __htl__


#include "eos.h"


namespace htl {
}


#if defined(EOS_PLATFORM_STM32G0) || \
	defined(EOS_PLATFORM_STM32F0) || \
	defined(EOS_PLATFORM_STM32F1) || \
	defined(EOS_PLATFORM_STM32F4) || \
	defined(EOS_PLATFORM_STM32F7)
	#include "HTL/STM32/htl.h"

#else
	#error "Unknown platform"

#endif


#endif // __htl__
