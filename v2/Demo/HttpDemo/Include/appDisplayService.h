#ifndef __appDisplayService__
#define __appDisplayService__


/// EOS includes
//
#include "eos.h"
#include "Services/eosAppLoop.h"


namespace app {

    using namespace eos;

    class Application;
	class IDisplayDriver;
	class Display;

	class DisplayService: public AppLoopService {
		private:
			IDisplayDriver *driver;
			Display *display;

		public:
			DisplayService(Application *application);

		protected:
			void onSetup();
			void onLoop();
	};

}

#endif // __appDisplayService__
