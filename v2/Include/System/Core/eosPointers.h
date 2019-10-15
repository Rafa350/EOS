#ifndef __eosPointers__
#define __eosPointers__


#include "eos.h"


namespace eos {

	template <class T>
	class SharedPtr {
		private:
			T* ptr;
			int* ptrRefCount;
	};

}


#endif // __eosPointers__
