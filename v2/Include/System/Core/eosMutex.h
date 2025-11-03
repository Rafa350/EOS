#ifndef __eosMutex__
#define __eosMutex__


// EOS includes
//
#include "eos.h"
#include "OSAL/osalMutex.h"


namespace eos {

	class Mutex {
		private:
			HMutex hMutex;

		public:
			Mutex();
			~Mutex();

			bool wait(unsigned waitTime);
			void release();
	};

}


#endif // __eosMutex__
