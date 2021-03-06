#ifndef __appApplication__
#define __appApplication__


// EOS includes
//
#include "eos.h"
#include "System/eosApplication.h"


namespace eos {

	class HTTPService;
}


namespace app {

	class LedService;
	class DisplayService;

	class MyApplication: public eos::Application {
		private:
			LedService* ledService;
#ifdef USE_DISPLAY            
			DisplayService* displayService;
#endif            
			eos::HTTPService* httpService;

		public :
			MyApplication();
	};

}


#endif
