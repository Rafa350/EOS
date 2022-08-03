#ifndef __appApplication__
#define __appApplication__


// EOS includes
//
#include "eos.h"
#include "System/eosApplication.h"


namespace app {

	class LedService;
	class DisplayService;

	class MyApplication: public eos::Application {
		private:
			LedService *_ledService;
			DisplayService *_displayService;

		public :
			MyApplication();
	};

}

#endif
