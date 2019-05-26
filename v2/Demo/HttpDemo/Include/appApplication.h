#ifndef __appApplication__
#define __appApplication__


// EOS includes
//
#include "eos.h"
#include "System/eosApplication.h"


namespace app {

	using namespace eos;

	class LedLoopService;
	class DisplayService;

	class MyApplication: public Application {
		private:
			LedLoopService *ledService;
			DisplayService *displayService;

		public :
			MyApplication();
	};

}

#endif
