#pragma once
#ifndef __eosDevice_CLT0138SQ7__
#define __eosDevice_CLT0138SQ7__


#include "eos.h"
#include "HTL/htlGPIO.h"
#include "HTL/htlSPI.h"
#include "System/eosResults.h"


namespace eos {

	class Device_CLT0138SQ7 final {
		public:
	        using Pin = htl::gpio::PinDevice;
	        using DevSPI = htl::spi::SPIDevice;
			enum class State {
				reset,
				ready
			};
			struct CreateParams {
			    Pin *pinSS;
			    DevSPI *devSPI;
			};

        private:
			Device_CLT0138SQ7(const Device_CLT0138SQ7&) = delete;
			Device_CLT0138SQ7 & operator = (const Device_CLT0138SQ7&) = delete;

		protected:
			State _state;
			uint8_t _pinState;
			bool _underVoltage;
			bool _overTemperature;
			DevSPI *_devSPI;
			const Pin * const _pinSS;

		public:
            Device_CLT0138SQ7(DevSPI *devSPI, Pin *pinSS);
            Device_CLT0138SQ7(const CreateParams *params);

            Result initialize();
            void deinitialize();

            inline uint8_t read() const { return _pinState; }
            Result update();
            inline bool isUnderVoltage() const { return _underVoltage; }
            inline bool isOverTemperature() const { return _overTemperature; }

            inline State getState() const { return _state; }
            inline bool isReady() const { return _state == State::ready; }
	};
}


#endif // __eosDevice_CLT0138SQ7__
