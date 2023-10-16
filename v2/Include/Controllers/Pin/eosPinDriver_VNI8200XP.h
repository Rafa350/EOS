#pragma once
#ifndef __eosDriver_VNI8200XP__
#define __eosDriver_VNI8200XP__


#include "eos.h"
#include "Controllers/Pin/eosPinDriver.h"
#include "HTL/htlGPIO.h"
#include "HTL/htlSPI.h"


namespace eos {
    
	/// \brief Clase que implementa del driver del chip VNI8200XP
	///
    class VNI8200XP_Device {
		public:
			enum class State {
				reset,
				ready,
				updating
			};
			enum class Result {
				ok,
				error
			};
        public:
    		virtual ~VNI8200XP_Device() = default;
            virtual void set(uint8_t pinMask) = 0;
            virtual void clear(uint8_t pinMask) = 0;
            virtual void toggle(uint8_t pinMask) = 0;
			virtual void write(uint8_t pinMask, bool pinState) = 0;
			virtual uint8_t read() const = 0;
			virtual void enable() const = 0;
			virtual void disable() const = 0;
            virtual void update() = 0;
    };

    typedef VNI8200XP_Device *VNI8200XP_DeviceHandler;

	/// \brief Clase que implementa del driver del chip VNI8200XP
    ///        amb interficie SPI
	///
    class VNI8200XP_SerialDevice: public VNI8200XP_Device {
    	private:
    		State _state;
    		uint8_t _curPinState;
            uint8_t _oldPinState;
    		htl::spi::SPIDeviceHandler _hSPI;
    		htl::gpio::PinHandler _hPinSS;
    		htl::gpio::PinHandler _hPinOUTEN;
    	protected:
    		VNI8200XP_SerialDevice();
    	public:
            Result initialize(htl::spi::SPIDeviceHandler hSPI, htl::gpio::PinHandler hPinSS, htl::gpio::PinHandler hPinOUTEN = nullptr);
        	void set(uint8_t pinMask) override;
			void clear(uint8_t pinMask) override;
			void toggle(uint8_t pinMask) override;
			void write(uint8_t pinMask, bool pinState) override;
			uint8_t read() const override;
			void enable() const override;
			void disable() const override;
            void update() override;
    };
    
    template <uint8_t id_>
    class VNI8200XP_SerialDeviceX final: public VNI8200XP_SerialDevice {
        private:
            static VNI8200XP_SerialDeviceX _instance;
        public:
            static constexpr uint8_t id = id_;
        private:
            VNI8200XP_SerialDeviceX():
            	VNI8200XP_SerialDevice() {
            }
            VNI8200XP_SerialDeviceX(const VNI8200XP_SerialDeviceX&) = delete;
            VNI8200XP_SerialDeviceX operator = (const VNI8200XP_SerialDeviceX&) = delete;
        public:
			static constexpr VNI8200XP_SerialDeviceX * getHandler() {
				return &_instance;
			}
    };
    template <uint8_t id_>
	VNI8200XP_SerialDeviceX<id_> VNI8200XP_SerialDeviceX<id_>::_instance;
    
    
    /// \brief Clase que implementa del driver del pin amb el chip VNI8200XP
    ///
    class PinDriver_VNI8200XP final: public PinDriver {
		private:
			VNI8200XP_DeviceHandler const _hDevice;
			uint8_t const _pinMask;
		public:
			PinDriver_VNI8200XP(VNI8200XP_DeviceHandler hDevice, uint8_t pinNumber);
			void set() override;
			void clear() override;
			void toggle() override;
			void write(bool pinState) override;
			bool read() override;
    };
}


#endif // __eosDriver_VNI8200XP__
