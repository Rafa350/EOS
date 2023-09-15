#pragma once
#ifndef __appApplication__
#define __appApplication__


// EOS includes
//
#include "eos.h"
#include "System/eosRTOSApplication.h"


namespace app {

	class LedService;
	class DisplayService;

	class MyApplication: public eos::RTOSApplication {
		private:
			LedService *_ledService;
			DisplayService *_displayService;

		public :
			MyApplication();
	};

}


#endif // __appApplication__
