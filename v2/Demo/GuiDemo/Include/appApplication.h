#ifndef __appApplication__
#define __appApplication__


// EOS includes
//
#include "eos.h"
#include "System/eosApplication.h"


namespace eos {

	class GuiService;
}


namespace app {

	class LedService;

	class MyApplication: public eos::Application {
		private:
			LedService *ledService;
			eos::GuiService *guiService;

		public :
			MyApplication();
	};

}

#endif
