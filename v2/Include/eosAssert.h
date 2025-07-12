#pragma once
#ifndef __eosAssert__
#define __eosAssert__


#include "eos.h"


#if defined(EOS_DEBUG)

#define eosAssert(condition) \
    if (!(condition)) eosErrorHandler(__FILE__, __LINE__, #condition)

#define eosAssertReturn(call, result) \
	if ((call) != (result)) eosErrorHandler(__FILE__, __LINE__, #call)

#define eosWarning(msg) \
    eosErrorHandler(__FILE__, __LINE__, msg)

#define eosFatal(msg) \
    eosErrorHandler(__FILE__, __LINE__, msg)

#else

#define eosAssert(condition)
#define eosAssertReturn(call, result) \
	call
#define eosWarning(msg)
#define eosFatal(msg)

#endif


#if defined(EOS_DEBUG)
#ifdef __cplusplus
extern "C" {
#endif

void eosErrorHandler(const char *file, unsigned line, const char *message);

#ifdef __cplusplus
}
#endif
#endif


#endif // _-eosAssert__
