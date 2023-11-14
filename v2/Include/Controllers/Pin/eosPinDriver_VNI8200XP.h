#pragma once


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

	/// \brief Clase que implementa del driver del chip VNI8200XP
    ///        amb interficie SPI
	///
    class VNI8200XP_SerialDevice: public VNI8200XP_Device {
    	private:
    		State _state;
    		uint8_t _curPinState;
            uint8_t _oldPinState;
    		htl::spi::SPIDevice *_spi;
    		htl::gpio::Pin *_pinSS;
    		htl::gpio::Pin *_pinOUTEN;
    	protected:
    		VNI8200XP_SerialDevice();
    	public:
            Result initialize(htl::spi::SPIDevice *spi, htl::gpio::Pin *pinSS, htl::gpio::Pin *pinOUTEN = nullptr);
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
            static constexpr VNI8200XP_SerialDeviceX *pInst = &_instance;
            static constexpr VNI8200XP_SerialDeviceX &rInst = _instance;
        private:
            VNI8200XP_SerialDeviceX():
            	VNI8200XP_SerialDevice() {
            }
            VNI8200XP_SerialDeviceX(const VNI8200XP_SerialDeviceX&) = delete;
            VNI8200XP_SerialDeviceX operator = (const VNI8200XP_SerialDeviceX&) = delete;
    };
    template <uint8_t id_>
	VNI8200XP_SerialDeviceX<id_> VNI8200XP_SerialDeviceX<id_>::_instance;
    
    
    /// \brief Clase que implementa del driver del pin amb el chip VNI8200XP
    ///
    class PinDriver_VNI8200XP final: public PinDriver {
		private:
			VNI8200XP_Device * const _dev;
			uint8_t const _pinMask;
		public:
			PinDriver_VNI8200XP(VNI8200XP_Device *dev, uint8_t pinNumber);
			void set() override;
			void clear() override;
			void toggle() override;
			void write(bool pinState) override;
			bool read() override;
    };
}
