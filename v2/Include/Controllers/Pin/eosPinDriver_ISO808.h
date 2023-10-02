#pragma once
#ifndef __eosPinDriver_ISO808__
#define	__eosPinDriver_ISO808__


// EOS includes
//
#include "eos.h"
#include "Controllers/Pin/eosPinDriver.h"
#include "HTL/htlGPIO.h"


namespace eos {

	class ISO808Device {
		public:
			virtual ~ISO808Device() = default;
			virtual void initialize() = 0;
			virtual void load() = 0;
			virtual void sync() = 0;
			virtual void set(uint8_t pinMask) = 0;
			virtual void clear(uint8_t pinMask) = 0;
			virtual void toggle(uint8_t pinMask) = 0;
			virtual void write(uint8_t pinMask, bool pinState) = 0;
			virtual bool read(uint8_t pinMask) = 0;
	};

	typedef ISO808Device *ISO808DeviceHandler;


    template <typename PinSYNC_, typename PinLOAD_,
              typename PinIN1_, typename PinIN2_, typename PinIN3_, typename PinIN4_, 
              typename PinIN5_, typename PinIN6_, typename PinIN7_, typename PinIN8_,
              typename PinOUTEN_, typename PinFAULT_>
	class ISO808DeviceX final: public ISO808Device {
		private:
			static constexpr htl::gpio::PinHandler _hSYNC = PinSYNC_::getHandler();
			static constexpr htl::gpio::PinHandler _hLOAD = PinLOAD_::getHandler();
			static constexpr htl::gpio::PinHandler _hIN1 = PinIN1_::getHandler();
			static constexpr htl::gpio::PinHandler _hIN2 = PinIN2_::getHandler();
			static constexpr htl::gpio::PinHandler _hIN3 = PinIN3_::getHandler();
			static constexpr htl::gpio::PinHandler _hIN4 = PinIN4_::getHandler();
			static constexpr htl::gpio::PinHandler _hIN5 = PinIN5_::getHandler();
			static constexpr htl::gpio::PinHandler _hIN6 = PinIN6_::getHandler();
			static constexpr htl::gpio::PinHandler _hIN7 = PinIN7_::getHandler();
			static constexpr htl::gpio::PinHandler _hIN8 = PinIN8_::getHandler();
			static constexpr htl::gpio::PinHandler _hOUTEN = PinOUTEN_::getHandler();
			static constexpr htl::gpio::PinHandler _hFAULT = PinFAULT_::getHandler();
			uint8_t _pinState;

		private:
			static ISO808DeviceX _instance;
            
        private:
			ISO808DeviceX():
				_pinState {0} {

			}
            ISO808DeviceX(const ISO808DeviceX&) = delete;
			ISO808DeviceX & operator = (const ISO808DeviceX&) = delete;

		public:
			static constexpr ISO808DeviceX * getHandler() {
				return &_instance;
			}

			void initialize() override {
                _hSYNC->initOutput(htl::gpio::OutDriver::pushPull, htl::gpio::Speed::high, true);
                _hLOAD->initOutput(htl::gpio::OutDriver::pushPull, htl::gpio::Speed::high, true);
                _hIN1->initOutput(htl::gpio::OutDriver::pushPull, htl::gpio::Speed::high);
                _hIN2->initOutput(htl::gpio::OutDriver::pushPull, htl::gpio::Speed::high);
                _hIN3->initOutput(htl::gpio::OutDriver::pushPull, htl::gpio::Speed::high);
                _hIN4->initOutput(htl::gpio::OutDriver::pushPull, htl::gpio::Speed::high);
                _hIN5->initOutput(htl::gpio::OutDriver::pushPull, htl::gpio::Speed::high);
                _hIN6->initOutput(htl::gpio::OutDriver::pushPull, htl::gpio::Speed::high);
                _hIN7->initOutput(htl::gpio::OutDriver::pushPull, htl::gpio::Speed::high);
                _hIN8->initOutput(htl::gpio::OutDriver::pushPull, htl::gpio::Speed::high);
                _hOUTEN->initOutput(htl::gpio::OutDriver::pushPull, htl::gpio::Speed::high, false);
                _hFAULT->initInput(htl::gpio::PullUpDn::up);
            }
			
   			void load() override {
                _hLOAD->clear();
                if ((_pinState & 0x01) == 0) _hIN1->clear(); else _hIN1->set();
                if ((_pinState & 0x02) == 0) _hIN2->clear(); else _hIN2->set();
                if ((_pinState & 0x04) == 0) _hIN3->clear(); else _hIN3->set();
                if ((_pinState & 0x08) == 0) _hIN4->clear(); else _hIN4->set();
                if ((_pinState & 0x10) == 0) _hIN5->clear(); else _hIN5->set();
                if ((_pinState & 0x20) == 0) _hIN6->clear(); else _hIN6->set();
                if ((_pinState & 0x40) == 0) _hIN7->clear(); else _hIN7->set();
                if ((_pinState & 0x80) == 0) _hIN8->clear(); else _hIN8->set();
                _hLOAD->set();
            }

			void sync() override {
				_hSYNC->clear();
				_hSYNC->set();
			}

            void set(uint8_t pinMask) override {
                _pinState |= pinMask;
            }
			
            void clear(uint8_t pinMask) override {
                _pinState &= ~pinMask;
            }
			
            void toggle(uint8_t pinMask) override {
                _pinState ^= pinMask;
            }

            void write(uint8_t pinState) override {
            	_pinState = pinState;
            }

            uint8_t read() override {
            	return _pinState;
            }
			
            inline void outputEnable() {
                _hOUTEN->set();
            }
			
            inline void outputDisable() {
                _hOUTEN->clear();
            }
	};
    
    template <typename PinSYNC_, typename PinLOAD_,
              typename PinIN1_, typename PinIN2_, typename PinIN3_, typename PinIN4_,
              typename PinIN5_, typename PinIN6_, typename PinIN7_, typename PinIN8_,
              typename PinOUTEN_, typename PinFAULT_>
    ISO808DeviceX<PinSYNC_, PinLOAD_,
        PinIN1_, PinIN2_, PinIN3_, PinIN4_,
        PinIN5_, PinIN6_, PinIN7_, PinIN8_,
        PinOUTEN_, PinFAULT_>
    ISO808DeviceX<PinSYNC_, PinLOAD_,
        PinIN1_, PinIN2_, PinIN3_, PinIN4_,
        PinIN5_, PinIN6_, PinIN7_, PinIN8_,
        PinOUTEN_, PinFAULT_>::_instance;


    class PinDriver_ISO808 final: public PinDriver {
		private:
			ISO808DeviceHandler _hDevice;
			uint8_t _pinMask;
		public:
			PinDriver_ISO808(ISO808DeviceHandler hDevice, uint8_t pinNumber);
			void set() override;
			void clear() override;
			void toggle() override;
			void write(bool pinState) override;
			bool read() const override;
    };

}


#endif // __eosPinDriver_ISO808__
