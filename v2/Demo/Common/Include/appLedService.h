#pragma once
#ifndef __appLedService__
#define __appLedService__


// EOS includes
//
#include "eos.h"
#include "Services/eosService.h"
#include "HTL/htlGPIO.h"


namespace app {

	class LedService: public eos::Service {
		public:
			static constexpr uint32_t stackSize = 128;
			static constexpr const char *serviceName = "LED";

		private:
			#ifdef EXIST_LED1
				using PinLED1 = LED1_GPIO;
			#endif
			#ifdef EXIST_LED2
				using PinLED2 = LED2_GPIO;
			#endif

			static constexpr htl::GPIOPinState _ledON = LED1_ON;
			static constexpr htl::GPIOPinState _ledOFF = LED1_OFF;

		public:
			LedService();

		protected:
			void onInitialize() override;
			void onTask() override;
	};

}


#endif // __appLedService__
