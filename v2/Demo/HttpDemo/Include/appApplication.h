#ifndef __appApplication__
#define __appApplication__


// EOS includes
//
#include "eos.h"
#include "System/eosRTOSApplication.h"


namespace eos {

	class HTTPService;
	class LedService;
}


namespace app {

	class LedService;
	class DisplayService;

	class MyApplication: public eos::RTOSApplication {
		private:
            #ifdef EXIST_LED1
			eos::LedService *_ledService;
            #endif
			#ifdef EXIST_DISPLAY
			DisplayService *_displayService;
			#endif
			eos::HTTPService *_httpService;

		public :
			MyApplication();
	};

}


#endif
