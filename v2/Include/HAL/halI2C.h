#ifndef __halI2C__
#define __halI2C__


// EOS/HAL includes
//
#include "HAL/hal.h"


#if defined(EOS_PLATFORM_PIC32MX) || defined(EOS_PLATFORM_PIC32MZ)
	#include "HAL/PIC32/halI2C.h"

#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
	#include "HAL/STM32/halI2C.h"

#endif



#endif // __halI2C__
