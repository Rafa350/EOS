#pragma once
#ifndef __eosPinDriver_ISO808__
#define	__eosPinDriver_ISO808__


// EOS includes
//
#include "eos.h"
#include "Controllers/Pin/eosPinDriver.h"
#include "HTL/htlGPIO.h"


namespace eos {

    template <typename PinSYNC_, typename PinLOAD_,
              typename PinIN1_, typename PinIN2_, typename PinIN3_, typename PinIN4_, 
              typename PinIN5_, typename PinIN6_, typename PinIN7_, typename PinIN8_,
              typename PinOUTEN_, typename PinFAULT_>
	class Device_ISO808 final {
		private:
			static constexpr htl::gpio::PinHandler _pinSYNC = PinSYNC_::getHandler();
			static constexpr htl::gpio::PinHandler _pinLOAD = PinLOAD_::getHandler();
			static constexpr htl::gpio::PinHandler _pinIN1 = PinIN1_::getHandler();
			static constexpr htl::gpio::PinHandler _pinIN2 = PinIN2_::getHandler();
			static constexpr htl::gpio::PinHandler _pinIN3 = PinIN3_::getHandler();
			static constexpr htl::gpio::PinHandler _pinIN4 = PinIN4_::getHandler();
			static constexpr htl::gpio::PinHandler _pinIN5 = PinIN5_::getHandler();
			static constexpr htl::gpio::PinHandler _pinIN6 = PinIN6_::getHandler();
			static constexpr htl::gpio::PinHandler _pinIN7 = PinIN7_::getHandler();
			static constexpr htl::gpio::PinHandler _pinIN8 = PinIN8_::getHandler();
			static constexpr htl::gpio::PinHandler _pinOUTEN = PinOUTEN_::getHandler();
			static constexpr htl::gpio::PinHandler _pinFAULT = PinFAULT_::getHandler();
			static uint8_t _pinState;
            
        private:
            Device_ISO808(const Device_ISO808&) = delete;
			Device_ISO808 & operator = (const Device_ISO808 &) = delete;
            
			static void refresh() {
                _pinLOAD->clear();
                if ((_pinState & 0x01) == 0) _pinIN1->clear(); else _pinIN1->set();
                if ((_pinState & 0x02) == 0) _pinIN2->clear(); else _pinIN2->set();
                if ((_pinState & 0x04) == 0) _pinIN3->clear(); else _pinIN3->set();
                if ((_pinState & 0x08) == 0) _pinIN4->clear(); else _pinIN4->set();
                if ((_pinState & 0x10) == 0) _pinIN5->clear(); else _pinIN5->set();
                if ((_pinState & 0x20) == 0) _pinIN6->clear(); else _pinIN6->set();
                if ((_pinState & 0x40) == 0) _pinIN7->clear(); else _pinIN7->set();
                if ((_pinState & 0x80) == 0) _pinIN8->clear(); else _pinIN8->set();
                _pinLOAD->set();
            }

		public:
			static void initialize() {
                _pinSYNC->initOutput(htl::gpio::OutDriver::pushPull, htl::gpio::Speed::medium, true);
                _pinLOAD->initOutput(htl::gpio::OutDriver::pushPull, htl::gpio::Speed::medium, true);
                _pinIN1->initOutput(htl::gpio::OutDriver::pushPull, htl::gpio::Speed::medium);
                _pinIN2->initOutput(htl::gpio::OutDriver::pushPull, htl::gpio::Speed::medium);
                _pinIN3->initOutput(htl::gpio::OutDriver::pushPull, htl::gpio::Speed::medium);
                _pinIN4->initOutput(htl::gpio::OutDriver::pushPull, htl::gpio::Speed::medium);
                _pinIN5->initOutput(htl::gpio::OutDriver::pushPull, htl::gpio::Speed::medium);
                _pinIN6->initOutput(htl::gpio::OutDriver::pushPull, htl::gpio::Speed::medium);
                _pinIN7->initOutput(htl::gpio::OutDriver::pushPull, htl::gpio::Speed::medium);
                _pinIN8->initOutput(htl::gpio::OutDriver::pushPull, htl::gpio::Speed::medium);
                _pinOUTEN->initOutput(htl::gpio::OutDriver::pushPull, htl::gpio::Speed::medium, false);
                _pinFAULT->initInput(htl::gpio::PullUpDn::up);
            }
			
            inline static void set(uint8_t pinMask) {
                _pinState |= pinMask;
                refresh();
            }
			
            inline static void clear(uint8_t pinMask) {
                _pinState &= ~pinMask;
                refresh();
            }
			
            inline static void toggle(uint8_t pinMask) {
                _pinState ^= pinMask;
                refresh();
            }

            inline static void write(uint8_t pinState) {
            	_pinState = pinState;
            	refresh();
            }

            inline static uint8_t read() {
            	return _pinState;
            }
			
            inline static void outputEnable() {
                _pinOUTEN->set();
            }
			
            inline static void outputDisable() {
                _pinOUTEN->clear();
            }
	};
    
    template <typename PinSYNC_, typename PinLOAD_,
              typename PinIN1_, typename PinIN2_, typename PinIN3_, typename PinIN4_, 
              typename PinIN5_, typename PinIN6_, typename PinIN7_, typename PinIN8_,
              typename PinOUTEN_, typename PinFAULT_>
    uint8_t Device_ISO808<PinSYNC_, PinLOAD_,
        PinIN1_, PinIN2_, PinIN3_, PinIN4_, 
        PinIN5_, PinIN6_, PinIN7_, PinIN8_,
        PinOUTEN_, PinFAULT_>::_pinState = 0;
}


#endif // __eosPinDriver__ISO808__
