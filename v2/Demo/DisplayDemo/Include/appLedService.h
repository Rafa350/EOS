#ifndef __appLedService__
#define __appLedService__


// EOS includes
//
#include "eos.h"
#include "Services/eosAppLoopService.h"
#include "HAL2/halGPIO.h"


namespace eos {

	class Application;
}


namespace app {

	class LedService: public eos::AppLoopService {
		private:
#ifdef EXIST_LEDS_LED1
			eos::GPIO _gpioLED1;
#endif
#ifdef EXIST_LEDS_LED2
			eos::GPIO _gpioLED2;
#endif

		public:
			LedService(eos::Application *application);

		protected:
			void onSetup();
			void onLoop();
	};

}


#endif // __appLedService__
