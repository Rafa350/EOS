#ifndef __appLedService__
#define __appLedService__


// EOS includes
//
#include "eos.h"
#include "Services/eosAppLoopService.h"
#include "HTL/htlGPIO.h"


namespace eos {

	class Application;
}


namespace app {

	class LedService: public eos::AppLoopService {
		private:
			#ifdef EXIST_LED1
				using GPIO_LED1 = board::led1::GPIO_LED;
			#endif
			#ifdef EXIST_LED2
				using GPIO_LED2 = board::led2::GPIO_LED;
			#endif

		public:
			LedService(eos::Application *application);

		protected:
			void onSetup();
			void onLoop();
	};

}


#endif // __appLedService__
