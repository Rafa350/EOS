#pragma once
#ifndef __eosPlatform__
#define __eosPlatform__


#ifndef EOS_TOOLCHAIN_DETECTED
#include "eosToolchain.h"
#endif


// Microchip XC32 compiler
#if (EOS_TOOLCHAIN_DETECTED == 1) && \
	defined(EOS_TOOLCHAIN_XC32)

    #define EOS_PLATFORM_PIC32

	#if defined(__32MX460F512L__)
        #define EOS_PLATFORM_PIC32MX
        #define EOS_PLATFORM_PIC32MX4
        #define EOS_PLATFORM_PIC32MX460F512L
    #elif defined(__32MX795F512L__)
        #define EOS_PLATFORM_PIC32MX
        #define EOS_PLATFORM_PIC32MX7
        #define EOS_PLATFORM_PIC32MX795F512L
    #else
        #error "Unknown PIC32 processor"
    #endif
    #define EOS_PLATFORM_DETECTED 1


// GNU/STM32 compiler
#elif (EOS_TOOLCHAIN_DETECTED == 1) && \
	  defined(EOS_TOOLCHAIN_GNU)

    #define EOS_PLATFORM_STM32

    // STM32G030xx
    #if defined(STM32G030J6)
        #define EOS_PLATFORM_STM32G0
        #define EOS_PLATFORM_STM32G030
        #define EOS_PLATFORM_STM32G030J6
    #elif defined(STM32G030F6)
        #define EOS_PLATFORM_STM32G0
        #define EOS_PLATFORM_STM32G030
        #define EOS_PLATFORM_STM32G030F6
    #elif defined(STM32G030K6)
        #define EOS_PLATFORM_STM32G0
        #define EOS_PLATFORM_STM32G030
        #define EOS_PLATFORM_STM32G030K6
    #elif defined(STM32G030K8)
        #define EOS_PLATFORM_STM32G0
        #define EOS_PLATFORM_STM32G030
        #define EOS_PLATFORM_STM32G030K8
    #elif defined(STM32G030C6)
        #define EOS_PLATFORM_STM32G0
        #define EOS_PLATFORM_STM32G030
        #define EOS_PLATFORM_STM32G030C6
    #elif defined(STM32G030C8)
        #define EOS_PLATFORM_STM32G0
        #define EOS_PLATFORM_STM32G030
        #define EOS_PLATFORM_STM32G030C8

    // STM32G031xx
    #elif defined(STM32G031J6)
        #define EOS_PLATFORM_STM32G0
        #define EOS_PLATFORM_STM32G031
        #define EOS_PLATFORM_STM32G031J6
    #elif defined(STM32G031F6)
        #define EOS_PLATFORM_STM32G0
        #define EOS_PLATFORM_STM32G031
        #define EOS_PLATFORM_STM32G031F6
    #elif defined(STM32G031K8)
        #define EOS_PLATFORM_STM32G0
        #define EOS_PLATFORM_STM32G031
        #define EOS_PLATFORM_STM32G031K8

    // STM32G051xx
    #elif defined(STM32G051C8)
        #define EOS_PLATFORM_STM32G0
        #define EOS_PLATFORM_STM32G051
        #define EOS_PLATFORM_STM32G051C8
    #elif defined(STM32G051K8)
        #define EOS_PLATFORM_STM32G0
        #define EOS_PLATFORM_STM32G051
        #define EOS_PLATFORM_STM32G051K8

    // STM32G071xx
    #elif defined(STM32G071KB)
        #define EOS_PLATFORM_STM32G0
        #define EOS_PLATFORM_STM32G071
        #define EOS_PLATFORM_STM32G071KB
    #elif defined(STM32G071CB)
        #define EOS_PLATFORM_STM32G0
        #define EOS_PLATFORM_STM32G071
        #define EOS_PLATFORM_STM32G071CB
    #elif defined(STM32G071RB)
        #define EOS_PLATFORM_STM32G0
        #define EOS_PLATFORM_STM32G071
        #define EOS_PLATFORM_STM32G071RB

	// STM32G0B1xx
    #elif defined(STM32G0B1RE)
        #define EOS_PLATFORM_STM32G0
        #define EOS_PLATFORM_STM32G0B1
        #define EOS_PLATFORM_STM32G0B1RE

	// STM32F030xx
	#elif defined(STM32F030R8)
        #define EOS_PLATFORM_STM32F0
        #define EOS_PLATFORM_STM32F030
        #define EOS_PLATFORM_STM32F030R8
    #elif defined(STM32F030RC)
        #define EOS_PLATFORM_STM32F0
        #define EOS_PLATFORM_STM32F030
        #define EOS_PLATFORM_STM32F030RC

    // STM32F103xx
    #elif defined(STM32F103xx)
        #define EOS_PLATFORM_STM32F1
        #define EOS_PLATFORM_STM32F103

    // STM32F429xx
    #elif defined(STM32F429ZI)
        #define EOS_PLATFORM_STM32F4
        #define EOS_PLATFORM_STM32F429
        #define EOS_PLATFORM_STM32F429ZI

    // STM32F746xx
    #elif defined(STM32F746NG)
        #define EOS_PLATFORM_STM32F7
        #define EOS_PLATFORM_STM32F746
        #define EOS_PLATFORM_STM32F746NG

    // STM32F769xx
    #elif defined(STM32F769xx)
        #define EOS_PLATFORM_STM32F7
        #define EOS_PLATFORM_STM32F769

    #else
        #error "Unknown STM32 processor"
    #endif

	#define EOS_PLATFORM_DETECTED 1


// GNU/MSP432 compiler
#elif (EOS_TOOLCHAIN_DETECTED == 1) && \
	  defined(EOS_TOOLCHAIN_GNU) && \
	  defined(MSP432)

    #define EOS_PLATFORM_MSP432
	#define EOS_PLATFORM_DETECTED 1


// GNU/MINGW compiler
#elif (EOS_TOOLCHAIN_DETECTED == 1) && \
	  defined(EOS_TOOLCHAIN_GNU) && \
	  (defined(__MINGW32__) || defined(__MINGW64__))

    #define EOS_PLATFORM_DOS
    #define EOS_PLATFORM_WINDOWS
	#define EOS_PLATFORM_DETECTED 1


// MSC compiler
#elif (EOS_TOOLCHAIN_DETECTED == 1) && \
	  defined(EOS_TOOLCHAIN_MVC)

    #define EOS_PLATFORM_DOS
	#define EOS_PLATFORM_WINDOWS
	#define EOS_PLATFORM_DETECTED 1


#else
	#define EOS_PLATFORM_DETECTED 0
#endif


#ifdef __cplusplus
namespace eos {
	namespace build {

		struct Platform {
			#ifdef EOS_PLATFORM_PIC32
			static constexpr bool is_PIC32_Platform = true;
			#else
			static constexpr bool is_PIC32_Platform = false;
			#endif

			#ifdef EOS_PLATFORM_PIC32MX
			static constexpr bool is_PIC32MX_Platform = true;
			#else
			static constexpr bool is_PIC32MX_Platform = false;
			#endif

			#ifdef EOS_PLATFORM_PIC32MZ
			static constexpr bool is_PIC32MZ_Platform = true;
			#else
			static constexpr bool is_PIC32MZ_Platform = false;
			#endif

			#ifdef EOS_PLATFORM_STM32
			static constexpr bool is_STM32_Platform = true;
			#else
			static constexpr bool is_STM32_Platform = false;
			#endif

			#ifdef EOS_PLATFORM_STM32G0
			static constexpr bool is_STM32G0_Platform = true;
			#else
			static constexpr bool is_STM32G0_Platform = false;
			#endif

			#ifdef EOS_PLATFORM_STM32F0
			static constexpr bool is_STM32F0_Platform = true;
			#else
			static constexpr bool is_STM32F0_Platform = false;
			#endif

			#ifdef EOS_PLATFORM_STM32F4
			static constexpr bool is_STM32F4_Platform = true;
			#else
			static constexpr bool is_STM32F4_Platform = false;
			#endif

			#ifdef EOS_PLATFORM_STM32F7
			static constexpr bool is_STM32F7_Platform = true;
			#else
			static constexpr bool is_STM32F7_Platform = false;
			#endif
		};
	}
}
#endif


#endif // __eosPlatform__
