#ifndef __halUART__
#define	__halUART__


// EOS includes
//
#include "eos.h"


#if defined(EOS_PLATFORM_PIC32MX) || defined(EOS_PLATFORM_PIC32MZ)
	#include "HAL/PIC32/halUART.h"

#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
	#include "HAL/STM32/halUART.h"

#endif


#endif // __halUART__

