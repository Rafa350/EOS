#pragma once
#ifndef __eosPinDriver_ISO808__
#define	__eosPinDriver_ISO808__


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
			htl::gpio::PinHandler const _hPinSYNC;
			htl::gpio::PinHandler const _hPinLOAD;
			htl::gpio::PinHandler const _hPinIN1;
			htl::gpio::PinHandler const _hPinIN2;
			htl::gpio::PinHandler const _hPinIN3;
			htl::gpio::PinHandler const _hPinIN4;
			htl::gpio::PinHandler const _hPinIN5;
			htl::gpio::PinHandler const _hPinIN6;
			htl::gpio::PinHandler const _hPinIN7;
			htl::gpio::PinHandler const _hPinIN8;
			htl::gpio::PinHandler const _hPinOUTEN;
			htl::gpio::PinHandler const _hPinFAULT;
        protected:
            ISO808_Device(htl::gpio::PinHandler const _hPinSYNC, htl::gpio::PinHandler const _hPinLOAD,
                htl::gpio::PinHandler _hPinIN1, htl::gpio::PinHandler _hPinIN2, htl::gpio::PinHandler _hPinIN3,
				htl::gpio::PinHandler _hPinIN4, htl::gpio::PinHandler _hPinIN5, htl::gpio::PinHandler _hPinIN6,
				htl::gpio::PinHandler _hPinIN7, htl::gpio::PinHandler _hPinIN8, htl::gpio::PinHandler _hPinOUTEN,
                htl::gpio::PinHandler _hPinFAULT);
		public:
			void initialize();
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
                _hPinOUTEN->set();
            }
			inline void disable() const {
                _hPinOUTEN->clear();
                
            }
            void update();
            bool isOK();
	};


	typedef ISO808_Device *ISO808_DeviceHandler;


    template <typename PinSYNC_, typename PinLOAD_,
              typename PinIN1_, typename PinIN2_, typename PinIN3_, typename PinIN4_, 
              typename PinIN5_, typename PinIN6_, typename PinIN7_, typename PinIN8_,
              typename PinOUTEN_, typename PinFAULT_>
	class ISO808_DeviceX final: public ISO808_Device {
		private:
			static ISO808_DeviceX _instance;
            
        private:
			ISO808_DeviceX():
                ISO808_Device(PinSYNC_::getHandler(), PinLOAD_::getHandler(),
                PinIN1_::getHandler(), PinIN2_::getHandler(), PinIN3_::getHandler(), PinIN4_::getHandler(),
                PinIN5_::getHandler(), PinIN6_::getHandler(), PinIN7_::getHandler(), PinIN8_::getHandler(),
                PinOUTEN_::getHandler(), PinFAULT_::getHandler()) {
			}
            ISO808_DeviceX(const ISO808_DeviceX&) = delete;
			ISO808_DeviceX & operator = (const ISO808_DeviceX&) = delete;

		public:
			static constexpr ISO808_DeviceX * getHandler() {
				return &_instance;
			}
			
	};
    
    template <typename PinSYNC_, typename PinLOAD_,
              typename PinIN1_, typename PinIN2_, typename PinIN3_, typename PinIN4_,
              typename PinIN5_, typename PinIN6_, typename PinIN7_, typename PinIN8_,
              typename PinOUTEN_, typename PinFAULT_>
    ISO808_DeviceX<PinSYNC_, PinLOAD_,
        PinIN1_, PinIN2_, PinIN3_, PinIN4_,
        PinIN5_, PinIN6_, PinIN7_, PinIN8_,
        PinOUTEN_, PinFAULT_>
    ISO808_DeviceX<PinSYNC_, PinLOAD_,
        PinIN1_, PinIN2_, PinIN3_, PinIN4_,
        PinIN5_, PinIN6_, PinIN7_, PinIN8_,
        PinOUTEN_, PinFAULT_>::_instance;


    class PinDriver_ISO808 final: public PinDriver {
		private:
			ISO808_DeviceHandler const _hDevice;
			uint8_t const _pinMask;
		public:
			PinDriver_ISO808(ISO808_DeviceHandler hDevice, uint8_t pinNumber);
			void set() override;
			void clear() override;
			void toggle() override;
			void write(bool pinState) override;
			bool read() override;
    };

}


#endif // __eosPinDriver_ISO808__
