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
				slowBlink,
				mediumBlink,
				fastBlink,
				flash1,
				flash2,
				flash3,
				flash4
	        };

	    private:
	        static constexpr const char *_serviceName = "Led";
	        static constexpr uint32_t _serviceStackDepth = 96;
	        static constexpr rtos::Task::Priority _servicePriority = rtos::Task::Priority::low;

	        static constexpr Time _stepInterval  = Time::fromMiliseconds(150);
	        static constexpr Time _slowBlinkInterval = Time::fromMiliseconds(1000);
	        static constexpr Time _mediumBlinkInterval = Time::fromMiliseconds(500);
	        static constexpr Time _fastBlinkInterval = Time::fromMiliseconds(250);

	        static constexpr uint16_t _flash1Pattern    = 0b0000000001001111;
	        static constexpr uint16_t _flash2Pattern    = 0b0000000101001111;
	        static constexpr uint16_t _flash3Pattern    = 0b0000010101001111;
	        static constexpr uint16_t _flash4Pattern    = 0b0001010101001111;

	    private:
	        Pin * const _pinLED;
	        LedMode _mode;
	        uint8_t _step;

		protected:
			void onInitialize(ServiceParams &params) override;
			void onExecute() override;

		public:
			LedService(Pin *pinLED);

			void setLedMode(LedMode value);
	};

}


#endif // __eosLedService__
