#pragma once
#ifndef __eosDriver_VNI8200XP__
#define __eosDriver_VNI8200XP__


#include "eos.h"
#include "Controllers/Pin/eosPinDriver.h"
#include "HTL/htlGPIO.h"
#include "HTL/htlSPI.h"


namespace eos {
    
    class VNI8200XPDevice {
        public:
    		virtual ~VNI8200XPDevice() = default;
            virtual void set(uint8_t pinMask) = 0;
            virtual void clear(uint8_t pinMask) = 0;
            virtual void toggle(uint8_t pinMask) = 0;
			virtual void write(uint8_t pinMask, bool pinState) = 0;
			virtual bool read(uint8_t pinMask) = 0;
    };

    typedef VNI8200XPDevice *VNI8200XPDeviceHandler;

    
    template <typename SPIDevice_, typename PinSS_, typename PinOUTEN_>
    class VNI8200XPSerialDevice final: public VNI8200XPDevice {
        private:
    		constexpr htl::spi::SPIDeviceHandler _hSPI = SPIDevice::getHandler();
            constexpr htl::gpio::PinHandler _hSS = PinSS_::getHandler();
            constexpr htl::gpio::PinHandler _hOUTEN = PinOUTEN_::getHandler();

        private:
            static VNI8200XPSerialDevice _instance;
        
        private:
            VNI8200XPSerialDevice() = default;
            VNI8200XPSerialDevice(const VNI8200XPSerialDevice&) = delete;
            VNI8200XPSerialDevice operator = (const VNI8200XPSerialDevice&) = delete;

        public:
			static constexpr VNI8200XPSerialDevice * getHandler() {
				return &_instance;
			}
            void set(uint8_t pinState) override;
            void clear(uint8_t pinState) override;
            void toggle(uint8_t pinState) override;
    };
    template <typename SPIDevice_, typename PinSS_, typename PinOUTEN_>
	VNI8200XPSerialDevice<SPIDevice_, PinSS_, PinOUTEN> VNI8200XPSerialDevice<SPIDevice_, PinSS_, PinOUTEN_>::_instance;
    

    template <typename PinIN1_, typename PinIN2_, typename PinIN3_, typename PinIN4_,
              typename PinIN5_, typename PinIN6_, typename PinIN7_, typename PinIN8_>
    class VNI8200XPParalelDevice final: public VNI8200XPDevice {
        private:
			constexpr htl::gpio::PinHandler _hIN1 = PinIN1_::getHandler();
			constexpr htl::gpio::PinHandler _hIN2 = PinIN2_::getHandler();
			constexpr htl::gpio::PinHandler _hIN3 = PinIN3_::getHandler();
			constexpr htl::gpio::PinHandler _hIN4 = PinIN4_::getHandler();
			constexpr htl::gpio::PinHandler _hIN5 = PinIN5_::getHandler();
			constexpr htl::gpio::PinHandler _hIN6 = PinIN6_::getHandler();
			constexpr htl::gpio::PinHandler _hIN7 = PinIN7_::getHandler();
			constexpr htl::gpio::PinHandler _hIN8 = PinIN8_::getHandler();

        private:
            static VNI8200XPParalelDevice _instance;

        private:
            VNI8200XPParalelDevice() = default;
            VNI8200XPParalelDevice(const VNI8200XPParalelDevice&) = delete;
            VNI8200XPParalelDevice operator = (const VNI8200XPParalelDevice&) = delete;

        public:
			static constexpr VNI8200XPParalelDevice * getHandler() {
				return &_instance;
			}
            void set(uint8_t pinMask) override;
            void clear(uint8_t pinMask) override;
            void toggle(uint8_t pinMask) override;
    };
    
    
    class PinDriver_VNI8200XP final: public PinDriver {
		private:
			VNI8200XPDeviceHandler _hDevice;
			uint8_t _pinNumber;
		public:
			PinDriver_VNI8200XP(VNI8200XPDeviceHandler hDevice, uint8_t pinNumber);
			void set() override;
			void clear() override;
			void toggle() override;
			void write(bool state) override;
			bool read() const override;
    };
}


#endif // __eosDriver_VNI8200XP__
