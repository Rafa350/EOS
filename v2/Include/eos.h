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
		#error "No se reconoce el procesador"
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
		#error "No se reconoce el procesador"
	#endif

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
	#error "No se reconoce el compilador"
#endif


// Standard includes
//
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>


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
#endif


// EOS includes
//
#include "eosConfig.h"


// Entrada a l'aplicacio
//
void AppMain();
void AppInitialize();


#endif // __eos__

