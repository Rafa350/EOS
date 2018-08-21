#ifndef __eos__
#define	__eos__


// Compilador Microchip XC32
#if defined(__XC32)

	// Declara la familia del procesador
	#if defined(__PIC32MX)
		#define EOS_PIC32MX
	#elif defined(__PIC32MZ)
		#define EOS_PIC32MZ
	#else
		#error "No se reconoce el procesador"
	#endif

	// Declara el indicador de depuracio
	#if defined(__DEBUG)
		#define EOS_DEBUG
	#endif

// Compilador GNU/STM32
#elif defined(__GNUC__) && defined(STM32)

	// Declara la familia del procesador
	#if defined(STM32F4)
		#define EOS_STM32F4
	#elif defined(STM32F7)
		#define EOS_STM32F7
	#else
		#error "No se reconoce el procesador"
	#endif

	// Declara el indicador de depuracio
	#if defined(DEBUG)
		#define EOS_DEBUG
	#endif

#else
	#error "No se reconoce el compilador"
#endif


// EOS includes
//
#include "eosConfig.h"


#endif // __eos__

