#ifndef __EOS_HPP
#define	__EOS_HPP


#if defined(__XC)
#include <xc.h>
#elif defined(__GNUC__) && defined(STM32F4)
#include "stm32f4xx.h"
#else
#error "No se reconoce el compilador"
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "eosConfig.h"


#define eosMin(a, b)    (a) < (b) ? a : b
#define eosMax(a, b)    (a) > (b) ? a : b

#ifdef __DEBUG
#define eosAssert(condition, errorCode, message) \
    if (!(condition)) eosErrorHandler(__FILE__, __LINE__, errorCode, message);
#else
#define eosAssert(condition, errorCode, message)
#endif

#ifdef __DEBUG
extern void eosErrorHandler(const char *file, unsigned line, unsigned errorCode, const char *message);
#endif


#endif	

