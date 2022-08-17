#pragma once
/// \file      halGPIO_ex.h
/// \author    Rafael Serrano (rsr.openware@gmail.com)
/// \brief     GPIO module manager.
/// \addtogroup HTL HAL Template Library
/// @{
/// \addtogroup HTL_STM32 STM32
/// @{
/// \defgroup HTL_STM32_GPIO GPIO
/// @{
#ifndef __STM32_htlGPIO__
#define __STM32_htlGPIO__


// EOS includes
//
#include "HTL/htl.h"


namespace htl {

    /// \brief Port identifiers.
    enum class GPIOPort {
        #ifdef GPIOA_BASE
            A,
        #endif
        #ifdef GPIOB_BASE
            B,
        #endif
        #ifdef GPIOC_BASE
            C,
        #endif
        #ifdef GPIOD_BASE
            D,
        #endif
        #ifdef GPIOE_BASE
            E,
        #endif
        #ifdef GPIOF_BASE
            F,
        #endif
        #ifdef GPIOG_BASE
            G,
        #endif
        #ifdef GPIOH_BASE
            H,
        #endif
        #ifdef GPIOI_BASE
            I,
        #endif
        #ifdef GPIOJ_BASE
            J,
        #endif
        #ifdef GPIOK_BASE
            K,
        #endif
    };

    /// \brief Pin identifiers.
    enum class GPIOPin {
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

    /// \brief Alternate function identifiers
    enum class GPIOAlt {
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

    /// \brief Pull up/down mode identifier.
    enum class GPIOPull {
    	noChange,
        none,
        up,
        down
    };

    /// \brief Driver type identifiers.
    enum class GPIODriver {
    	noChange,
        pushPull,
        openDrain
    };

    /// \brief Speed identifier.
    enum class GPIOSpeed {
    	noChange,
        low,
        medium,
        high,
        fast
    };

    void GPIO_initInput(GPIO_TypeDef*, uint32_t, GPIOPull);
    void GPIO_initOutput(GPIO_TypeDef*, uint32_t, GPIODriver, GPIOSpeed);
    void GPIO_initAlt(GPIO_TypeDef*, uint32_t, GPIODriver, GPIOSpeed, GPIOAlt);

    template <GPIOPort>
    struct GPIOPortTrait {
    };

    template <GPIOPort, GPIOPin>
    struct GPIOPinTrait {
    };

    template <GPIOPort port_>
    class GPIOPortActivator final {
    	private:
    		static uint16_t _activated;

    	public:
    		static void activate(
    			uint16_t mask) {

    			if (!_activated) {
    				if constexpr (port_ == GPIOPort::A)
    					RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    				else if constexpr (port_ == GPIOPort::B)
    					RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    				else if constexpr (port_ == GPIOPort::C)
    					RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    				else if constexpr (port_ == GPIOPort::D)
    					RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    				else if constexpr (port_ == GPIOPort::E)
    					RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
    				else if constexpr (port_ == GPIOPort::F)
    					RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;
    				else if constexpr (port_ == GPIOPort::G)
    					RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
    				else if constexpr (port_ == GPIOPort::H)
    					RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;
    				else if constexpr (port_ == GPIOPort::I)
    					RCC->AHB1ENR |= RCC_AHB1ENR_GPIOIEN;
    				else if constexpr (port_ == GPIOPort::J)
    					RCC->AHB1ENR |= RCC_AHB1ENR_GPIOJEN;
    				else if constexpr (port_ == GPIOPort::K)
    					RCC->AHB1ENR |= RCC_AHB1ENR_GPIOKEN;
    				__DSB();
    			}
    			_activated |= mask;
    		}

    		static void deactivate(
    			uint16_t mask) {

    			_activated &= ~mask;
    			if (!_activated) {
    				if constexpr (port_ == GPIOPort::A)
    					RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOAEN;
    				else if constexpr (port_ == GPIOPort::B)
    					RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOBEN;
    				else if constexpr (port_ == GPIOPort::C)
    					RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOCEN;
    				else if constexpr (port_ == GPIOPort::D)
    					RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIODEN;
    				else if constexpr (port_ == GPIOPort::E)
    					RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOEEN;
    				else if constexpr (port_ == GPIOPort::F)
    					RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOFEN;
    				else if constexpr (port_ == GPIOPort::G)
    					RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOGEN;
    				else if constexpr (port_ == GPIOPort::H)
    					RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOHEN;
    				else if constexpr (port_ == GPIOPort::I)
    					RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOIEN;
    				else if constexpr (port_ == GPIOPort::J)
    					RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOJEN;
    				else if constexpr (port_ == GPIOPort::K)
    					RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOKEN;
    			}
    		}
    };

    template <GPIOPort port_> uint16_t GPIOPortActivator<port_>::_activated = 0;


    /// \class GPIO_x
    /// \brief Adapter class for gpio pins
    ///
    template <GPIOPort port_, GPIOPin pin_>
    class GPIO_x final {
        private:
            using PortTrait = GPIOPortTrait<port_>;
            using PinTrait = GPIOPinTrait<port_, pin_>;
            using Activator = GPIOPortActivator<port_>;
            static constexpr uint32_t _addr = PortTrait::addr;
            static constexpr uint32_t _pn = PinTrait::pn;

        public:
            static constexpr GPIOPort port = port_;
            static constexpr GPIOPin pin = pin_;

        private:
            GPIO_x() = delete;
            GPIO_x(const GPIO_x &) = delete;
            GPIO_x(const GPIO_x &&) = delete;
            ~GPIO_x() = delete;

            GPIO_x & operator = (const GPIO_x &) = delete;
            GPIO_x & operator = (const GPIO_x &&) = delete;

        public:
            static void initInput(
            	GPIOPull pull = GPIOPull::none) {

            	Activator::activate(1 << _pn);
                GPIO_initInput(
                    reinterpret_cast<GPIO_TypeDef*>(_addr), 
                    _pn,
                    pull);
            }

            static void initOutput(
            	GPIODriver driver,
				GPIOSpeed speed = GPIOSpeed::medium) {

            	Activator::activate(1 << _pn);
            	GPIO_initOutput(
                    reinterpret_cast<GPIO_TypeDef*>(_addr),
                    _pn,
                    driver,
                    speed);
            }

            static void initAlt(
            	GPIODriver driver,
				GPIOSpeed speed,
				GPIOAlt alt) {
                
            	Activator::activate(1 << _pn);
            	GPIO_initAlt(
                    reinterpret_cast<GPIO_TypeDef*>(_addr),
                    _pn,
                    driver,
                    speed,
					alt);
            }

            static void deInit() {

            	Activator::deactivate(1 << _pn);
            }

            /// \brief Set pin to ON state.
            ///
            inline static void set() {

                GPIO_TypeDef *regs = reinterpret_cast<GPIO_TypeDef*>(_addr);
                regs->BSRR = 1 << _pn;
            }

            /// \brief Set pin to OFF state.
            ///
            inline static void clear() {

                GPIO_TypeDef *regs = reinterpret_cast<GPIO_TypeDef*>(_addr);
                regs->BSRR = 1 << (_pn + 16);
            }

            /// \brief Toggle pin state.
            ///
            inline static void toggle() {

                GPIO_TypeDef *regs = reinterpret_cast<GPIO_TypeDef*>(_addr);
                regs->ODR ^= 1 << _pn;
            }

            /// \brief Read pin state
            /// \return Pin state.
            ///
            inline static bool read() {

                GPIO_TypeDef *regs = reinterpret_cast<GPIO_TypeDef*>(_addr);
                return regs->IDR & (1 << _pn);
            }

            /// \brief Write pin state.
            /// \param b: State to write.
            ///
            inline static void write(bool s) {

                GPIO_TypeDef *regs = reinterpret_cast<GPIO_TypeDef*>(_addr);
                regs->BSRR = 1 << (_pn + (s ? 0 : 16));
            }
    };

    #ifdef GPIOA_BASE
        typedef GPIO_x<GPIOPort::A, GPIOPin::_0> GPIO_A0;
        typedef GPIO_x<GPIOPort::A, GPIOPin::_1> GPIO_A1;
        typedef GPIO_x<GPIOPort::A, GPIOPin::_2> GPIO_A2;
        typedef GPIO_x<GPIOPort::A, GPIOPin::_3> GPIO_A3;
        typedef GPIO_x<GPIOPort::A, GPIOPin::_4> GPIO_A4;
        typedef GPIO_x<GPIOPort::A, GPIOPin::_5> GPIO_A5;
        typedef GPIO_x<GPIOPort::A, GPIOPin::_6> GPIO_A6;
        typedef GPIO_x<GPIOPort::A, GPIOPin::_7> GPIO_A7;
        typedef GPIO_x<GPIOPort::A, GPIOPin::_8> GPIO_A8;
        typedef GPIO_x<GPIOPort::A, GPIOPin::_9> GPIO_A9;
        typedef GPIO_x<GPIOPort::A, GPIOPin::_10> GPIO_A10;
        typedef GPIO_x<GPIOPort::A, GPIOPin::_11> GPIO_A11;
        typedef GPIO_x<GPIOPort::A, GPIOPin::_12> GPIO_A12;
        typedef GPIO_x<GPIOPort::A, GPIOPin::_13> GPIO_A13;
        typedef GPIO_x<GPIOPort::A, GPIOPin::_14> GPIO_A14;
        typedef GPIO_x<GPIOPort::A, GPIOPin::_15> GPIO_A15;
    #endif

    #ifdef GPIOB_BASE
        typedef GPIO_x<GPIOPort::B, GPIOPin::_0> GPIO_B0;
        typedef GPIO_x<GPIOPort::B, GPIOPin::_1> GPIO_B1;
        typedef GPIO_x<GPIOPort::B, GPIOPin::_2> GPIO_B2;
        typedef GPIO_x<GPIOPort::B, GPIOPin::_3> GPIO_B3;
        typedef GPIO_x<GPIOPort::B, GPIOPin::_4> GPIO_B4;
        typedef GPIO_x<GPIOPort::B, GPIOPin::_5> GPIO_B5;
        typedef GPIO_x<GPIOPort::B, GPIOPin::_6> GPIO_B6;
        typedef GPIO_x<GPIOPort::B, GPIOPin::_7> GPIO_B7;
        typedef GPIO_x<GPIOPort::B, GPIOPin::_8> GPIO_B8;
        typedef GPIO_x<GPIOPort::B, GPIOPin::_9> GPIO_B9;
        typedef GPIO_x<GPIOPort::B, GPIOPin::_10> GPIO_B10;
        typedef GPIO_x<GPIOPort::B, GPIOPin::_11> GPIO_B11;
        typedef GPIO_x<GPIOPort::B, GPIOPin::_12> GPIO_B12;
        typedef GPIO_x<GPIOPort::B, GPIOPin::_13> GPIO_B13;
        typedef GPIO_x<GPIOPort::B, GPIOPin::_14> GPIO_B14;
        typedef GPIO_x<GPIOPort::B, GPIOPin::_15> GPIO_B15;
    #endif

    #ifdef GPIOC_BASE
        typedef GPIO_x<GPIOPort::C, GPIOPin::_0> GPIO_C0;
        typedef GPIO_x<GPIOPort::C, GPIOPin::_1> GPIO_C1;
        typedef GPIO_x<GPIOPort::C, GPIOPin::_2> GPIO_C2;
        typedef GPIO_x<GPIOPort::C, GPIOPin::_3> GPIO_C3;
        typedef GPIO_x<GPIOPort::C, GPIOPin::_4> GPIO_C4;
        typedef GPIO_x<GPIOPort::C, GPIOPin::_5> GPIO_C5;
        typedef GPIO_x<GPIOPort::C, GPIOPin::_6> GPIO_C6;
        typedef GPIO_x<GPIOPort::C, GPIOPin::_7> GPIO_C7;
        typedef GPIO_x<GPIOPort::C, GPIOPin::_8> GPIO_C8;
        typedef GPIO_x<GPIOPort::C, GPIOPin::_9> GPIO_C9;
        typedef GPIO_x<GPIOPort::C, GPIOPin::_10> GPIO_C10;
        typedef GPIO_x<GPIOPort::C, GPIOPin::_11> GPIO_C11;
        typedef GPIO_x<GPIOPort::C, GPIOPin::_12> GPIO_C12;
        typedef GPIO_x<GPIOPort::C, GPIOPin::_13> GPIO_C13;
        typedef GPIO_x<GPIOPort::C, GPIOPin::_14> GPIO_C14;
        typedef GPIO_x<GPIOPort::C, GPIOPin::_15> GPIO_C15;
    #endif

    #ifdef GPIOD_BASE
        typedef GPIO_x<GPIOPort::D, GPIOPin::_0> GPIO_D0;
        typedef GPIO_x<GPIOPort::D, GPIOPin::_1> GPIO_D1;
        typedef GPIO_x<GPIOPort::D, GPIOPin::_2> GPIO_D2;
        typedef GPIO_x<GPIOPort::D, GPIOPin::_3> GPIO_D3;
        typedef GPIO_x<GPIOPort::D, GPIOPin::_4> GPIO_D4;
        typedef GPIO_x<GPIOPort::D, GPIOPin::_5> GPIO_D5;
        typedef GPIO_x<GPIOPort::D, GPIOPin::_6> GPIO_D6;
        typedef GPIO_x<GPIOPort::D, GPIOPin::_7> GPIO_D7;
        typedef GPIO_x<GPIOPort::D, GPIOPin::_8> GPIO_D8;
        typedef GPIO_x<GPIOPort::D, GPIOPin::_9> GPIO_D9;
        typedef GPIO_x<GPIOPort::D, GPIOPin::_10> GPIO_D10;
        typedef GPIO_x<GPIOPort::D, GPIOPin::_11> GPIO_D11;
        typedef GPIO_x<GPIOPort::D, GPIOPin::_12> GPIO_D12;
        typedef GPIO_x<GPIOPort::D, GPIOPin::_13> GPIO_D13;
        typedef GPIO_x<GPIOPort::D, GPIOPin::_14> GPIO_D14;
        typedef GPIO_x<GPIOPort::D, GPIOPin::_15> GPIO_D15;
    #endif

    #ifdef GPIOE_BASE
        typedef GPIO_x<GPIOPort::E, GPIOPin::_0> GPIO_E0;
        typedef GPIO_x<GPIOPort::E, GPIOPin::_1> GPIO_E1;
        typedef GPIO_x<GPIOPort::E, GPIOPin::_2> GPIO_E2;
        typedef GPIO_x<GPIOPort::E, GPIOPin::_3> GPIO_E3;
        typedef GPIO_x<GPIOPort::E, GPIOPin::_4> GPIO_E4;
        typedef GPIO_x<GPIOPort::E, GPIOPin::_5> GPIO_E5;
        typedef GPIO_x<GPIOPort::E, GPIOPin::_6> GPIO_E6;
        typedef GPIO_x<GPIOPort::E, GPIOPin::_7> GPIO_E7;
        typedef GPIO_x<GPIOPort::E, GPIOPin::_8> GPIO_E8;
        typedef GPIO_x<GPIOPort::E, GPIOPin::_9> GPIO_E9;
        typedef GPIO_x<GPIOPort::E, GPIOPin::_10> GPIO_E10;
        typedef GPIO_x<GPIOPort::E, GPIOPin::_11> GPIO_E11;
        typedef GPIO_x<GPIOPort::E, GPIOPin::_12> GPIO_E12;
        typedef GPIO_x<GPIOPort::E, GPIOPin::_13> GPIO_E13;
        typedef GPIO_x<GPIOPort::E, GPIOPin::_14> GPIO_E14;
        typedef GPIO_x<GPIOPort::E, GPIOPin::_15> GPIO_E15;
    #endif

    #ifdef GPIOF_BASE
        typedef GPIO_x<GPIOPort::F, GPIOPin::_0> GPIO_F0;
        typedef GPIO_x<GPIOPort::F, GPIOPin::_1> GPIO_F1;
        typedef GPIO_x<GPIOPort::F, GPIOPin::_2> GPIO_F2;
        typedef GPIO_x<GPIOPort::F, GPIOPin::_3> GPIO_F3;
        typedef GPIO_x<GPIOPort::F, GPIOPin::_4> GPIO_F4;
        typedef GPIO_x<GPIOPort::F, GPIOPin::_5> GPIO_F5;
        typedef GPIO_x<GPIOPort::F, GPIOPin::_6> GPIO_F6;
        typedef GPIO_x<GPIOPort::F, GPIOPin::_7> GPIO_F7;
        typedef GPIO_x<GPIOPort::F, GPIOPin::_8> GPIO_F8;
        typedef GPIO_x<GPIOPort::F, GPIOPin::_9> GPIO_F9;
        typedef GPIO_x<GPIOPort::F, GPIOPin::_10> GPIO_F10;
        typedef GPIO_x<GPIOPort::F, GPIOPin::_11> GPIO_F11;
        typedef GPIO_x<GPIOPort::F, GPIOPin::_12> GPIO_F12;
        typedef GPIO_x<GPIOPort::F, GPIOPin::_13> GPIO_F13;
        typedef GPIO_x<GPIOPort::F, GPIOPin::_14> GPIO_F14;
        typedef GPIO_x<GPIOPort::F, GPIOPin::_15> GPIO_F15;
    #endif

    #ifdef GPIOG_BASE
        typedef GPIO_x<GPIOPort::G, GPIOPin::_0> GPIO_G0;
        typedef GPIO_x<GPIOPort::G, GPIOPin::_1> GPIO_G1;
        typedef GPIO_x<GPIOPort::G, GPIOPin::_2> GPIO_G2;
        typedef GPIO_x<GPIOPort::G, GPIOPin::_3> GPIO_G3;
        typedef GPIO_x<GPIOPort::G, GPIOPin::_4> GPIO_G4;
        typedef GPIO_x<GPIOPort::G, GPIOPin::_5> GPIO_G5;
        typedef GPIO_x<GPIOPort::G, GPIOPin::_6> GPIO_G6;
        typedef GPIO_x<GPIOPort::G, GPIOPin::_7> GPIO_G7;
        typedef GPIO_x<GPIOPort::G, GPIOPin::_8> GPIO_G8;
        typedef GPIO_x<GPIOPort::G, GPIOPin::_9> GPIO_G9;
        typedef GPIO_x<GPIOPort::G, GPIOPin::_10> GPIO_G10;
        typedef GPIO_x<GPIOPort::G, GPIOPin::_11> GPIO_G11;
        typedef GPIO_x<GPIOPort::G, GPIOPin::_12> GPIO_G12;
        typedef GPIO_x<GPIOPort::G, GPIOPin::_13> GPIO_G13;
        typedef GPIO_x<GPIOPort::G, GPIOPin::_14> GPIO_G14;
        typedef GPIO_x<GPIOPort::G, GPIOPin::_15> GPIO_G15;
    #endif

    #ifdef GPIOH_BASE
        typedef GPIO_x<GPIOPort::H, GPIOPin::_0> GPIO_H0;
        typedef GPIO_x<GPIOPort::H, GPIOPin::_1> GPIO_H1;
        typedef GPIO_x<GPIOPort::H, GPIOPin::_2> GPIO_H2;
        typedef GPIO_x<GPIOPort::H, GPIOPin::_3> GPIO_H3;
        typedef GPIO_x<GPIOPort::H, GPIOPin::_4> GPIO_H4;
        typedef GPIO_x<GPIOPort::H, GPIOPin::_5> GPIO_H5;
        typedef GPIO_x<GPIOPort::H, GPIOPin::_6> GPIO_H6;
        typedef GPIO_x<GPIOPort::H, GPIOPin::_7> GPIO_H7;
        typedef GPIO_x<GPIOPort::H, GPIOPin::_8> GPIO_H8;
        typedef GPIO_x<GPIOPort::H, GPIOPin::_9> GPIO_H9;
        typedef GPIO_x<GPIOPort::H, GPIOPin::_10> GPIO_H10;
        typedef GPIO_x<GPIOPort::H, GPIOPin::_11> GPIO_H11;
        typedef GPIO_x<GPIOPort::H, GPIOPin::_12> GPIO_H12;
        typedef GPIO_x<GPIOPort::H, GPIOPin::_13> GPIO_H13;
        typedef GPIO_x<GPIOPort::H, GPIOPin::_14> GPIO_H14;
        typedef GPIO_x<GPIOPort::H, GPIOPin::_15> GPIO_H15;
    #endif

    #ifdef GPIOI_BASE
        typedef GPIO_x<GPIOPort::I, GPIOPin::_0> GPIO_I0;
        typedef GPIO_x<GPIOPort::I, GPIOPin::_1> GPIO_I1;
        typedef GPIO_x<GPIOPort::I, GPIOPin::_2> GPIO_I2;
        typedef GPIO_x<GPIOPort::I, GPIOPin::_3> GPIO_I3;
        typedef GPIO_x<GPIOPort::I, GPIOPin::_4> GPIO_I4;
        typedef GPIO_x<GPIOPort::I, GPIOPin::_5> GPIO_I5;
        typedef GPIO_x<GPIOPort::I, GPIOPin::_6> GPIO_I6;
        typedef GPIO_x<GPIOPort::I, GPIOPin::_7> GPIO_I7;
        typedef GPIO_x<GPIOPort::I, GPIOPin::_8> GPIO_I8;
        typedef GPIO_x<GPIOPort::I, GPIOPin::_9> GPIO_I9;
        typedef GPIO_x<GPIOPort::I, GPIOPin::_10> GPIO_I10;
        typedef GPIO_x<GPIOPort::I, GPIOPin::_11> GPIO_I11;
        typedef GPIO_x<GPIOPort::I, GPIOPin::_12> GPIO_I12;
        typedef GPIO_x<GPIOPort::I, GPIOPin::_13> GPIO_I13;
        typedef GPIO_x<GPIOPort::I, GPIOPin::_14> GPIO_I14;
        typedef GPIO_x<GPIOPort::I, GPIOPin::_15> GPIO_I15;
    #endif

    #ifdef GPIOJ_BASE
        typedef GPIO_x<GPIOPort::J, GPIOPin::_0> GPIO_J0;
        typedef GPIO_x<GPIOPort::J, GPIOPin::_1> GPIO_J1;
        typedef GPIO_x<GPIOPort::J, GPIOPin::_2> GPIO_J2;
        typedef GPIO_x<GPIOPort::J, GPIOPin::_3> GPIO_J3;
        typedef GPIO_x<GPIOPort::J, GPIOPin::_4> GPIO_J4;
        typedef GPIO_x<GPIOPort::J, GPIOPin::_5> GPIO_J5;
        typedef GPIO_x<GPIOPort::J, GPIOPin::_6> GPIO_J6;
        typedef GPIO_x<GPIOPort::J, GPIOPin::_7> GPIO_J7;
        typedef GPIO_x<GPIOPort::J, GPIOPin::_8> GPIO_J8;
        typedef GPIO_x<GPIOPort::J, GPIOPin::_9> GPIO_J9;
        typedef GPIO_x<GPIOPort::J, GPIOPin::_10> GPIO_J10;
        typedef GPIO_x<GPIOPort::J, GPIOPin::_11> GPIO_J11;
        typedef GPIO_x<GPIOPort::J, GPIOPin::_12> GPIO_J12;
        typedef GPIO_x<GPIOPort::J, GPIOPin::_13> GPIO_J13;
        typedef GPIO_x<GPIOPort::J, GPIOPin::_14> GPIO_J14;
        typedef GPIO_x<GPIOPort::J, GPIOPin::_15> GPIO_J15;
    #endif

    #ifdef GPIOK_BASE
        typedef GPIO_x<GPIOPort::K, GPIOPin::_0> GPIO_K0;
        typedef GPIO_x<GPIOPort::K, GPIOPin::_1> GPIO_K1;
        typedef GPIO_x<GPIOPort::K, GPIOPin::_2> GPIO_K2;
        typedef GPIO_x<GPIOPort::K, GPIOPin::_3> GPIO_K3;
        typedef GPIO_x<GPIOPort::K, GPIOPin::_4> GPIO_K4;
        typedef GPIO_x<GPIOPort::K, GPIOPin::_5> GPIO_K5;
        typedef GPIO_x<GPIOPort::K, GPIOPin::_6> GPIO_K6;
        typedef GPIO_x<GPIOPort::K, GPIOPin::_7> GPIO_K7;
        typedef GPIO_x<GPIOPort::K, GPIOPin::_8> GPIO_K8;
        typedef GPIO_x<GPIOPort::K, GPIOPin::_9> GPIO_K9;
        typedef GPIO_x<GPIOPort::K, GPIOPin::_10> GPIO_K10;
        typedef GPIO_x<GPIOPort::K, GPIOPin::_11> GPIO_K11;
        typedef GPIO_x<GPIOPort::K, GPIOPin::_12> GPIO_K12;
        typedef GPIO_x<GPIOPort::K, GPIOPin::_13> GPIO_K13;
        typedef GPIO_x<GPIOPort::K, GPIOPin::_14> GPIO_K14;
        typedef GPIO_x<GPIOPort::K, GPIOPin::_15> GPIO_K15;
    #endif


    #ifdef GPIOA_BASE
        template<>
        struct GPIOPortTrait<GPIOPort::A> {
            static constexpr uint32_t addr = GPIOA_BASE;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::A, GPIOPin::_0> {
            static constexpr uint32_t pn = 0;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::A, GPIOPin::_1> {
            static constexpr uint32_t pn = 1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::A, GPIOPin::_3> {
            static constexpr uint32_t pn = 3;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::A, GPIOPin::_4> {
            static constexpr uint32_t pn = 4;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::A, GPIOPin::_5> {
            static constexpr uint32_t pn = 5;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::A, GPIOPin::_6> {
            static constexpr uint32_t pn = 6;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::A, GPIOPin::_7> {
            static constexpr uint32_t pn = 7;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::A, GPIOPin::_8> {
            static constexpr uint32_t pn = 8;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::A, GPIOPin::_9> {
            static constexpr uint32_t pn = 9;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::A, GPIOPin::_10> {
            static constexpr uint32_t pn = 10;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::A, GPIOPin::_11> {
            static constexpr uint32_t pn = 11;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::A, GPIOPin::_12> {
            static constexpr uint32_t pn = 12;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::A, GPIOPin::_13> {
            static constexpr uint32_t pn = 13;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::A, GPIOPin::_14> {
            static constexpr uint32_t pn = 14;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::A, GPIOPin::_15> {
            static constexpr uint32_t pn = 15;
        };
    #endif

    #ifdef GPIOB_BASE
        template  <>
        struct GPIOPortTrait<GPIOPort::B> {
            static constexpr uint32_t addr = GPIOB_BASE;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::B, GPIOPin::_0> {
            static constexpr uint32_t pn = 0;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::B, GPIOPin::_1> {
            static constexpr uint32_t pn = 1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::B, GPIOPin::_2> {
            static constexpr uint32_t pn = 2;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::B, GPIOPin::_3> {
            static constexpr uint32_t pn = 3;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::B, GPIOPin::_4> {
            static constexpr uint32_t pn = 4;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::B, GPIOPin::_5> {
            static constexpr uint32_t pn = 5;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::B, GPIOPin::_6> {
            static constexpr uint32_t pn = 6;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::B, GPIOPin::_7> {
            static constexpr uint32_t pn = 7;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::B, GPIOPin::_8> {
            static constexpr uint32_t pn = 8;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::B, GPIOPin::_9> {
            static constexpr uint32_t pn = 9;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::B, GPIOPin::_10> {
            static constexpr uint32_t pn = 10;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::B, GPIOPin::_11> {
            static constexpr uint32_t pn = 11;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::B, GPIOPin::_14> {
            static constexpr uint32_t pn = 14;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::B, GPIOPin::_15> {
            static constexpr uint32_t pn = 15;
        };
    #endif

    #ifdef GPIOC_BASE
        template  <>
        struct GPIOPortTrait<GPIOPort::C> {
            static constexpr uint32_t addr = GPIOC_BASE;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::C, GPIOPin::_2> {
            static constexpr uint32_t pn = 2;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::C, GPIOPin::_6> {
            static constexpr uint32_t pn = 6;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::C, GPIOPin::_7> {
            static constexpr uint32_t pn = 7;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::C, GPIOPin::_10> {
            static constexpr uint32_t pn = 10;
        };
    #endif

    #ifdef GPIOD_BASE
        template  <>
        struct GPIOPortTrait<GPIOPort::D> {
            static constexpr uint32_t addr = GPIOD_BASE;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::D, GPIOPin::_3> {
            static constexpr uint32_t pn = 3;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::D, GPIOPin::_6> {
            static constexpr uint32_t pn = 6;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::D, GPIOPin::_7> {
            static constexpr uint32_t pn = 7;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::D, GPIOPin::_13> {
            static constexpr uint32_t pn = 13;
        };
    #endif

    #ifdef GPIOE_BASE
        template  <>
        struct GPIOPortTrait<GPIOPort::E> {
            static constexpr uint32_t addr = GPIOE_BASE;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::E, GPIOPin::_4> {
            static constexpr uint32_t pn = 4;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::E, GPIOPin::_5> {
            static constexpr uint32_t pn = 5;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::E, GPIOPin::_6> {
            static constexpr uint32_t pn = 6;
        };
    #endif

    #ifdef GPIOF_BASE
        template  <>
        struct GPIOPortTrait<GPIOPort::F> {
            static constexpr uint32_t addr = GPIOF_BASE;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::F, GPIOPin::_7> {
            static constexpr uint32_t pn = 7;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::F, GPIOPin::_9> {
            static constexpr uint32_t pn = 9;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::F, GPIOPin::_10> {
            static constexpr uint32_t pn = 10;
        };
    #endif

    #ifdef GPIOG_BASE
        template  <>
        struct GPIOPortTrait<GPIOPort::G> {
            static constexpr uint32_t addr = GPIOG_BASE;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::G, GPIOPin::_6> {
            static constexpr uint32_t pn = 6;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::G, GPIOPin::_7> {
            static constexpr uint32_t pn = 7;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::G, GPIOPin::_9> {
            static constexpr uint32_t pn = 9;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::G, GPIOPin::_10> {
            static constexpr uint32_t pn = 10;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::G, GPIOPin::_11> {
            static constexpr uint32_t pn = 11;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::G, GPIOPin::_12> {
            static constexpr uint32_t pn = 12;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::G, GPIOPin::_13> {
            static constexpr uint32_t pn = 13;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::G, GPIOPin::_14> {
            static constexpr uint32_t pn = 14;
        };
    #endif

    #ifdef GPIOH_BASE
        template  <>
        struct GPIOPortTrait<GPIOPort::H> {
            static constexpr uint32_t addr = GPIOH_BASE;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::H, GPIOPin::_0> {
            static constexpr uint32_t pn = 0;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::H, GPIOPin::_1> {
            static constexpr uint32_t pn = 1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::H, GPIOPin::_2> {
            static constexpr uint32_t pn = 2;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::H, GPIOPin::_3> {
            static constexpr uint32_t pn = 3;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::H, GPIOPin::_4> {
            static constexpr uint32_t pn = 4;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::H, GPIOPin::_5> {
            static constexpr uint32_t pn = 5;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::H, GPIOPin::_6> {
            static constexpr uint32_t pn = 6;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::H, GPIOPin::_7> {
            static constexpr uint32_t pn = 7;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::H, GPIOPin::_8> {
            static constexpr uint32_t pn = 8;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::H, GPIOPin::_9> {
            static constexpr uint32_t pn = 9;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::H, GPIOPin::_10> {
            static constexpr uint32_t pn = 10;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::H, GPIOPin::_11> {
            static constexpr uint32_t pn = 11;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::H, GPIOPin::_12> {
            static constexpr uint32_t pn = 12;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::H, GPIOPin::_14> {
            static constexpr uint32_t pn = 14;
        };
    #endif

    #ifdef GPIOI_BASE
        template  <>
        struct GPIOPortTrait<GPIOPort::I> {
            static constexpr uint32_t addr = GPIOI_BASE;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::I, GPIOPin::_0> {
            static constexpr uint32_t pn = 0;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::I, GPIOPin::_1> {
            static constexpr uint32_t pn = 1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::I, GPIOPin::_2> {
            static constexpr uint32_t pn = 2;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::I, GPIOPin::_3> {
            static constexpr uint32_t pn = 3;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::I, GPIOPin::_4> {
            static constexpr uint32_t pn = 4;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::I, GPIOPin::_5> {
            static constexpr uint32_t pn = 5;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::I, GPIOPin::_6> {
            static constexpr uint32_t pn = 6;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::I, GPIOPin::_9> {
            static constexpr uint32_t pn = 9;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::I, GPIOPin::_10> {
            static constexpr uint32_t pn = 10;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::I, GPIOPin::_11> {
            static constexpr uint32_t pn = 11;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::I, GPIOPin::_12> {
            static constexpr uint32_t pn = 12;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::I, GPIOPin::_13> {
            static constexpr uint32_t pn = 13;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::I, GPIOPin::_14> {
            static constexpr uint32_t pn = 14;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::I, GPIOPin::_15> {
            static constexpr uint32_t pn = 15;
        };
    #endif

    #ifdef GPIOJ_BASE
        template  <>
        struct GPIOPortTrait<GPIOPort::J> {
            static constexpr uint32_t addr = GPIOJ_BASE;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::J, GPIOPin::_0> {
            static constexpr uint32_t pn = 0;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::J, GPIOPin::_1> {
            static constexpr uint32_t pn = 1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::J, GPIOPin::_2> {
            static constexpr uint32_t pn = 2;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::J, GPIOPin::_3> {
            static constexpr uint32_t pn = 3;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::J, GPIOPin::_4> {
            static constexpr uint32_t pn = 4;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::J, GPIOPin::_5> {
            static constexpr uint32_t pn = 5;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::J, GPIOPin::_6> {
            static constexpr uint32_t pn = 6;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::J, GPIOPin::_7> {
            static constexpr uint32_t pn = 7;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::J, GPIOPin::_8> {
            static constexpr uint32_t pn = 8;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::J, GPIOPin::_9> {
            static constexpr uint32_t pn = 9;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::J, GPIOPin::_10> {
            static constexpr uint32_t pn = 10;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::J, GPIOPin::_11> {
            static constexpr uint32_t pn = 11;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::J, GPIOPin::_13> {
            static constexpr uint32_t pn = 13;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::J, GPIOPin::_14> {
            static constexpr uint32_t pn = 14;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::J, GPIOPin::_15> {
            static constexpr uint32_t pn = 15;
        };
    #endif

    #ifdef GPIOK_BASE
        template  <>
        struct GPIOPortTrait<GPIOPort::K> {
            static constexpr uint32_t addr = GPIOK_BASE;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::K, GPIOPin::_0> {
            static constexpr uint32_t pn = 0;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::K, GPIOPin::_1> {
            static constexpr uint32_t pn = 1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::K, GPIOPin::_2> {
            static constexpr uint32_t pn = 2;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::K, GPIOPin::_3> {
            static constexpr uint32_t pn = 3;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::K, GPIOPin::_4> {
            static constexpr uint32_t pn = 4;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::K, GPIOPin::_5> {
            static constexpr uint32_t pn = 5;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::K, GPIOPin::_6> {
            static constexpr uint32_t pn = 6;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::K, GPIOPin::_7> {
            static constexpr uint32_t pn = 7;
        };
    #endif


	class GPIOAdapter final {
		private:
			GPIO_TypeDef *_regs;
			uint32_t _pn;

			GPIOAdapter(const GPIOAdapter &) = delete;
			GPIOAdapter(GPIOAdapter &&) = delete;

			GPIOAdapter operator = (const GPIOAdapter&) = delete;
			GPIOAdapter operator = (const GPIOAdapter&&) = delete;

		public:
			GPIOAdapter(
				uint32_t addr,
				uint32_t pn) :

				 _regs(reinterpret_cast<GPIO_TypeDef*>(addr)),
				 _pn(pn) {
			 }

			 inline void set() const {

				 _regs->BSRR = 1 << _pn;
			 }

			 inline void clear() const {

				 _regs->BSRR = 1 << (_pn + 16);
			 }

			 inline void toggle() const {

				 _regs->ODR ^= 1 << _pn;
			 }

			 inline void write(bool state) const {

				 if (state)
					 set();
				 else
					 clear();
			 }

			 inline bool read() const {

				 return _regs->IDR & (1 << _pn);
			 }
	};

	template <typename gpio_>
    const GPIOAdapter& getGPIOAdapter() {

        using PortTrait = GPIOPortTrait<gpio_::port>;
        using PinTrait = GPIOPinTrait<gpio_::port, gpio_::pin>;

        static GPIOAdapter adapter(PortTrait::addr, PinTrait::pn);

        return adapter;
    }
}


#endif // __STM32_htlGPIO__

/// @}
/// @}
/// @}

