#ifndef __EOS_ASSERT_HPP
#define	__EOS_ASSERT_HPP


#include "eos.hpp"


#if defined(EOS_DEBUG)

#define eosArgumentIsNotNull(name, variable) \
    if (variable == nullptr) eosErrorHandler(__FILE__, __LINE__, name)

#define eosArgumentIsNotZero(name, variable) \
    if (variable == 0) eosErrorHandler(__FILE__, __LINE__, name)

#define eosAssert(condition) \
    if (!(condition)) eosErrorHandler(__FILE__, __LINE__, #condition)

#else

#define eosArgumentIsNotNull(name, variable)
#define eosArgumentIsNotZero(name, variable)
#define eosAssert(condition)

#endif


#if defined(EOS_DEBUG)
extern void eosErrorHandler(const char *file, unsigned line, const char *message);
#endif


#endif	

