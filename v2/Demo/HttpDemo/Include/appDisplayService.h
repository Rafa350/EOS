#ifndef __appDisplayService__
#define __appDisplayService__


/// EOS includes
//
#include "eos.h"
#include "Services/eosAppLoopService.h"


namespace eos {

	class Application;
	class IDisplayDriver;
	class Graphics;
}


namespace app {

	class DisplayService: public eos::AppLoopService {
		private:
			eos::IDisplayDriver *_driver;
			eos::Graphics *_graphics;

		public:
			DisplayService(eos::Application *application);

		protected:
			void onSetup();
			void onLoop();
	};

}

#endif // __appDisplayService__
