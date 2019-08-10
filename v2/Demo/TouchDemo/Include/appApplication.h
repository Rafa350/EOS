#ifndef __appApplication__
#define __appApplication__


// EOS includes
//
#include "eos.h"
#include "System/eosApplication.h"


namespace eos {

	class GuiTouchPadService;
	struct TouchPadEventArgs;
}


namespace app {

	class LedService;
	class DisplayService;
	class TouchService;

	class MyApplication: public eos::Application {
		private:
			LedService *ledService;
			DisplayService *displayService;
			eos::GuiTouchPadService *touchPadService;

		public :
			MyApplication();

		private:
			void touchPadNotification(eos::TouchPadEventArgs *args);
	};

}


#endif // __appApplication__
