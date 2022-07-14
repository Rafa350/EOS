#ifndef __appLedService__
#define __appLedService__


// EOS includes
//
#include "eos.h"
#include "Services/eosAppLoopService.h"
#include "HTL/htlGPIO.h"


namespace app {

	class LedService: public eos::AppLoopService {
		private:
			#ifdef EXIST_LEDS_LED1
				typedef LEDS_LED1_TYPE GPIO_LED1;
			#endif
			#ifdef EXIST_LEDS_LED2
				typedef LEDS_LED2_TYPE GPIO_LED2;
			#endif

		public:
			LedService(eos::Application *application);

		protected:
			void onSetup();
			void onLoop();
	};

}


#endif // __appLedService__
