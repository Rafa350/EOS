#ifndef __eos__
#define	__eos__


// Microchip XC32 compiler definitions
#if defined(__XC32)

	// Platform definitions
	#if defined(__PIC32MX)
		#define EOS_PIC32MX
	#elif defined(__PIC32MZ)
		#define EOS_PIC32MZ
	#else
		#error "Unknown processor"
	#endif
    #define EOS_PIC32

    // Toolchain definitions
    #define EOS_TOOLCHAIN_XC32

	// Debugger definitions
	#if defined(__DEBUG)
		#define EOS_DEBUG
	#endif

// GNU/STM32 compiler definitions
#elif defined(__GNUC__) && defined(STM32)

	// Platform definitions
	#if defined(STM32F4)
		#define EOS_STM32F4
	#elif defined(STM32F7)
		#define EOS_STM32F7
	#else
		#error "Unknown processor"
	#endif
    #define EOS_STM32

    // Toolchain definitions
    #define EOS_TOOLCHAIN_GNU

	// Debugger definitions
	#if defined(DEBUG)
		#define EOS_DEBUG
	#endif

// GNU/MSP432 compiler definitions
#elif defined(__GNUC__) && defined(MSP432)

    // Platform definitions
    #define EOS_MSP432

    // Toolchain definitions
    #define EOS_TOOLCHAIN_GNU

	// Debugger definitions
	#if defined(DEBUG)
		#define EOS_DEBUG
	#endif

// GNU/MINGW compiler definitions
#elif defined(__GNUC__) && (defined(__MINGW32__) || defined(__MINGW64__))

    // Platform definitions
    #define EOS_DOS
    #define EOS_WINDOWS

    // Toolchain definitions
    #define EOS_TOOLCHAIN_GNU

	// Debugger definitions
	#if defined(DEBUG)
		#define EOS_DEBUG
	#endif

// MSC compiler definitions
#elif defined(_MSC_VER)

	// Platform definitions
    #define EOS_DOS
	#define EOS_WINDOWS

    // Toolchain definitions
    #define EOS_TOOLCHAIN_MVC

#else
	#error "Unknown toolchain"
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
#if defined(EOS_PIC32MX) || defined(EOS_PIC32MZ)
	#include "xc.h"
#elif defined(EOS_STM32F4)
	#include "stm32f4xx.h"
#elif defined(EOS_STM32F7)
	#include "stm32f7xx.h"
#elif defined(EOS_MSP432)
    #include "msp.h"
#elif defined(EOS_DOS) || defined(EOS_WINDOWS)
#endif


// Compiler patchs
//
#ifdef EOS_TOOLCHAIN_XC32
    #define final
#endif


// EOS includes
//
#include "eosConfig.h"
#include "Board/eosBoard.h"


// Base namespace declaration
//
#ifdef __cplusplus
namespace eos {
}
#endif


// Application entry point
//
void appMain();
void appInitialize();


#endif // __eos__

