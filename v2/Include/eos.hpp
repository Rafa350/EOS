#ifndef __EOS_HPP
#define	__EOS_HPP


#include <xc.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "eosConfig.h"


#define eosMin(a, b)    (a) < (b) ? a : b
#define eosMax(a, b)    (a) > (b) ? a : b

#ifdef __DEBUG
#define eosAssert(condition, errorCode, message) \
    if (!(condition)) eosErrorHandler(errorCode, message);
#else
#define eosAssert(condition, errorCode, message)
#endif

#ifdef __DEBUG
extern void eosErrorHandler(unsigned errorCode, const char *message);
#endif


#endif	

