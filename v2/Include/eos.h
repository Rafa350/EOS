#pragma once
#ifndef __eos__
#define __eos__


// Environment detection includes
//
#include "eosVersion.h"
#include "eosToolchain.h"
#include "eosPlatform.h"


#if EOS_TOOLCHAIN_DETECTED != 1
#error "Unknown toolchain"
#endif

#if EOS_PLATFORM_DETECTED != 1
#error "Unknown platform"
#endif


// Standard includes
//
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>


// Platform includes
//
#if defined(EOS_PLATFORM_PIC32MX) || \
	defined(EOS_PLATFORM_PIC32MZ)
	#include "xc.h"

#elif defined(EOS_PLATFORM_STM32F0)
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
    #if defined(EOS_PLATFORM_STM32F746)
        #define STM32F746xx
    #endif
	#include "stm32f7xx.h"

#elif defined(EOS_PLATFORM_STM32G0)
	#if defined(EOS_PLATFORM_STM32G031)
		#define STM32G031xx
	#elif defined(EOS_PLATFORM_STM32G051)
		#define STM32G051xx
	#elif defined(EOS_PLATFORM_STM32G071)
		#define STM32G071xx
	#elif defined(EOS_PLATFORM_STM32G0B1)
		#define STM32G0B1xx
	#endif
	#include "stm32g0xx.h"

#elif defined(EOS_PLATFORM_MSP432)
    #include "msp.h"

#elif defined(EOS_PLATFORM_DOS) || \
	defined(EOS_PLATFORM_WINDOWS)
#endif


// Modus de depuracio
//
#if defined(DEBUG) || defined(_DEBUG) || defined(__DEBUG)
	#define EOS_DEBUG
#endif


// EOS includes
//
#ifndef EOS_NO_INCLUDE_CONFIG
#include "eosConfig.h"
#endif
#ifndef EOS_NO_INCLUDE_BOARD
#include "Board/eosBoard.h"
#endif


// Application entry point
//
void appMain();
void appInitialize();


#endif // __eos__
