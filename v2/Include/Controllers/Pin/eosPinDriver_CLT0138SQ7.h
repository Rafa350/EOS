#pragma once
#ifndef __eosPinDriver_CLT0138SQ7__
#define __eosPinDriver_CLT0138SQ7__


#include "eos.h"
#include "Controllers/Pin/eosPinDriver.h"
#include "HTL/htlGPIO.h"
#include "HTL/htlSPI.h"


namespace eos {

	class CLT0138SQ7_Device {
		protected:
			htl::spi::SPIDeviceHandler const _hSPI;
			htl::gpio::PinHandler const _hSS;
		protected:
			CLT0138SQ7_Device(htl::spi::SPIDeviceHandler hSPI, htl::gpio::PinHandler hSS);
		public:
            void initialize();
			uint8_t read();
            void update();
            
	};

	typedef CLT0138SQ7_Device *CLT0138SQ7_DeviceHandlewr;

	template <typename SPIDevice_, typename PinSS_>
	class CLT0138SQ7_DeviceX final: public CLT0138SQ7_Device {
		private:
			static CLT0138SQ7_DeviceX _instance;
		private:
			CLT0138SQ7_DeviceX():
				CLT0138SQ7_DeviceX(SPIDevice_::getHandler(), PinSS_::getHandler()) {
			}
			CLT0138SQ7_DeviceX(const CLT0138SQ7_DeviceX&) = delete;
			CLT0138SQ7_DeviceX operator = (const CLT0138SQ7_DeviceX&) = delete;
		public:
			static constexpr CLT0138SQ7_DeviceX * getHandler() {
				return &_instance;
			}
	};
    template <typename SPIDevice_, typename PinSS_>
    CLT0138SQ7_DeviceX<SPIDevice_, PinSS_> CLT0138SQ7_DeviceX<SPIDevice_, PinSS_>::_instance;
}


#endif // __eosPinDriver_CLT0138SQ7__
