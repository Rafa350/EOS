#ifndef __appApplication__
#define __appApplication__


// EOS includes
//
#include "eos.h"
#include "System/eosRTOSApplication.h"


namespace app {

	class MyApplication: public eos::RTOSApplication {
		protected:
			void onExecute() override;
		public :
			MyApplication();
	};

}


#endif
