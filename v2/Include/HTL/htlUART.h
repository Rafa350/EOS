#pragma once
#ifndef __htlUART__
#define	__htlUART__


// EOS includes
//
#include "HTL/htl.h"


#if defined(EOS_PIC32MX) || defined(EOS_PIC32MZ)
	#include "HTL/PIC32/htlUART.h"

#elif defined(EOS_STM32F4) || defined(EOS_STM32F7)
	#include "HTL/STM32/htlUART.h"

#elif defined(EOS_MSP432)
    #include "HTL/MSP432/htlUART.h"

#endif


#endif // __htlUART__

