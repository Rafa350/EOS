#ifndef __appLedService__
#define __appLedService__


// EOS includes
//
#include "eos.h"
#include "Services/eosAppLoopService.h"
#include "HAL/halGPIO.h"


namespace app {

	class LedService: public eos::AppLoopService {
		private:
#ifdef EXIST_LEDS_LED1
			eos::GPIOPinAdapter<LED_LED1_PORT, LED_LED1_PIN> led1;
#endif
#ifdef EXIST_LEDS_LED2
			eos::GPIOPinAdapter<LED_LED2_PORT, LED_LED2_PIN> led2;
#endif

		public:
			LedService(eos::Application *pApplication);

		protected:
			void onSetup();
			void onLoop();
	};

}


#endif // __appLedService__
