#pragma once
/// \file      htlGPIO.h
/// \author    Rafael Serrano (rsr.openware@gmail.com)
/// \brief     GPIO module manager.
/// \addtogroup HTL HAL Template Library
/// @{
/// \addtogroup HTL_PIC32 PIC32
/// @{
/// \defgroup HTL_PIC32_GPIO GPIO
/// @{
#ifndef __PIC32_htlGPIO__
#define __PIC32_htlGPIO__


// EOS includes
//
#include "HTL/htl.h"


namespace htl {
    
    namespace gpio {

        enum class PortID {
            #ifdef HTL_PORTA_EXIST
            A, 
            #endif
            #ifdef HTL_PORTB_EXIST
            B, 
            #endif
            #ifdef HTL_PORTC_EXIST
            C, 
            #endif
            #ifdef HTL_PORTD_EXIST
            D, 
            #endif
            #ifdef HTL_PORTE_EXIST
            E, 
            #endif
            #ifdef HTL_PORTF_EXIST
            F, 
            #endif
            #ifdef HTL_PORTG_EXIST
            G
            #endif
        };
        
        enum class PinID {
            _0, 
            _1, 
            _2, 
            _3, 
            _4, 
            _5, 
            _6, 
            _7, 
            _8, 
            _9, 
            _10, 
            _11, 
            _12, 
            _13, 
            _14, 
            _15
        };
    
        typedef uint8_t PinNumber;
        typedef uint16_t PinMask;
    
        enum class PullUp {
            noChange,
            none,
            up
        };

        enum class OutDriver {
            noChange,
            pushPull,
            openDrain
        };

        enum class Speed {
            noChange,
            low,
            medium,
            hight,
            fast
        };
        
        enum class InitPinState {
            noChange,
            clear,
            set
        };

        enum class PinState {
            clear,
            set
        };


        namespace internal {

            struct __attribute__((packed , aligned(4))) GPIORegisters {
                volatile uint32_t TRISx;
                volatile uint32_t TRISxCLR;
                volatile uint32_t TRISxSET;
                volatile uint32_t TRISxINV;
                volatile uint32_t PORTx;
                volatile uint32_t PORTxCLR;
                volatile uint32_t PORTxSET;
                volatile uint32_t PORTxINV;
                volatile uint32_t LATx;
                volatile uint32_t LATxCLR;
                volatile uint32_t LATxSET;
                volatile uint32_t LATxINV;
                volatile uint32_t ODCx;
                volatile uint32_t ODCxCLR;
                volatile uint32_t ODCxSET;
                volatile uint32_t ODCxINV;
            };
            
        }
    

        class Port {
            private:
                internal::GPIORegisters *_gpio;
            protected:
                Port(internal::GPIORegisters *gpio);
            public:
                void activate();
                void deactivate();
                void reset();
                void initInput(PinMask mask, PullUp pullUp = PullUp::none);
                void initOutput(PinMask mask, OutDriver driver = OutDriver::pushPull, Speed speed = Speed::medium);
                inline void set(PinMask mask) { 
                    _gpio->LATxSET = mask; 
                }
                inline void set(PinID pinID) { 
                    _gpio->LATxSET = 1 << (int)pinID; 
                }
                inline void clear(PinMask mask) { 
                    _gpio->LATxCLR = mask; 
                }
                inline void clear(PinID pinID) { 
                    _gpio->LATxCLR = 1 << (int)pinID; 
                }
                inline void toggle(PinMask mask) { 
                    _gpio->LATxINV = mask; 
                }
                inline void toggle(PinID pinID) { 
                    _gpio->LATxINV = 1 << (int)pinID; 
                }
                inline PinMask read() { 
                    return _gpio->PORTx; 
                }
                inline PinState read(PinID pinID) {
                    return (_gpio->PORTx & (1 << (int)pinID)) ? PinState::set : PinState::clear;
                }
                inline void write(PinMask mask) { 
                    _gpio->LATx = mask; 
                }            
                inline void write(PinMask clearMask, PinMask setMask) {
                    uint16_t r = _gpio->PORTx;
                    r &= ~clearMask;
                    r |= setMask;
                    _gpio->LATx = r;
                }
                inline void write(PinID pinID, PinState state) {
                    if (state == PinState::set)
                        _gpio->LATxSET = 1 << (int) pinID;
                    else
                        _gpio->LATxCLR = 1 << (int) pinID;
                }
        };

        typedef Port * PortHandler;


        namespace internal {
            
            template <PortID>
            struct HardwareInfo;
            
        }

        template <PortID portID_>
        class PortX final: public Port {
            private:
                using HI = internal::HardwareInfo<portID_>;
            private:
                static constexpr uint32_t _gpioAddr = HI::gpioAddr;
                static _port;
			public:
				static constexpr PortID portID = portID_;
            protected:
                PortX(): 
                    Port(reinterpret_cast<internal::GPIORegisters*>(_gpioAddr)) {
                }
            public:
                inline static PortX * getHandler() {
                    return &_port;
                }
        };

		template <PortID portID_>
		PortX<portID_> PortX<portID_>::_port;

		template <PortID portID_>
		inline PortHandler getPortHandler() {
			return PortX<portID_>::getHandler();
		}

        #ifdef HTL_PORTA_EXIST
        typedef PortX<PortID::A> PortA;
        #endif
        #ifdef HTL_PORTB_EXIST
        typedef PortX<PortID::B> PortB;
        #endif
        #ifdef HTL_PORTC_EXIST
        typedef PortX<PortID::C> PortC;
        #endif
        #ifdef HTL_PORTD_EXIST
        typedef PortX<PortID::D> PortD;
        #endif
        #ifdef HTL_PORTE_EXIST
        typedef PortX<PortID::E> PortE;
        #endif
        #ifdef HTL_PORTF_EXIST
        typedef PortX<PortID::F> PortF;
        #endif
        #ifdef HTL_PORTG_EXIST
        typedef PortX<PortID::G> PortG;
        #endif

    
        class Pin {
            private:
                internal::GPIORegisters *_gpio;
                PinMask _pinMask;
            protected:
                GPIOPin(internal::GPIORegisters *gpio, PinID pinID);
            public :
                void initInput();
                void initOutput(OutDriver driver = OutDriver::pushPull, Speed speed = Speed::medium, InitPinState state = InitPinState::noChange);
                inline void set() {
                    _gpio->LATxSET = _pinMask; 
                }
                inline void clear() {
                    _gpio->LATxCLR = _pinMask; 
                }
                inline void toggle() {
                    _gpio->LATxINV = _pinMask; 
                }
                inline GPIOPinState read() {
                    return _gpio->PORTx & _pinMask ? GPIOPinState::set : GPIOPinState::clear;
                }
                inline void write(GPIOPinState state) {
                    if (state == GPIOPinState::set)
                        _gpio->LATxSET = _pinMask;
                    else
                        _gpio->LATxCLR = _pinMask;
                }
        };
        
        typedef Pin * PinHandler;
        
        template <PortID portID_, PinID pinID_>
        class PinX final: public Pin {
            private:
                using HI = internal::HardwareInfo<portID_>;
            private:
                static constexpr uint32_t _gpioAddr = HI::gpioAddr;
                static PinX _pin;
            protected:
                PinX(): 
                    Pin(reinterpret_cast<internal::GPIORegisters*>(_gpioAddr), pinID_) {
                }
            public:
                inline static PinHandler getHandler() {
                    return &_pin;
                }
        };
        
		template <PortID portID_, PinID pinID_>
		PinX<portID_, pinID_> PinX<portID_>::_pin;

		template <PortID portID_, PinID pinID_>
		inline PinHandler getPinHandler() {
			return PinX<portID_, pinID_>::getHandler();
		}

        #ifdef HTL_PORTA_EXIST
        typedef PinX<PortID::A, PinID::_0> PinA0;
        typedef PinX<PortID::A, PinID::_1> PinA1;
        typedef PinX<PortID::A, PinID::_2> PinA2;
        typedef PinX<PortID::A, PinID::_3> PinA3;
        typedef PinX<PortID::A, PinID::_4> PinA4;
        typedef PinX<PortID::A, PinID::_5> PinA5;
        typedef PinX<PortID::A, PinID::_6> PinA6;
        typedef PinX<PortID::A, PinID::_7> PinA7;
        typedef PinX<PortID::A, PinID::_8> PinA8;
        typedef PinX<PortID::A, PinID::_9> PinA9;
        typedef PinX<PortID::A, PinID::_10> PinA10;
        typedef PinX<PortID::A, PinID::_11> PinA11;
        typedef PinX<PortID::A, PinID::_12> PinA12;
        typedef PinX<PortID::A, PinID::_13> PinA13;
        typedef PinX<PortID::A, PinID::_14> PinA14;
        typedef PinX<PortID::A, PinID::_15> PinA15;
        #endif

          
        namespace internal {
    
            #ifdef HTL_PORTA_EXIST
            template <>
            struct HardwareInfo<PortID::A> {
                static constexpr uint32_t gpioAddr = _PORTA_BASE_ADDRESS - 0x10;
            };
            #endif

            #ifdef HTL_PORTB_EXIST
            template <>
            struct HardwareInfo<PortID::B> {
                static constexpr uint32_t gpioAddr = _PORTB_BASE_ADDRESS - 0x10;
            };
            #endif

            #ifdef HTL_PORTC_EXIST
            template <>
            struct HardwareInfo<PortID::C> {
                static constexpr uint32_t gpioAddr = _PORTC_BASE_ADDRESS - 0x10;
            };
            #endif

            #ifdef HTL_PORTD_EXIST
            template <>
            struct HardwareInfo<PortID::D> {
                static constexpr uint32_t gpioAddr = _PORTD_BASE_ADDRESS - 0x10;
            };
            #endif

            #ifdef HTL_PORTE_EXIST
            template <>
            struct HardwareInfo<PortID::E> {
                static constexpr uint32_t gpioAddr = _PORTE_BASE_ADDRESS - 0x10;
            };
            #endif

            #ifdef HTL_PORTF_EXIST
            template <>
            struct HardwareInfo<PortID::F> {
                static constexpr uint32_t gpioAddr = _PORTF_BASE_ADDRESS - 0x10;
            };
            #endif

            #ifdef HTL_PORTG_EXIST
            template <>
            struct HardwareInfo<PortID::G> {
                static constexpr uint32_t gpioAddr = _PORTG_BASE_ADDRESS - 0x10;
            };
            #endif
        }
    }
}


#endif // __PIC32_htlGPIO__

/// @}
/// @}
/// @}
