#pragma once
#ifndef __htlI2C__
#define	__htlI2C__


// EOS includes
//
#include "HTL/htl.h"


#if defined(EOS_PLATFORM_PIC32MX) || defined(EOS_PLATFORM_PIC32MZ)
	#include "HTL/PIC32/htlI2C.h"

#elif defined(EOS_PLATFORM_STM32F0) || defined(EOS_PLATFORM_STM32F1) || \
	defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
	#include "HTL/STM32/htlI2C.h"
    
#elif defined(EOS_PLATFORM_MSP432)
    #include "HTL/MSP432/htlI2C.h"

#endif


#endif // __htlI2C__


