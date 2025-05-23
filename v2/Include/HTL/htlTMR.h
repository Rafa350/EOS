#pragma once
#ifndef __htlTMR__
#define __htlTMR__


// EOS includes
//
#include "HTL/htl.h"


#if defined(EOS_PLATFORM_PIC32MX) || \
	defined(EOS_PLATFORM_PIC32MZ)
	#include "HTL/PIC32/htlTMR.h"

#elif defined(EOS_PLATFORM_STM32)
	#include "HTL/STM32/htlTMR.h"

#elif defined(EOS_PLATFORM_MSP432)
    #include "HTL/MSP432/htlTMR.h"

#endif


#endif // __htlTMR__
