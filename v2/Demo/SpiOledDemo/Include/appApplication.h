#pragma once
#ifndef __appApplication__
#define __appApplication__


// EOS includes
//
#include "eos.h"
#include "System/eosRTOSApplication.h"


namespace app {

	class MyApplication: public eos::RTOSApplication {
		public :
			MyApplication();
	};

}


#endif // __appApplication__
