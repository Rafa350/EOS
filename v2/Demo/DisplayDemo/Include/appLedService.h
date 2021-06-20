#ifndef __appLedService__
#define __appLedService__


// EOS includes
//
#include "eos.h"
#include "Services/eosAppLoopService.h"
#include "HAL/halGPIOTpl.h"


namespace eos {

	class Application;
}


namespace app {

	class LedService: public eos::AppLoopService {
		private:
#ifdef EXIST_LEDS_LED1
			eos::GPIOPinAdapter<LEDS_LED1_PORT, LEDS_LED1_PIN> led1;
#endif
#ifdef EXIST_LEDS_LED2
			eos::GPIOPinAdapter<LEDS_LED2_PORT, LEDS_LED2_PIN> led2;
#endif

		public:
			LedService(eos::Application *application);

		protected:
			void onSetup();
			void onLoop();
	};

}


#endif // __appLedService__
