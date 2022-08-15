#ifndef __halTMR__
#define	__halTMR__


// HAL includes
//
#include "HAL/hal.h"


#if defined(EOS_PLATFORM_PIC32MX) || defined(EOS_PLATFORM_PIC32MZ)
	#include "HAL/PIC32/halTMR.h"

#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
	#include "hal/STM32/halTMR.h"

#endif


#endif // __halTMR__
