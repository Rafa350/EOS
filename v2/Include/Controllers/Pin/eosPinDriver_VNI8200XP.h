#pragma once
#ifndef __eosDriver_VNI8200XP__
#define __eosDriver_VNI8200XP__


#include "eos.h"
#include "Controllers/Pin/eosPinDriver.h"
#include "HTL/htlGPIO.h"
#include "HTL/htlSPI.h"


namespace eos {
    
    class VNI8200XP_Device {
        public:
    		virtual ~VNI8200XP_Device() = default;
            virtual void initialize() = 0;
            virtual void set(uint8_t pinMask) = 0;
            virtual void clear(uint8_t pinMask) = 0;
            virtual void toggle(uint8_t pinMask) = 0;
			virtual void write(uint8_t pinMask, bool pinState) = 0;
			virtual bool read(uint8_t pinMask) = 0;
			virtual void enable() = 0;
			virtual void disable() = 0;
            virtual void update() = 0;
            virtual bool isOK() = 0;
    };

    typedef VNI8200XP_Device *VNI8200XP_DeviceHandler;

    class VNI8200XP_SerialDevice: public VNI8200XP_Device {
    	private:
    		uint8_t _newState;
            uint8_t _oldState
    		htl::spi::SPIDeviceHandler const _hSPI;
    		htl::gpio::PinHandler const _hSS;
    		htl::gpio::PinHandler const _hOUTEN;
    	private:
    		uint8_t calcParity(uint8_t data);
    		uint8_t transmit(uint8_t data);
    	protected:
    		VNI8200XP_SerialDevice(htl::spi::SPIDeviceHandler hSPI,  htl::gpio::PinHandler hSS, htl::gpio::PinHandler hOUTEN);
    	public:
            void initialize() override;
        	void set(uint8_t pinMask) override;
			void clear(uint8_t pinMask) override;
			void toggle(uint8_t pinMask) override;
			void write(uint8_t pinMask, bool pinState) override;
			bool read(uint8_t pinMask) override;
			void enable() override;
			void disable() override;
            void update() override;
            bool isOK() override;
    };
    
    template <typename SPIDevice_, typename PinSS_, typename PinOUTEN_>
    class VNI8200XP_SerialDeviceX final: public VNI8200XP_SerialDevice {
        private:
            static VNI8200XP_SerialDeviceX _instance;
        private:
            VNI8200XP_SerialDeviceX():
            	VNI8200XP_SerialDevice( SPIDevice_::getHandler(), PinSS_::getHandler(), PinOUTEN_::getHandler()) {
            }
            VNI8200XP_SerialDeviceX(const VNI8200XP_SerialDeviceX&) = delete;
            VNI8200XP_SerialDeviceX operator = (const VNI8200XP_SerialDeviceX&) = delete;
        public:
			static constexpr VNI8200XP_SerialDeviceX * getHandler() {
				return &_instance;
			}
    };
    template <typename SPIDevice_, typename PinSS_, typename PinOUTEN_>
	VNI8200XP_SerialDeviceX<SPIDevice_, PinSS_, PinOUTEN_> VNI8200XP_SerialDeviceX<SPIDevice_, PinSS_, PinOUTEN_>::_instance;
    
    
    class PinDriver_VNI8200XP final: public PinDriver {
		private:
			VNI8200XP_DeviceHandler const _hDevice;
			uint8_t const _pinNumber;
		public:
			PinDriver_VNI8200XP(VNI8200XP_DeviceHandler hDevice, uint8_t pinNumber);
			void set() override;
			void clear() override;
			void toggle() override;
			void write(bool pinState) override;
			bool read() const override;
    };
}


#endif // __eosDriver_VNI8200XP__
