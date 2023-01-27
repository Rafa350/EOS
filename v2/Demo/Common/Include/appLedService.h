#pragma once
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
			#ifdef EXIST_LED1
				using PinLED1 = LED1_GPIO;
			#endif
			#ifdef EXIST_LED2
				using PinLED2 = LED2_GPIO;
			#endif

			static constexpr htl::GPIOState _ledON = LED1_ON;
			static constexpr htl::GPIOState _ledOFF = LED1_OFF;

		public:
			LedService();

		protected:
			void onSetup();
			void onLoop();
	};

}


#endif // __appLedService__
