#ifndef __halSYS__
#define	__halSYS__


// HAL includes
//
#include "HAL/hal.h"


#if defined(EOS_PLATFORM_PIC32MX) || defined(EOS_PLATFORM_PIC32MZ)
	#include "HAL/PIC32/halSYS.h"

#elif defined(EOS_PLATFORM_STM32F0) || defined(EOS_PLATFORM_STM32F1) || \
	defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
	#include "HAL/STM32/halSYS.h"

#endif


#endif // __halSYS__


