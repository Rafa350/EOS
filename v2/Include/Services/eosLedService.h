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

	    private:
	        Pin * const _pinLED1;
	        Pin * const _pinLED2;

		public:
			static constexpr uint32_t stackSize = 128;
			static constexpr const char *serviceName = "LED";

		public:
			LedService(Pin *pinLED1, Pin *pinLED2 = nullptr);

		protected:
            bool onTaskStart() override;
			bool onTask() override;
	};

}


#endif // __eosLedService__
