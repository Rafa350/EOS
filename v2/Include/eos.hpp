#ifndef __EOS_HPP
#define	__EOS_HPP


#if defined(__XC32)
#include <xc.h>
#elif defined(__GNUC__) && defined(STM32F4)
#include "stm32f4xx.h"
#else
#error "No se reconoce el compilador"
#endif

#include "eosConfig.h"


#define eosMin(a, b)    (a) < (b) ? a : b
#define eosMax(a, b)    (a) > (b) ? a : b


#endif	

