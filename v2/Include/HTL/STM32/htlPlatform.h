#pragma once
#ifndef __STM32_htlPlatform__
#define __STM32_htlPlatform__


#include "eos.h"


#if defined(EOS_PLATFORM_STM32F0)
	#if defined(EOS_PLATFORM_STM32F030R8)
		#define STM32F030x8
	#endif
	#include "stm32f0xx.h"

#elif defined(EOS_PLATFORM_STM32F1)
	#include "stm32f1xx.h"

#elif defined(EOS_PLATFORM_STM32F4)
    #if defined(EOS_PLATFORM_STM32F429)
        #define STM32F429xx
    #endif
    #include "stm32f4xx.h"

#elif defined(EOS_PLATFORM_STM32F7)
	#if !defined(STM32F7)
		#define STM32F7
	#endif
	#if !defined(STM32F7xx)
		#define STM32F7xx
	#endif
    #if defined(EOS_PLATFORM_STM32F746) && !defined(STM32F746xx)
        #define STM32F746xx
    #endif
	#include "stm32f7xx.h"

#elif defined(EOS_PLATFORM_STM32G0)
	#if !defined(STM32G0)
		#define STM32G0
	#endif
	#if !defined(STM32G0xx)
		#define STM32G0xx
	#endif
	#if defined(EOS_PLATFORM_STM32G031) && !defined(STM32G031xx)
		#define STM32G031xx
	#elif defined(EOS_PLATFORM_STM32G051) && !defined(STM32G051xx)
		#define STM32G051xx
	#elif defined(EOS_PLATFORM_STM32G071) && !defined(STM32G071xx)
		#define STM32G071xx
	#elif defined(EOS_PLATFORM_STM32G0B1) && !defined(STM32G0B1xx)
		#define STM32G0B1xx
	#endif
	#include "stm32g0xx.h"
#else
	#error "Unknown platform"
#endif


#endif // __STM32_htlPlatform__
