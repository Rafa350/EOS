#pragma once
#ifndef __htlTMR__
#define	__htlTMR__


// EOS includes
//
#include "eos.h"


#if defined(EOS_PIC32MX) || defined(EOS_PIC32MZ)
	#include "HTL/PIC32/htlTMR.h"

#elif defined(EOS_STM32F4) || defined(EOS_STM32F7)
	#include "HTL/STM32/htlTMR.h"

#elif defined(EOS_MSP432)
    #include "HTL/MSP432/htlTMR.h"

#endif


#endif // __htlTMR__

