#ifndef __halUSB__
#define	__halUSB__


// EOS includes
//
#include "eos.h"


#if defined(EOS_PLATFORM_PIC32MX) || defined(EOS_PLATFORM_PIC32MZ)
	#include "HAL/PIC32/halUSB.h"

#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
	#include "HAL/STM32/halUSB.h"

#endif


#endif // __halUSB__

