#ifndef __halINT__
#define __halINT__


// EOS includes
//
#include "eos.h"


#if defined(EOS_PIC32MX) || defined(EOS_PIC32MZ)
	#include "HAL/PIC32/halINT.h"

#elif defined(EOS_STM32F4)
	#include "HAL/STM32/halINT.h"

#endif


#endif // __halINT__
