#pragma once
#ifndef __eosDevice_CLT0138SQ7__
#define __eosDevice_CLT0138SQ7__


#include "eos.h"
#include "HTL/htlGPIO.h"
#include "HTL/htlSPI.h"


namespace eos {

	class Device_CLT0138SQ7 {
		public:
	        using Pin = htl::gpio::Pin;
	        using DevSPI = htl::spi::SPIDevice;
			enum class State {
				reset,
				ready
			};
			enum class Result {
				ok,
				error
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
			Pin const * _pinSS;
            
		protected:
			Device_CLT0138SQ7();
            
		public:
            Result initialize(DevSPI *devSPI, Pin *pinSS);
			
            inline uint8_t read() const { return _pinState; }
            void update();
            inline bool isUnderVoltage() const { return _underVoltage; }
            inline bool isOverTemperature() const { return _overTemperature; }
            
	};

	template <uint8_t id_>
	class DeviceX_CLT0138SQ7 final: public Device_CLT0138SQ7 {
		private:
			static DeviceX_CLT0138SQ7 _instance;
            
		public:
			static constexpr DeviceX_CLT0138SQ7 *pInst = &_instance;
            static constexpr DeviceX_CLT0138SQ7 &rInst = _instance;
            
		private:
			DeviceX_CLT0138SQ7():
				Device_CLT0138SQ7() {
			}
	};
    
    template <uint8_t id_>
    DeviceX_CLT0138SQ7<id_> DeviceX_CLT0138SQ7<id_>::_instance;
}


#endif // __eosDevice_CLT0138SQ7__
