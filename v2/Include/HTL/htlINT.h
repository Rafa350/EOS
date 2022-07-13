#ifndef __htlINT__
#define __htlINT__


// EOS includes
//
#include "eos.h"


#if defined(EOS_PIC32MX) || defined(EOS_PIC32MZ)
	#include "HTL/PIC32/htlINT.h"

#elif defined(EOS_STM32F4) || defined(EOS_STM32F7)
	#include "HTL/STM32/htlINT.h"

#endif


#endif // __htlINT__
