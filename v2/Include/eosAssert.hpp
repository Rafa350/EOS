#ifndef __EOS_ASSERT_HPP
#define	__EOS_ASSERT_HPP


#include "eos.hpp"


#if defined(EOS_DEBUG)

#define eosArgumentIsNotNull(variable) \
    if (variable == nullptr) eosErrorHandler(__FILE__, __LINE__, #variable)

#define eosArgumentIsNotZero(variable) \
    if (variable == 0) eosErrorHandler(__FILE__, __LINE__, #variable)

#define eosAssert(condition) \
    if (!(condition)) eosErrorHandler(__FILE__, __LINE__, #condition)

#else

#define eosArgumentIsNotNull(variable)
#define eosArgumentIsNotZero(variable)
#define eosAssert(condition)

#endif


#if defined(EOS_DEBUG)
extern void eosErrorHandler(const char *file, unsigned line, const char *message);
#endif


#endif

