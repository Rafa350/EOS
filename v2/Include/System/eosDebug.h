#ifndef __eosDebug__
#define __eosDebug__


#include "eos.h"


#if defined(EOS_DEBUG)


namespace eos {

	class Debug {
		public:
			static void initialize();
			static void print(const char *);
	};
}


#endif


#endif // __eosDebug__
