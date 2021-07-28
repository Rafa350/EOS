#ifndef __appDisplayService__
#define __appDisplayService__


// EOS includes
//
#include "eos.h"
#include "Services/eosAppLoopService.h"


namespace eos {

	class Application;
	class IDisplayDriver;
}

namespace app {

	class DisplayService: public eos::AppLoopService {
		private:
			eos::IDisplayDriver* _driver;

		protected:
			void onSetup();
			void onLoop();

		public:
			DisplayService(eos::Application* application);
	};
}


#endif // __appDisplayService__
