#pragma once


// EOS includes
//
#include "eos.h"
#include "Controllers/Pin/eosPinDriver.h"
#include "HTL/htlGPIO.h"


namespace eos {

	class ISO808_Device {
        private:
            uint8_t _oldState;
			uint8_t _newState;
			htl::gpio::Pin *_pinSYNC;
			htl::gpio::Pin *_pinLOAD;
			htl::gpio::Pin *_pinIN1;
			htl::gpio::Pin *_pinIN2;
			htl::gpio::Pin *_pinIN3;
			htl::gpio::Pin *_pinIN4;
			htl::gpio::Pin *_pinIN5;
			htl::gpio::Pin *_pinIN6;
			htl::gpio::Pin *_pinIN7;
			htl::gpio::Pin *_pinIN8;
			htl::gpio::Pin *_pinOUTEN;
			htl::gpio::Pin *_pinFAULT;

        protected:
            ISO808_Device();

		public:
			void initialize(htl::gpio::Pin *pinSYNC, htl::gpio::Pin *pinLOAD,
	                htl::gpio::Pin *pinIN1, htl::gpio::Pin *pinIN2, htl::gpio::Pin *pinIN3,
	                htl::gpio::Pin *pinIN4, htl::gpio::Pin *pinIN5, htl::gpio::Pin *pinIN6,
	                htl::gpio::Pin *pinIN7, htl::gpio::Pin *pinIN8, htl::gpio::Pin *pinOUTEN,
	                htl::gpio::Pin *pinFAULT);
            inline void set(uint8_t pinMask) {
                _newState |= pinMask;
            }
            inline void clear(uint8_t pinMask) {
                _newState &= ~pinMask;
            }
            inline void toggle(uint8_t pinMask) {
                _newState ^= pinMask;
            }
            inline void write(uint8_t pinMask) {
            	_newState = pinMask;
            }
            inline uint8_t read() const {
            	return _newState;
            }
			inline void enable() const {
                _pinOUTEN->set();
            }
			inline void disable() const {
                _pinOUTEN->clear();
                
            }
            void update();
            bool isOK();
	};


    template <uint8_t id_>
	class ISO808_DeviceX final: public ISO808_Device {
		private:
			static ISO808_DeviceX _instance;

		public:
			static constexpr ISO808_DeviceX *pInst = &_instance;
			static constexpr ISO808_DeviceX &rInst = _instance;

        private:
            ISO808_DeviceX(const ISO808_DeviceX&) = delete;
			ISO808_DeviceX & operator = (const ISO808_DeviceX&) = delete;
	};
    
    template <uint8_t id_>
    ISO808_DeviceX<id_> ISO808_DeviceX<id_>::_instance;


    class PinDriver_ISO808 final: public PinDriver {
		private:
			ISO808_Device * const _dev;
			uint8_t const _pinMask;

		public:
			PinDriver_ISO808(ISO808_Device *dev, uint8_t pinNumber);
			void set() override;
			void clear() override;
			void toggle() override;
			void write(bool pinState) override;
			bool read() override;
    };

}
