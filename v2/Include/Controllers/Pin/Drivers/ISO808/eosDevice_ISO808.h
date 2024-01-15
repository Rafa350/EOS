#pragma once
#ifndef __eosDevice_ISO808__
#define __eosDevice_ISO808__


// EOS includes
//
#include "eos.h"
#include "HTL/htlGPIO.h"


namespace eos {

	class Device_ISO808 final {
        public:
            using Pin = htl::gpio::Pin;
            using Result = SimpleResult<BasicResults>;
            struct CreateParams {
                Pin *pinSYNC;
                Pin *pinLOAD;
                Pin *pinIN1;
                Pin *pinIN1;
                Pin *pinIN1;
                Pin *pinIN1;
                Pin *pinIN1;
                Pin *pinIN1;
                Pin *pinIN1;
                Pin *pinIN1;
                Pin *pinOUTEN;
                Pin *pinFAULT;
            };
            
        private:
            uint8_t _oldState;
			uint8_t _newState;
			const Pin * const _pinSYNC;
			const Pin * const _pinLOAD;
			const Pin * const _pinIN1;
			const Pin * const _pinIN2;
			const Pin * const _pinIN3;
			const Pin * const _pinIN4;
			const Pin * const _pinIN5;
			const Pin * const _pinIN6;
			const Pin * const _pinIN7;
			const Pin * const _pinIN8;
			const Pin * const _pinOUTEN;
			const Pin * const _pinFAULT;
            
        private:
            Device_ISO808(const Device_ISO808 &) = delete;
            Device_ISO808 & operator = (const Device_ISO808 &) = delete;

        public:
            Device_ISO808(Pin *pinSYNC, Pin *pinLOAD, Pin *pinIN1, Pin *pinIN2, 
                Pin *pinIN3, Pin *pinIN4, Pin *pinIN5, Pin *pinIN6, Pin *pinIN7, 
                Pin *pinIN8, Pin *pinOUTEN, Pin *pinFAULT);
            Device_ISO808(const CreateParams *params);

			Result initialize();
            void deinitialize();
                    
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

}


#endif // __eosDevice_ISO808
