#ifndef __eosInclude__
#define	__eosInclude__


// Includer pel compilador Microchip XC32
#if defined(__XC32)
    #include <xc.h>

// Includes pel compilador GNU STM32
#elif defined(__GNUC__) && defined(STM32F4)
    #include <stm32f4xx.h>

#elif defined(__GNUC__) && defined(STM32F7)
    #include <stm32f7xx.h>

#else
    #error "Compilador no soportado"
#endif


// Includes estandard
#include <stdbool.h>
#include <stdint.h>


#endif // __eosInclude__

