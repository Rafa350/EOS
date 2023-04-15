#pragma once
#ifndef __htlGPIO__
#define	__htlGPIO__


// EOS includes
//
#include "HTL/htl.h"


#if defined(EOS_PLATFORM_PIC32MX) || \
	defined(EOS_PLATFORM_PIC32MZ)
	#include "HTL/PIC32/htlGPIO.h"

#elif defined(EOS_PLATFORM_STM32F0) || \
	defined(EOS_PLATFORM_STM32F1) || \
	defined(EOS_PLATFORM_STM32F4) || \
	defined(EOS_PLATFORM_STM32F7) || \
	defined(EOS_PLATFORM_STM32G0)
	#include "HTL/STM32/htlGPIO.h"

#elif defined(EOS_PLATFORM_MSP432)
    #include "HTL/MSP432/htlGPIO.h"

#else
	#error "Unknown platform"

#endif


#endif // __htlGPIO__

