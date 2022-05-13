#ifndef __halINT_ex__
#define __halINT_ex__


// EOS includes
//
#include "eos.h"


#if defined(EOS_PIC32MX) || defined(EOS_PIC32MZ)
	#include "HAL/PIC32/halINT_ex.h"

#elif defined(EOS_STM32F4) || defined(EOS_STM32F7)
	#include "HAL/STM32/halINT_ex.h"

#endif


#endif // __halINT_ex__
