#pragma once
#ifndef __htlUART__
#define __htlUART__


// EOS includes
//
#include "HTL/htl.h"


#if defined(EOS_PLATFORM_PIC32MX) || \
	defined(EOS_PLATFORM_PIC32MZ)
	#include "HTL/PIC32/htlUART.h"

#elif defined(EOS_PLATFORM_STM32)
	#include "HTL/STM32/htlUART.h"

#elif defined(EOS_PLATFORM_MSP432)
    #include "HTL/MSP432/htlUART.h"

#endif


#endif // __htlUART__
