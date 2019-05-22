#ifndef __eosAssert__
#define	__eosAssert__


#include "eos.h"


#if defined(EOS_DEBUG)

#define eosCheckIsNull(variable) \
    if ((void*)variable == (void*)0) eosErrorHandler(__FILE__, __LINE__, #variable)

#define eosCheckIsZero(variable) \
    if (variable == 0) eosErrorHandler(__FILE__, __LINE__, #variable)

#define eosCheckIsOutOfRange(variable, min, max) \
    if ((variable < min) || (variable > max)) eosErrorHandler(__FILE__, __LINE__, #variable)

#define eosAssert(condition) \
    if (!(condition)) eosErrorHandler(__FILE__, __LINE__, #condition)

#else

#define eosCheckIsNull(variable)
#define eosCheckIsZero(variable)
#define eosCheckIsOutOfRange(variable, min, max)
#define eosAssert(condition)

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


#endif // __eosAssert__

