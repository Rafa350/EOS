#pragma once
#ifndef __eosLedService__
#define __eosLedService__


// EOS includes
//
#include "eos.h"
#include "HTL/htlGPIO.h"
#include "Services/eosService.h"


namespace eos {

	class LedService: public Service {
	    public:
	        using Pin = htl::gpio::PinDevice;

	        enum class LedMode {
	        	on,
				off,
				blinkSlow,
				blinkFast,
				flash1,
				flass2,
				flash3,
				flash4
	        };

	    private:
	        Pin * const _pinLED1;
	        Pin * const _pinLED2;
	        LedMode _modeLED1;
	        LedMode _modeLED2;

		protected:
			void onInitialize(ServiceParams &params) override;
			void onExecute() override;

		public:
			LedService(Pin *pinLED1, Pin *pinLED2 = nullptr);

			void setLed1Mode(LedMode value);
			void setLed2Mode(LedMode value);
	};

}


#endif // __eosLedService__
