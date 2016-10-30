#ifndef __EOS_ASSERT_HPP
#define	__EOS_ASSERT_HPP


#if defined(__DEBUG)
#define eosArgumentIsNotNull(name, variable) if (variable == nullptr) eosErrorHandler(__FILE__, __LINE__, name)
#define eosArgumentIsNotZero(name, variable) if (variable == 0) eosErrorHandler(__FILE__, __LINE__, name)
#else
#define eosArgumentIsNotNull(name, variable)
#define eosArgumentIsNotZero(name, variable)
#endif

#if defined(__DEBUG)
#define eosAssert(condition, message) \
    if (!(condition)) eosErrorHandler(__FILE__, __LINE__, message);
#else
#define eosAssert(condition, message)
#endif

#if defined(__DEBUG)
extern void eosErrorHandler(const char *file, unsigned line, const char *message);
#endif


#endif	

