#ifndef __EOS_HPP
#define	__EOS_HPP


#include <xc.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "eosConfig.h"


#define eosMin(a, b)    (a) < (b) ? a : b
#define eosMax(a, b)    (a) > (b) ? a : b

#ifdef __EOS_DEBUG
#define eosAssert(condition, errorCode, message) \
    if (!(condition)) eosErrorHandler(errorCode, message);
#else
#define eosAssert(condition, errorCode, message)
#endif


extern void eosErrorHandler(unsigned errorCode, char *message);


#endif	

