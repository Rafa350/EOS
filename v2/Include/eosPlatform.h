#pragma once
#ifndef __eosPlatform__
#define __eosPlatform__


#ifndef EOS_TOOLCHAIN_DETECTED
#include "eosToolchain.h"
#endif


// Microchip XC32 compiler
#if (EOS_TOOLCHAIN_DETECTED == 1) && \
	defined(EOS_TOOLCHAIN_XC32)

	// Platform definitions
	#if defined(__PIC32MX)
        #define EOS_PLATFORM_PIC32MX
        #if defined(__32MX460F512L__)
            #define EOS_PLATFORM_PIC32MX4
        #elif defined(__32MX795F512L__)
            #define EOS_PLATFORM_PIC32MX7
        #else
            #error  "Unknown processor PIC32MX"
        #endif
    #elif defined(__PIC32MZ)
		#define EOS_PLATFORM_PIC32MZ
	#else
		#error "Unknown processor"
	#endif
    #define EOS_PLATFORM_PIC32
	#define EOS_PLATFORM_DETECTED 1


// GNU/STM32 compiler
#elif (EOS_TOOLCHAIN_DETECTED == 1) && \
	  defined(EOS_TOOLCHAIN_GNU) && \
	  defined(STM32)

	// Platform definitions
    #if defined(STM32F0)
		#if defined(STM32F030F4) || \
            defined(STM32F030x8)
			#define EOS_PLATFORM_STM32F0
		#else
            #error  "Unknown processor STM32F0"
		#endif
	#elif defined(STM32F1)
		#if defined(STM32F103xx)
			#define EOS_PLATFORM_STM32F1
		#else
            #error  "Unknown processor STM32F1"
		#endif
	#elif defined(STM32F4)
		#if defined(STM32F429)
			#define EOS_PLATFORM_STM32F4
		#else
			#error "Unknown processor STM32F4"
		#endif
	#elif defined(STM32F7)
		#if defined(STM32F746xx) || \
		    defined(STM32F769xx)
			#define EOS_PLATFORM_STM32F7
		#else
            #error  "Unknown processor STM32F7"
		#endif
	#else
		#error "Unknown processor"
	#endif
    #define EOS_PLATFORM_STM32
	#define EOS_PLATFORM_DETECTED 1


// GNU/MSP432 compiler
#elif (EOS_TOOLCHAIN_DETECTED == 1) && \
	  defined(EOS_TOOLCHAIN_GNU) && \
	  defined(MSP432)

    // Platform definitions
    #define EOS_PLATFORM_MSP432
	#define EOS_PLATFORM_DETECTED 1


// GNU/MINGW compiler
#elif (EOS_TOOLCHAIN_DETECTED == 1) && \
	  defined(EOS_TOOLCHAIN_GNU) && \
	  (defined(__MINGW32__) || defined(__MINGW64__))

    // Platform definitions
    #define EOS_PLATFORM_DOS
    #define EOS_PLATFORM_WINDOWS
	#define EOS_PLATFORM_DETECTED 1


// MSC compiler
#elif (EOS_TOOLCHAIN_DETECTED == 1) && \
	  defined(EOS_TOOLCHAIN_MVC)

	// Platform definitions
    #define EOS_PLATFORM_DOS
	#define EOS_PLATFORM_WINDOWS
	#define EOS_PLATFORM_DETECTED 1


#else
	#define EOS_PLATFORM_DETECTED 0
#endif


#ifdef __cplusplus
namespace eos {
	namespace build {
		#ifdef EOS_PLATFORM_PIC32
			constexpr bool is_PIC32_Platform = true;
		#else
			constexpr bool is_PIC32_Platform = false;
		#endif

		#ifdef EOS_PLATFORM_PIC32MX
			constexpr bool is_PIC32MX_Platform = true;
		#else
			constexpr bool is_PIC32MX_Platform = false;
		#endif

		#ifdef EOS_PLATFORM_PIC32MZ
			constexpr bool is_PIC32MZ_Platform = true;
		#else
			constexpr bool is_PIC32MZ_Platform = false;
		#endif

		#ifdef EOS_PLATFORM_STM32
			constexpr bool is_STM32_Platform = true;
		#else
			constexpr bool is_STM32_Platform = false;
		#endif

		#ifdef EOS_PLATFORM_STM32F0
			constexpr bool is_STM32F0_Platform = true;
		#else
			constexpr bool is_STM32F0_Platform = false;
		#endif

		#ifdef EOS_PLATFORM_STM32F4
			constexpr bool is_STM32F4_Platform = true;
		#else
			constexpr bool is_STM32F4_Platform = false;
		#endif

		#ifdef EOS_PLATFORM_STM32F7
			constexpr bool is_STM32F7_Platform = true;
		#else
			constexpr bool is_STM32F7_Platform = false;
		#endif
	}
}
#endif


#endif // __eosPlatform__
