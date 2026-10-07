#pragma once

//#include "HTL/htl.h"
#include "eosPlatform.h"


#if defined(EOS_PLATFORM_PIC32MX) || \
    defined(EOS_PLATFORM_PIC32MZ)
    #include "hardware_pic32.h"

#elif defined(EOS_PLATFORM_STM32)
	#include "hardware_stm32.h"

#else
	#error "Unknown platform"

#endif
