#ifndef __EOS_H
#define	__EOS_H


// Compilador Microchip XC32
#if defined(__XC32)

    // Declara el tipus de procesador
    #if defined( __PIC32MX)
        #define EOS_PIC32MX
    #elif defined(__PIC32MZ)
        #define EOS_PIC32MZ
    #endif

    // Declara el indicador de depuracio
    #if defined(__DEBUG)
        #define EOS_DEBUG
    #endif

// Compilador GNU
#elif defined(__GNUC__) 

    #if defined(STM32F4)
        #define EOS_STM32F4
    #endif
            
#else
    #error "No se reconoce el compilador"
#endif


#include "eosConfig.h"


#endif	

