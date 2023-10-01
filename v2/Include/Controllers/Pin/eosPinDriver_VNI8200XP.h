#pragma once
#ifndef __eosDriver_VNI8200XP__
#define __eosDriver_VNI8200XP__


#include "eos.h"
#include "Controllers/Pin/eosPinDriver.h"
#include "HTL/htlGPIO.h"


namespace eos {
    
    class Driver_VNI8200XP {
        public:
            virtual void set(uint8_t pinMask) = 0;
            virtual void clear(uint8_t pinMask) = 0;
            virtual void toggle(uint8_t pinMask) = 0;
    };

    
    template <typename PinSCK_, typename PinMISO_, typename PinMOSI, typename PinSS_, typename PinOUTEN_>
    class Driver_VNI8200XPSerial final: public Driver_VNI8200XP {
        private:
            const htl::gpio::PinHandler _pinSCK = PinSCK_::getHandler();
            const htl::gpio::PinHandler _pinMISO = PinMISO_::getHandler();
            const htl::gpio::PinHandler _pinMOSI = PinMOSI_::getHandler();
            const htl::gpio::PinHandler _pinSS = PinSS_::getHandler();
            const htl::gpio::PinHandler _pinOUTEN = PinOUTEN_::getHandler();
        
        public:
            void set(uint8_t pinState) override;
            void clear(uint8_t pinState) override;
            void toggle(uint8_t pinState) override;
    };
    

    typename <typename PinIN1_, typename PinIN2_, typename PinIN3_, typename PinIN4_, 
              typename PinIN5_, typename PinIN6_, typename PinIN7_, typename PinIN8_>
    class Driver_VNI8200XPParalel final: public Driver_VNI8200XP {
        private:
			const htl::gpio::PinHandler _pinIN1 = PinIN1_::getHandler();
			const htl::gpio::PinHandler _pinIN2 = PinIN2_::getHandler();
			const htl::gpio::PinHandler _pinIN3 = PinIN3_::getHandler();
			const htl::gpio::PinHandler _pinIN4 = PinIN4_::getHandler();
			const htl::gpio::PinHandler _pinIN5 = PinIN5_::getHandler();
			const htl::gpio::PinHandler _pinIN6 = PinIN6_::getHandler();
			const htl::gpio::PinHandler _pinIN7 = PinIN7_::getHandler();
			const htl::gpio::PinHandler _pinIN8 = PinIN8_::getHandler();

        public:
            void set(uint8_t pinMask) override;
            void clear(uint8_t pinMask) override;
            void toggle(uint8_t pinMask) override;
    };
    
    
    class PinDriver_VNI80200XP final: public PinDriver {
		private:
			Driver_VNI8200XP *_driver;
			uint8_t _pinNumber;
		public:
			PinDriver_VNI8200XP(Driver_VNI8200XP *driver, uint8_t pinNumber);
			void set() override;
			void clear() override;
			void toggle() override;
			void write(bool state) override;
			bool read() const override;
    };
}


#endif // __eosDriver_VNI8200XP__
