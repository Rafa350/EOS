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
            #ifdef HTL_GPIOA_EXIST
            A,
            #endif
            #ifdef HTL_GPIOB_EXIST
            B,
            #endif
            #ifdef HTL_GPIOC_EXIST
            C,
            #endif
            #ifdef HTL_GPIOD_EXIST
            D,
            #endif
            #ifdef HTL_GPIOE_EXIST
            E,
            #endif
            #ifdef HTL_GPIOF_EXIST
            F,
            #endif
            #ifdef HTL_GPIOG_EXIST
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

        /// \bried Input mode
        enum class InputMode {
			floating,
			pullUp
        };

		/// \bried Output mode
		enum class OutputMode {
			pushPull,
			openDrain,
			openDrainPullUp
		};

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
                internal::GPIORegisters * const _gpio;
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
                inline bool read(PinID pinID) {
                    return (_gpio->PORTx & (1 << (int)pinID)) ? true : false;
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
                inline void write(PinID pinID, bool pinState) {
                    if (pinState)
                        _gpio->LATxSET = 1 << (int) pinID;
                    else
                        _gpio->LATxCLR = 1 << (int) pinID;
                }
        };


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
                static PortX _instance;
			public:
				static constexpr PortID portID = portID_;
                static constexpr PortX *pInst = &_instance;
                static constexpr PortX &rInst = _instance;
            protected:
                PortX():
                    Port(reinterpret_cast<internal::GPIORegisters*>(_gpioAddr)) {
                }
        };

		template <PortID portID_>
		PortX<portID_> PortX<portID_>::_instance;

        #ifdef HTL_GPIOA_EXIST
        typedef PortX<PortID::A> PortA;
        #endif
        #ifdef HTL_GPIOB_EXIST
        typedef PortX<PortID::B> PortB;
        #endif
        #ifdef HTL_GPIOC_EXIST
        typedef PortX<PortID::C> PortC;
        #endif
        #ifdef HTL_GPIOD_EXIST
        typedef PortX<PortID::D> PortD;
        #endif
        #ifdef HTL_GPIOE_EXIST
        typedef PortX<PortID::E> PortE;
        #endif
        #ifdef HTL_GPIOF_EXIST
        typedef PortX<PortID::F> PortF;
        #endif
        #ifdef HTL_GPIOG_EXIST
        typedef PortX<PortID::G> PortG;
        #endif


        class Pin {
            private:
                internal::GPIORegisters * const _gpio;
                PinMask const _pinMask;
            protected:
                Pin(internal::GPIORegisters *gpio, PinID pinID);
            public :
                void initInput(PullUp pullUp = PullUp::noChange);
                void initOutput(OutDriver driver = OutDriver::pushPull, Speed speed = Speed::medium);
                void initOutput(OutDriver driver, Speed speed, bool pinState);
                inline void set() {
                    _gpio->LATxSET = _pinMask;
                }
                inline void clear() {
                    _gpio->LATxCLR = _pinMask;
                }
                inline void toggle() {
                    _gpio->LATxINV = _pinMask;
                }
                inline bool read() {
                    return _gpio->PORTx & _pinMask ? true : false;
                }
                inline void write(bool pinState) {
                    if (pinState)
                        _gpio->LATxSET = _pinMask;
                    else
                        _gpio->LATxCLR = _pinMask;
                }
        };

        template <PortID portID_, PinID pinID_>
        class PinX final: public Pin {
            private:
                using HI = internal::HardwareInfo<portID_>;
            private:
                static constexpr uint32_t _gpioAddr = HI::gpioAddr;
                static PinX _instance;
            public:
                static constexpr PortID portID = portID_;
                static constexpr PinID pinID = pinID_;
                static constexpr PinX *pInst = &_instance;
                static constexpr PinX &rInst = _instance;
            protected:
                PinX():
                    Pin(reinterpret_cast<internal::GPIORegisters*>(_gpioAddr), pinID_) {
                }
        };

		template <PortID portID_, PinID pinID_>
		PinX<portID_, pinID_> PinX<portID_, pinID_>::_instance;


        #ifdef HTL_GPIOA_EXIST
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

        #ifdef HTL_GPIOB_EXIST
        typedef PinX<PortID::B, PinID::_0> PinB0;
        typedef PinX<PortID::B, PinID::_1> PinB1;
        typedef PinX<PortID::B, PinID::_2> PinB2;
        typedef PinX<PortID::B, PinID::_3> PinB3;
        typedef PinX<PortID::B, PinID::_4> PinB4;
        typedef PinX<PortID::B, PinID::_5> PinB5;
        typedef PinX<PortID::B, PinID::_6> PinB6;
        typedef PinX<PortID::B, PinID::_7> PinB7;
        typedef PinX<PortID::B, PinID::_8> PinB8;
        typedef PinX<PortID::B, PinID::_9> PinB9;
        typedef PinX<PortID::B, PinID::_10> PinB10;
        typedef PinX<PortID::B, PinID::_11> PinB11;
        typedef PinX<PortID::B, PinID::_12> PinB12;
        typedef PinX<PortID::B, PinID::_13> PinB13;
        typedef PinX<PortID::B, PinID::_14> PiBA14;
        typedef PinX<PortID::B, PinID::_15> PiBA15;
        #endif

        #ifdef HTL_GPIOC_EXIST
        typedef PinX<PortID::C, PinID::_0> PinC0;
        typedef PinX<PortID::C, PinID::_1> PinC1;
        typedef PinX<PortID::C, PinID::_2> PinC2;
        typedef PinX<PortID::C, PinID::_3> PinC3;
        typedef PinX<PortID::C, PinID::_4> PinC4;
        typedef PinX<PortID::C, PinID::_5> PinC5;
        typedef PinX<PortID::C, PinID::_6> PinC6;
        typedef PinX<PortID::C, PinID::_7> PinC7;
        typedef PinX<PortID::C, PinID::_8> PinC8;
        typedef PinX<PortID::C, PinID::_9> PinC9;
        typedef PinX<PortID::C, PinID::_10> PinC10;
        typedef PinX<PortID::C, PinID::_11> PinC11;
        typedef PinX<PortID::C, PinID::_12> PinC12;
        typedef PinX<PortID::C, PinID::_13> PinC13;
        typedef PinX<PortID::C, PinID::_14> PiBC14;
        typedef PinX<PortID::C, PinID::_15> PiBC15;
        #endif

        #ifdef HTL_GPIOD_EXIST
        typedef PinX<PortID::D, PinID::_0> PinD0;
        typedef PinX<PortID::D, PinID::_1> PinD1;
        typedef PinX<PortID::D, PinID::_2> PinD2;
        typedef PinX<PortID::D, PinID::_3> PinD3;
        typedef PinX<PortID::D, PinID::_4> PinD4;
        typedef PinX<PortID::D, PinID::_5> PinD5;
        typedef PinX<PortID::D, PinID::_6> PinD6;
        typedef PinX<PortID::D, PinID::_7> PinD7;
        typedef PinX<PortID::D, PinID::_8> PinD8;
        typedef PinX<PortID::D, PinID::_9> PinD9;
        typedef PinX<PortID::D, PinID::_10> PinD10;
        typedef PinX<PortID::D, PinID::_11> PinD11;
        typedef PinX<PortID::D, PinID::_12> PinD12;
        typedef PinX<PortID::D, PinID::_13> PinD13;
        typedef PinX<PortID::D, PinID::_14> PiBD14;
        typedef PinX<PortID::D, PinID::_15> PiBD15;
        #endif

        namespace internal {

            #ifdef HTL_GPIOA_EXIST
            template <>
            struct HardwareInfo<PortID::A> {
                static constexpr uint32_t gpioAddr = _PORTA_BASE_ADDRESS - 0x10;
            };
            #endif

            #ifdef HTL_GPIOB_EXIST
            template <>
            struct HardwareInfo<PortID::B> {
                static constexpr uint32_t gpioAddr = _PORTB_BASE_ADDRESS - 0x10;
            };
            #endif

            #ifdef HTL_GPIOC_EXIST
            template <>
            struct HardwareInfo<PortID::C> {
                static constexpr uint32_t gpioAddr = _PORTC_BASE_ADDRESS - 0x10;
            };
            #endif

            #ifdef HTL_GPIOD_EXIST
            template <>
            struct HardwareInfo<PortID::D> {
                static constexpr uint32_t gpioAddr = _PORTD_BASE_ADDRESS - 0x10;
            };
            #endif

            #ifdef HTL_GPIOE_EXIST
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
