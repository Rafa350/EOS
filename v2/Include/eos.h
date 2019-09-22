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

	// Debugger definitions
	#if defined(DEBUG)
		#define EOS_DEBUG
	#endif

// GNU/MSP432 compiler definitions
#elif defined(__GNUC__) && defined(MSP432)

    // Platform definitions
    #define EOS_MSP432

	// Debugger definitions
	#if defined(DEBUG)
		#define EOS_DEBUG
	#endif

// GNU/MINGW compiler definitions
#elif defined(__GNUC__) && (defined(__MINGW32__) || defined(__MINGW64__))

    // Platform definitions
    #define EOS_WINDOWS

	// Debugger definitions
	#if defined(DEBUG)
		#define EOS_DEBUG
	#endif

#else
	#error "Unknown compiler"
#endif


// Standard includes
//
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>


// Platform includes
//
#if defined(EOS_PIC32MX)
	#include "xc.h"
#elif defined(EOS_PIC32MZ)
	#include "xc.h"
#elif defined(EOS_STM32F4)
	#include "stm32f4xx.h"
#elif defined(EOS_STM32F7)
	#include "stm32f7xx.h"
#elif defined(EOS_MSP432)    
    #include "msp.h"
#endif


// Compiler patchs
//
#ifdef __XC32
    #define final
#endif


// EOS includes
//
#include "eosConfig.h"


// Declaracions previes
//
#ifdef __cplusplus
namespace eos {
	class Application;
	class Service;
}
#endif


// Entrada a l'aplicacio
//
void appMain();
void appInitialize();


#endif // __eos__

