#pragma once
#ifndef __eosPinDriver_CLT0138SQ7__
#define __eosPinDriver_CLT0138SQ7__


#include "eos.h"
#include "Controllers/Pin/eosPinDriver.h"
#include "HTL/htlGPIO.h"
#include "HTL/htlSPI.h"


namespace eos {

	class CLT0138SQ7_Device {
		public:
			enum class State {
				reset,
				ready
			};
			enum class Result {
				ok,
				error
			};
		protected:
			State _state;
			uint8_t _pinState;
			bool _underVoltage;
			bool _overTemperature;
			htl::spi::SPIDeviceHandler _hSPI;
			htl::gpio::PinHandler _hPinSS;
		protected:
			CLT0138SQ7_Device();
		public:
            Result initialize(htl::spi::SPIDeviceHandler hSPI, htl::gpio::PinHandler hPinSS);
			inline uint8_t read() const { return _pinState; }
            void update();
            inline bool isUnderVoltage() const { return _underVoltage; }
            inline bool isOverTemperature() const { return _overTemperature; }
            
	};

	typedef CLT0138SQ7_Device *CLT0138SQ7_DeviceHandler;

	template <uint8_t id_>
	class CLT0138SQ7_DeviceX final: public CLT0138SQ7_Device {
		private:
			static CLT0138SQ7_DeviceX _instance;
		private:
			CLT0138SQ7_DeviceX():
				CLT0138SQ7_Device() {
			}
			CLT0138SQ7_DeviceX(const CLT0138SQ7_DeviceX&) = delete;
			CLT0138SQ7_DeviceX operator = (const CLT0138SQ7_DeviceX&) = delete;
		public:
			static constexpr CLT0138SQ7_DeviceX * getHandler() {
				return &_instance;
			}
	};
    template <uint8_t id_>
    CLT0138SQ7_DeviceX<id_> CLT0138SQ7_DeviceX<id_>::_instance;


    class PinDriver_CLT0138SQ7 final: public PinDriver {
    	private:
    		CLT0138SQ7_DeviceHandler const _hDevice;
    		uint8_t const _pinMask;
    	public:
    		PinDriver_CLT0138SQ7(CLT0138SQ7_DeviceHandler hDevice, uint8_t pinNumber);
            void set() override;
            void clear() override;
            void toggle() override;
            void write(bool state) override;
            bool read() override;
    };
}


#endif // __eosPinDriver_CLT0138SQ7__
