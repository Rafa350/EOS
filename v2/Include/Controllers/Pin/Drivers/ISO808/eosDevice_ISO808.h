#pragma once
#ifndef __eosDevice_ISO808__
#define __eosDevice_ISO808__


// EOS includes
//
#include "eos.h"
#include "HTL/htlGPIO.h"


namespace eos {

	class Device_ISO808 {
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
            
        private:
            Device_ISO808(const Device_ISO808 &) = delete;
            Device_ISO808 & operator = (const Device_ISO808 &) = delete;

        protected:
            Device_ISO808();

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
	class DeviceX_ISO808 final: public Device_ISO808 {
		private:
			static DeviceX_ISO808 _instance;
            
        private:
            DeviceX_ISO808() :
                Device_ISO808() {
                    
            }

		public:
            static constexpr uint8_t id = id_;
			static constexpr DeviceX_ISO808 *pInst = &_instance;
			static constexpr DeviceX_ISO808 &rInst = _instance;
	};
    
    template <uint8_t id_>
    DeviceX_ISO808<id_> DeviceX_ISO808<id_>::_instance;

}


#endif // __eosDevice_ISO808
