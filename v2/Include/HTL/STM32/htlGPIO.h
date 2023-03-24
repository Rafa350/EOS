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
    enum class GPIOPortId {
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
            G,
        #endif
        #ifdef HTL_GPIOH_EXIST
            H,
        #endif
        #ifdef HTL_GPIOI_EXIST
            I,
        #endif
        #ifdef HTL_GPIOJ_EXIST
            J,
        #endif
        #ifdef HTL_GPIOK_EXIST
            K,
        #endif
    };

    /// \brief Pin identifiers.
    enum class GPIOPinId {
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

    /// \brief Driver type identifier.
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

    enum class GPIOInitState {
    	noChange,
		clear,
		set
    };

    enum class GPIOState {
		clear,
    	set
    };

    template <GPIOPortId>
    struct GPIOPortTrait {
    };

    template <GPIOPortId, GPIOPinId>
    struct GPIOPinTrait {
    };

    template <GPIOPortId portId_>
    class GPIOPortActivator final {
    	private:
    		using PortTrait = GPIOPortTrait<portId_>;
    		static constexpr uint32_t en_addr = PortTrait::en_addr;
    		static constexpr uint32_t en_bit = PortTrait::en_bit;
    		static uint16_t _activated;

    	public:
    		static void activate(
    			uint16_t mask) {

    			if (!_activated) {
					uint32_t *p = reinterpret_cast<uint32_t*>(en_addr);
					*p |= 1 << en_bit;
    				__DSB();
    			}
    			_activated |= mask;
    		}

    		static void deactivate(
    			uint16_t mask) {

    			_activated &= ~mask;
    			if (!_activated) {
					uint32_t *p = reinterpret_cast<uint32_t*>(en_addr);
					*p &= ~(1 << en_bit);
    			}
    		}
    };

    template <GPIOPortId portId_> uint16_t GPIOPortActivator<portId_>::_activated = 0;
    
    
    /// \class GPIOPortBase_x
    /// \brief Base class for gpio port.
    ///
    class GPIOPortBase_x {
        protected:
            static void initInput(GPIO_TypeDef *regs, uint16_t mask, GPIOPull pull);
            static void initOutput(GPIO_TypeDef *regs, uint16_t mask, GPIODriver driver, GPIOSpeed speed);
    };
    
    /// \class GPIOPort_x
    /// \brief Class form gpio port.
    ///
    template <GPIOPortId portId_>
    class GPIOPort_x final: public GPIOPortBase_x {
        private:
            using PortTrait = GPIOPortTrait<portId_>;
            using Activator = GPIOPortActivator<portId_>;
            static constexpr uint32_t _addr = PortTrait::addr;

        public:
            static constexpr GPIOPortId port = portId_;
            
        public:
            /// \brief Initialize port as inputs.
            /// \param mask: Pin mask.
            /// \param pull: Pull up/down options
            ///
            static void initInput(
                uint16_t mask,
            	GPIOPull pull = GPIOPull::none) {

            	Activator::activate(mask);
            	GPIOPortBase_x::initInput(
                    reinterpret_cast<GPIO_TypeDef*>(_addr), 
                    mask,
                    pull);
            }

            /// \brief Initialize port as outputs.
            /// \param mask: Pin mask.
            /// \param driver: Driver options.
            /// \param speed: Speed options.
            ///
            static void initOutput(
                uint16_t mask,
            	GPIODriver driver,
				GPIOSpeed speed = GPIOSpeed::medium,
				GPIOInitState state = GPIOInitState::noChange) {

            	Activator::activate(mask);
                GPIOPortBase_x::initOutput(
                    reinterpret_cast<GPIO_TypeDef*>(_addr),
                    mask,
                    driver,
                    speed);
            }

            /// \brief Set pins to set state
            /// \param mask: Pin mask.
            ///
            static void set(uint16_t mask) {
                GPIO_TypeDef *regs = reinterpret_cast<GPIO_TypeDef*>(_addr);
                regs->BSRR = mask;
            }

            /// \brief Set pins to clear state
            /// \param mask: Pin mask.
            ///
            static void clear(uint16_t mask) {
                GPIO_TypeDef *regs = reinterpret_cast<GPIO_TypeDef*>(_addr);
                regs->BSRR = mask << 16;
            }

            /// \brief Toggle pin state
            /// \param mask: Pin mask.
            ///
            static void toggle(uint16_t mask) {
                GPIO_TypeDef *regs = reinterpret_cast<GPIO_TypeDef*>(_addr);
                regs->ODR ^= mask;
            }
    };


    /// \class GPIOBase_x
    /// \brief Base class for gpio pins
    ///
    class GPIOBase_x {
    	protected:
			static void initInput(GPIO_TypeDef *regs, uint32_t pn, GPIOPull pull);
			static void initOutput(GPIO_TypeDef *regs, uint32_t pn, GPIODriver driver, GPIOSpeed speed);
			static void initAlt(GPIO_TypeDef *regs, uint32_t pn, GPIODriver driver, GPIOSpeed speed, GPIOAlt alt);
            static void initAnalogic(GPIO_TypeDef *regs, uint32_t pn);
    };

    /// \class GPIO_x
    /// \brief Class for gpio pins
    ///
    template <GPIOPortId portId_, GPIOPinId pinId_>
    class GPIO_x final: public GPIOBase_x {
        private:
            using PortTrait = GPIOPortTrait<portId_>;
            using PinTrait = GPIOPinTrait<portId_, pinId_>;
            using Activator = GPIOPortActivator<portId_>;
            static constexpr uint32_t _addr = PortTrait::addr;
            static constexpr uint32_t _pn = PinTrait::pn;

        public:
            static constexpr GPIOPortId port = portId_;
            static constexpr GPIOPinId pin = pinId_;

        private:
            GPIO_x() = delete;
            GPIO_x(const GPIO_x &) = delete;
            GPIO_x(const GPIO_x &&) = delete;
            ~GPIO_x() = delete;

            GPIO_x & operator = (const GPIO_x &) = delete;
            GPIO_x & operator = (const GPIO_x &&) = delete;

        public:
            /// \brief Inicialitza el pin com entrada.
            /// \param pull: Opcions de pull up/down
            ///
            static void initInput(
            	GPIOPull pull = GPIOPull::none) {

            	Activator::activate(1 << _pn);
            	GPIOBase_x::initInput(
                    reinterpret_cast<GPIO_TypeDef*>(_addr), 
                    _pn,
                    pull);
            }

            /// \brief Inicialitza el pin com a sortida.
            /// \param driver: Opcions de driver
            /// \param speed: Opcions de velocitat.
            ///
            static void initOutput(
            	GPIODriver driver,
				GPIOSpeed speed = GPIOSpeed::medium,
				GPIOInitState state = GPIOInitState::noChange) {

            	Activator::activate(1 << _pn);

                GPIO_TypeDef *regs = reinterpret_cast<GPIO_TypeDef*>(_addr);

                if (state != GPIOInitState::noChange)
                	regs->BSRR = 1 << (_pn + (state == GPIOInitState::set ? 0 : 16));

                GPIOBase_x::initOutput(
                    regs,
                    _pn,
                    driver,
                    speed);
            }

             /// \brief Inicialitza el pin com a funcio alternativa.
             /// \param driver: Opcions del driver.
             /// \param speed: Opcions de velocitat.
             /// \param alt: Funcio del pin.
             ///
            static void initAlt(
            	GPIODriver driver,
				GPIOSpeed speed,
				GPIOAlt alt) {
                
            	Activator::activate(1 << _pn);
            	GPIOBase_x::initAlt(
                    reinterpret_cast<GPIO_TypeDef*>(_addr),
                    _pn,
                    driver,
                    speed,
					alt);
            }
            
            /// \brief Inicialitza el pin com entrada/sortida analogica.
            ///
            static void initAnalogic() {

            	Activator::activate(1 << _pn);
            	GPIOBase_x::initAnalogic(
                    reinterpret_cast<GPIO_TypeDef*>(_addr),
                    _pn);
            }

            /// \brief Desinicialitza el pin.
            ///
            static void deinitialize() {

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
            inline static GPIOState read() {

                GPIO_TypeDef *regs = reinterpret_cast<GPIO_TypeDef*>(_addr);
                return ((regs->IDR & (1 << _pn)) == 0) ? GPIOState::clear : GPIOState::set;
            }

            /// \brief Write pin state.
            /// \param state: State to write.
            ///
            inline static void write(
            	GPIOState state) {

                GPIO_TypeDef *regs = reinterpret_cast<GPIO_TypeDef*>(_addr);
                regs->BSRR = 1 << (_pn + (state == GPIOState::set ? 0 : 16));
            }
    };

    #ifdef HTL_GPIOA_EXIST
        using GPIO_A = GPIOPort_x<GPIOPortId::A>;
        typedef GPIO_x<GPIOPortId::A, GPIOPinId::_0> GPIO_A0;
        typedef GPIO_x<GPIOPortId::A, GPIOPinId::_1> GPIO_A1;
        typedef GPIO_x<GPIOPortId::A, GPIOPinId::_2> GPIO_A2;
        typedef GPIO_x<GPIOPortId::A, GPIOPinId::_3> GPIO_A3;
        typedef GPIO_x<GPIOPortId::A, GPIOPinId::_4> GPIO_A4;
        typedef GPIO_x<GPIOPortId::A, GPIOPinId::_5> GPIO_A5;
        typedef GPIO_x<GPIOPortId::A, GPIOPinId::_6> GPIO_A6;
        typedef GPIO_x<GPIOPortId::A, GPIOPinId::_7> GPIO_A7;
        typedef GPIO_x<GPIOPortId::A, GPIOPinId::_8> GPIO_A8;
        typedef GPIO_x<GPIOPortId::A, GPIOPinId::_9> GPIO_A9;
        typedef GPIO_x<GPIOPortId::A, GPIOPinId::_10> GPIO_A10;
        typedef GPIO_x<GPIOPortId::A, GPIOPinId::_11> GPIO_A11;
        typedef GPIO_x<GPIOPortId::A, GPIOPinId::_12> GPIO_A12;
        typedef GPIO_x<GPIOPortId::A, GPIOPinId::_13> GPIO_A13;
        typedef GPIO_x<GPIOPortId::A, GPIOPinId::_14> GPIO_A14;
        typedef GPIO_x<GPIOPortId::A, GPIOPinId::_15> GPIO_A15;
    #endif

    #ifdef HTL_GPIOB_EXIST
        using GPIO_B = GPIOPort_x<GPIOPortId::B>;
        typedef GPIO_x<GPIOPortId::B, GPIOPinId::_0> GPIO_B0;
        typedef GPIO_x<GPIOPortId::B, GPIOPinId::_1> GPIO_B1;
        typedef GPIO_x<GPIOPortId::B, GPIOPinId::_2> GPIO_B2;
        typedef GPIO_x<GPIOPortId::B, GPIOPinId::_3> GPIO_B3;
        typedef GPIO_x<GPIOPortId::B, GPIOPinId::_4> GPIO_B4;
        typedef GPIO_x<GPIOPortId::B, GPIOPinId::_5> GPIO_B5;
        typedef GPIO_x<GPIOPortId::B, GPIOPinId::_6> GPIO_B6;
        typedef GPIO_x<GPIOPortId::B, GPIOPinId::_7> GPIO_B7;
        typedef GPIO_x<GPIOPortId::B, GPIOPinId::_8> GPIO_B8;
        typedef GPIO_x<GPIOPortId::B, GPIOPinId::_9> GPIO_B9;
        typedef GPIO_x<GPIOPortId::B, GPIOPinId::_10> GPIO_B10;
        typedef GPIO_x<GPIOPortId::B, GPIOPinId::_11> GPIO_B11;
        typedef GPIO_x<GPIOPortId::B, GPIOPinId::_12> GPIO_B12;
        typedef GPIO_x<GPIOPortId::B, GPIOPinId::_13> GPIO_B13;
        typedef GPIO_x<GPIOPortId::B, GPIOPinId::_14> GPIO_B14;
        typedef GPIO_x<GPIOPortId::B, GPIOPinId::_15> GPIO_B15;
    #endif

    #ifdef HTL_GPIOC_EXIST
        using GPIO_C = GPIOPort_x<GPIOPortId::C>;
        typedef GPIO_x<GPIOPortId::C, GPIOPinId::_0> GPIO_C0;
        typedef GPIO_x<GPIOPortId::C, GPIOPinId::_1> GPIO_C1;
        typedef GPIO_x<GPIOPortId::C, GPIOPinId::_2> GPIO_C2;
        typedef GPIO_x<GPIOPortId::C, GPIOPinId::_3> GPIO_C3;
        typedef GPIO_x<GPIOPortId::C, GPIOPinId::_4> GPIO_C4;
        typedef GPIO_x<GPIOPortId::C, GPIOPinId::_5> GPIO_C5;
        typedef GPIO_x<GPIOPortId::C, GPIOPinId::_6> GPIO_C6;
        typedef GPIO_x<GPIOPortId::C, GPIOPinId::_7> GPIO_C7;
        typedef GPIO_x<GPIOPortId::C, GPIOPinId::_8> GPIO_C8;
        typedef GPIO_x<GPIOPortId::C, GPIOPinId::_9> GPIO_C9;
        typedef GPIO_x<GPIOPortId::C, GPIOPinId::_10> GPIO_C10;
        typedef GPIO_x<GPIOPortId::C, GPIOPinId::_11> GPIO_C11;
        typedef GPIO_x<GPIOPortId::C, GPIOPinId::_12> GPIO_C12;
        typedef GPIO_x<GPIOPortId::C, GPIOPinId::_13> GPIO_C13;
        typedef GPIO_x<GPIOPortId::C, GPIOPinId::_14> GPIO_C14;
        typedef GPIO_x<GPIOPortId::C, GPIOPinId::_15> GPIO_C15;
    #endif

    #ifdef HTL_GPIOD_EXIST
        using GPIO_D = GPIOPort_x<GPIOPortId::D>;
        typedef GPIO_x<GPIOPortId::D, GPIOPinId::_0> GPIO_D0;
        typedef GPIO_x<GPIOPortId::D, GPIOPinId::_1> GPIO_D1;
        typedef GPIO_x<GPIOPortId::D, GPIOPinId::_2> GPIO_D2;
        typedef GPIO_x<GPIOPortId::D, GPIOPinId::_3> GPIO_D3;
        typedef GPIO_x<GPIOPortId::D, GPIOPinId::_4> GPIO_D4;
        typedef GPIO_x<GPIOPortId::D, GPIOPinId::_5> GPIO_D5;
        typedef GPIO_x<GPIOPortId::D, GPIOPinId::_6> GPIO_D6;
        typedef GPIO_x<GPIOPortId::D, GPIOPinId::_7> GPIO_D7;
        typedef GPIO_x<GPIOPortId::D, GPIOPinId::_8> GPIO_D8;
        typedef GPIO_x<GPIOPortId::D, GPIOPinId::_9> GPIO_D9;
        typedef GPIO_x<GPIOPortId::D, GPIOPinId::_10> GPIO_D10;
        typedef GPIO_x<GPIOPortId::D, GPIOPinId::_11> GPIO_D11;
        typedef GPIO_x<GPIOPortId::D, GPIOPinId::_12> GPIO_D12;
        typedef GPIO_x<GPIOPortId::D, GPIOPinId::_13> GPIO_D13;
        typedef GPIO_x<GPIOPortId::D, GPIOPinId::_14> GPIO_D14;
        typedef GPIO_x<GPIOPortId::D, GPIOPinId::_15> GPIO_D15;
    #endif

    #ifdef HTL_GPIOE_EXIST
        using GPIO_E = GPIOPort_x<GPIOPortId::E>;
        typedef GPIO_x<GPIOPortId::E, GPIOPinId::_0> GPIO_E0;
        typedef GPIO_x<GPIOPortId::E, GPIOPinId::_1> GPIO_E1;
        typedef GPIO_x<GPIOPortId::E, GPIOPinId::_2> GPIO_E2;
        typedef GPIO_x<GPIOPortId::E, GPIOPinId::_3> GPIO_E3;
        typedef GPIO_x<GPIOPortId::E, GPIOPinId::_4> GPIO_E4;
        typedef GPIO_x<GPIOPortId::E, GPIOPinId::_5> GPIO_E5;
        typedef GPIO_x<GPIOPortId::E, GPIOPinId::_6> GPIO_E6;
        typedef GPIO_x<GPIOPortId::E, GPIOPinId::_7> GPIO_E7;
        typedef GPIO_x<GPIOPortId::E, GPIOPinId::_8> GPIO_E8;
        typedef GPIO_x<GPIOPortId::E, GPIOPinId::_9> GPIO_E9;
        typedef GPIO_x<GPIOPortId::E, GPIOPinId::_10> GPIO_E10;
        typedef GPIO_x<GPIOPortId::E, GPIOPinId::_11> GPIO_E11;
        typedef GPIO_x<GPIOPortId::E, GPIOPinId::_12> GPIO_E12;
        typedef GPIO_x<GPIOPortId::E, GPIOPinId::_13> GPIO_E13;
        typedef GPIO_x<GPIOPortId::E, GPIOPinId::_14> GPIO_E14;
        typedef GPIO_x<GPIOPortId::E, GPIOPinId::_15> GPIO_E15;
    #endif

    #ifdef HTL_GPIOF_EXIST
        using GPIO_F = GPIOPort_x<GPIOPortId::F>;
        typedef GPIO_x<GPIOPortId::F, GPIOPinId::_0> GPIO_F0;
        typedef GPIO_x<GPIOPortId::F, GPIOPinId::_1> GPIO_F1;
        typedef GPIO_x<GPIOPortId::F, GPIOPinId::_2> GPIO_F2;
        typedef GPIO_x<GPIOPortId::F, GPIOPinId::_3> GPIO_F3;
        typedef GPIO_x<GPIOPortId::F, GPIOPinId::_4> GPIO_F4;
        typedef GPIO_x<GPIOPortId::F, GPIOPinId::_5> GPIO_F5;
        typedef GPIO_x<GPIOPortId::F, GPIOPinId::_6> GPIO_F6;
        typedef GPIO_x<GPIOPortId::F, GPIOPinId::_7> GPIO_F7;
        typedef GPIO_x<GPIOPortId::F, GPIOPinId::_8> GPIO_F8;
        typedef GPIO_x<GPIOPortId::F, GPIOPinId::_9> GPIO_F9;
        typedef GPIO_x<GPIOPortId::F, GPIOPinId::_10> GPIO_F10;
        typedef GPIO_x<GPIOPortId::F, GPIOPinId::_11> GPIO_F11;
        typedef GPIO_x<GPIOPortId::F, GPIOPinId::_12> GPIO_F12;
        typedef GPIO_x<GPIOPortId::F, GPIOPinId::_13> GPIO_F13;
        typedef GPIO_x<GPIOPortId::F, GPIOPinId::_14> GPIO_F14;
        typedef GPIO_x<GPIOPortId::F, GPIOPinId::_15> GPIO_F15;
    #endif

    #ifdef HTL_GPIOG_EXIST
        using GPIO_G = GPIOPort_x<GPIOPortId::G>;
        typedef GPIO_x<GPIOPortId::G, GPIOPinId::_0> GPIO_G0;
        typedef GPIO_x<GPIOPortId::G, GPIOPinId::_1> GPIO_G1;
        typedef GPIO_x<GPIOPortId::G, GPIOPinId::_2> GPIO_G2;
        typedef GPIO_x<GPIOPortId::G, GPIOPinId::_3> GPIO_G3;
        typedef GPIO_x<GPIOPortId::G, GPIOPinId::_4> GPIO_G4;
        typedef GPIO_x<GPIOPortId::G, GPIOPinId::_5> GPIO_G5;
        typedef GPIO_x<GPIOPortId::G, GPIOPinId::_6> GPIO_G6;
        typedef GPIO_x<GPIOPortId::G, GPIOPinId::_7> GPIO_G7;
        typedef GPIO_x<GPIOPortId::G, GPIOPinId::_8> GPIO_G8;
        typedef GPIO_x<GPIOPortId::G, GPIOPinId::_9> GPIO_G9;
        typedef GPIO_x<GPIOPortId::G, GPIOPinId::_10> GPIO_G10;
        typedef GPIO_x<GPIOPortId::G, GPIOPinId::_11> GPIO_G11;
        typedef GPIO_x<GPIOPortId::G, GPIOPinId::_12> GPIO_G12;
        typedef GPIO_x<GPIOPortId::G, GPIOPinId::_13> GPIO_G13;
        typedef GPIO_x<GPIOPortId::G, GPIOPinId::_14> GPIO_G14;
        typedef GPIO_x<GPIOPortId::G, GPIOPinId::_15> GPIO_G15;
    #endif

    #ifdef HTL_GPIOH_EXIST
        using GPIO_H = GPIOPort_x<GPIOPortId::H>;
        typedef GPIO_x<GPIOPortId::H, GPIOPinId::_0> GPIO_H0;
        typedef GPIO_x<GPIOPortId::H, GPIOPinId::_1> GPIO_H1;
        typedef GPIO_x<GPIOPortId::H, GPIOPinId::_2> GPIO_H2;
        typedef GPIO_x<GPIOPortId::H, GPIOPinId::_3> GPIO_H3;
        typedef GPIO_x<GPIOPortId::H, GPIOPinId::_4> GPIO_H4;
        typedef GPIO_x<GPIOPortId::H, GPIOPinId::_5> GPIO_H5;
        typedef GPIO_x<GPIOPortId::H, GPIOPinId::_6> GPIO_H6;
        typedef GPIO_x<GPIOPortId::H, GPIOPinId::_7> GPIO_H7;
        typedef GPIO_x<GPIOPortId::H, GPIOPinId::_8> GPIO_H8;
        typedef GPIO_x<GPIOPortId::H, GPIOPinId::_9> GPIO_H9;
        typedef GPIO_x<GPIOPortId::H, GPIOPinId::_10> GPIO_H10;
        typedef GPIO_x<GPIOPortId::H, GPIOPinId::_11> GPIO_H11;
        typedef GPIO_x<GPIOPortId::H, GPIOPinId::_12> GPIO_H12;
        typedef GPIO_x<GPIOPortId::H, GPIOPinId::_13> GPIO_H13;
        typedef GPIO_x<GPIOPortId::H, GPIOPinId::_14> GPIO_H14;
        typedef GPIO_x<GPIOPortId::H, GPIOPinId::_15> GPIO_H15;
    #endif

    #ifdef HTL_GPIOI_EXIST
        using GPIO_I = GPIOPort_x<GPIOPortId::I>;
        typedef GPIO_x<GPIOPortId::I, GPIOPinId::_0> GPIO_I0;
        typedef GPIO_x<GPIOPortId::I, GPIOPinId::_1> GPIO_I1;
        typedef GPIO_x<GPIOPortId::I, GPIOPinId::_2> GPIO_I2;
        typedef GPIO_x<GPIOPortId::I, GPIOPinId::_3> GPIO_I3;
        typedef GPIO_x<GPIOPortId::I, GPIOPinId::_4> GPIO_I4;
        typedef GPIO_x<GPIOPortId::I, GPIOPinId::_5> GPIO_I5;
        typedef GPIO_x<GPIOPortId::I, GPIOPinId::_6> GPIO_I6;
        typedef GPIO_x<GPIOPortId::I, GPIOPinId::_7> GPIO_I7;
        typedef GPIO_x<GPIOPortId::I, GPIOPinId::_8> GPIO_I8;
        typedef GPIO_x<GPIOPortId::I, GPIOPinId::_9> GPIO_I9;
        typedef GPIO_x<GPIOPortId::I, GPIOPinId::_10> GPIO_I10;
        typedef GPIO_x<GPIOPortId::I, GPIOPinId::_11> GPIO_I11;
        typedef GPIO_x<GPIOPortId::I, GPIOPinId::_12> GPIO_I12;
        typedef GPIO_x<GPIOPortId::I, GPIOPinId::_13> GPIO_I13;
        typedef GPIO_x<GPIOPortId::I, GPIOPinId::_14> GPIO_I14;
        typedef GPIO_x<GPIOPortId::I, GPIOPinId::_15> GPIO_I15;
    #endif

    #ifdef HTL_GPIOJ_EXIST
        using GPIO_J = GPIOPort_x<GPIOPortId::J>;
        typedef GPIO_x<GPIOPortId::J, GPIOPinId::_0> GPIO_J0;
        typedef GPIO_x<GPIOPortId::J, GPIOPinId::_1> GPIO_J1;
        typedef GPIO_x<GPIOPortId::J, GPIOPinId::_2> GPIO_J2;
        typedef GPIO_x<GPIOPortId::J, GPIOPinId::_3> GPIO_J3;
        typedef GPIO_x<GPIOPortId::J, GPIOPinId::_4> GPIO_J4;
        typedef GPIO_x<GPIOPortId::J, GPIOPinId::_5> GPIO_J5;
        typedef GPIO_x<GPIOPortId::J, GPIOPinId::_6> GPIO_J6;
        typedef GPIO_x<GPIOPortId::J, GPIOPinId::_7> GPIO_J7;
        typedef GPIO_x<GPIOPortId::J, GPIOPinId::_8> GPIO_J8;
        typedef GPIO_x<GPIOPortId::J, GPIOPinId::_9> GPIO_J9;
        typedef GPIO_x<GPIOPortId::J, GPIOPinId::_10> GPIO_J10;
        typedef GPIO_x<GPIOPortId::J, GPIOPinId::_11> GPIO_J11;
        typedef GPIO_x<GPIOPortId::J, GPIOPinId::_12> GPIO_J12;
        typedef GPIO_x<GPIOPortId::J, GPIOPinId::_13> GPIO_J13;
        typedef GPIO_x<GPIOPortId::J, GPIOPinId::_14> GPIO_J14;
        typedef GPIO_x<GPIOPortId::J, GPIOPinId::_15> GPIO_J15;
    #endif

    #ifdef HTL_GPIOK_EXIST
        using GPIO_K = GPIOPort_x<GPIOPortId::K>;
        typedef GPIO_x<GPIOPortId::K, GPIOPinId::_0> GPIO_K0;
        typedef GPIO_x<GPIOPortId::K, GPIOPinId::_1> GPIO_K1;
        typedef GPIO_x<GPIOPortId::K, GPIOPinId::_2> GPIO_K2;
        typedef GPIO_x<GPIOPortId::K, GPIOPinId::_3> GPIO_K3;
        typedef GPIO_x<GPIOPortId::K, GPIOPinId::_4> GPIO_K4;
        typedef GPIO_x<GPIOPortId::K, GPIOPinId::_5> GPIO_K5;
        typedef GPIO_x<GPIOPortId::K, GPIOPinId::_6> GPIO_K6;
        typedef GPIO_x<GPIOPortId::K, GPIOPinId::_7> GPIO_K7;
        typedef GPIO_x<GPIOPortId::K, GPIOPinId::_8> GPIO_K8;
        typedef GPIO_x<GPIOPortId::K, GPIOPinId::_9> GPIO_K9;
        typedef GPIO_x<GPIOPortId::K, GPIOPinId::_10> GPIO_K10;
        typedef GPIO_x<GPIOPortId::K, GPIOPinId::_11> GPIO_K11;
        typedef GPIO_x<GPIOPortId::K, GPIOPinId::_12> GPIO_K12;
        typedef GPIO_x<GPIOPortId::K, GPIOPinId::_13> GPIO_K13;
        typedef GPIO_x<GPIOPortId::K, GPIOPinId::_14> GPIO_K14;
        typedef GPIO_x<GPIOPortId::K, GPIOPinId::_15> GPIO_K15;
    #endif


    #ifdef HTL_GPIOA_EXIST
        template<>
        struct GPIOPortTrait<GPIOPortId::A> {
            static constexpr uint32_t addr = GPIOA_BASE;
				#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
					static constexpr uint32_t en_addr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
					static constexpr uint32_t en_bit = RCC_AHB1ENR_GPIOAEN_Pos;
				#elif defined(EOS_PLATFORM_STM32G0)
					static constexpr uint32_t en_addr = RCC_BASE + offsetof(RCC_TypeDef, IOPENR);
					static constexpr uint32_t en_bit = RCC_IOPENR_GPIOAEN_Pos;
				#endif
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::A, GPIOPinId::_0> {
            static constexpr uint32_t pn = 0;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::A, GPIOPinId::_1> {
            static constexpr uint32_t pn = 1;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::A, GPIOPinId::_2> {
            static constexpr uint32_t pn = 2;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::A, GPIOPinId::_3> {
            static constexpr uint32_t pn = 3;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::A, GPIOPinId::_4> {
            static constexpr uint32_t pn = 4;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::A, GPIOPinId::_5> {
            static constexpr uint32_t pn = 5;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::A, GPIOPinId::_6> {
            static constexpr uint32_t pn = 6;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::A, GPIOPinId::_7> {
            static constexpr uint32_t pn = 7;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::A, GPIOPinId::_8> {
            static constexpr uint32_t pn = 8;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::A, GPIOPinId::_9> {
            static constexpr uint32_t pn = 9;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::A, GPIOPinId::_10> {
            static constexpr uint32_t pn = 10;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::A, GPIOPinId::_11> {
            static constexpr uint32_t pn = 11;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::A, GPIOPinId::_12> {
            static constexpr uint32_t pn = 12;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::A, GPIOPinId::_13> {
            static constexpr uint32_t pn = 13;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::A, GPIOPinId::_14> {
            static constexpr uint32_t pn = 14;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::A, GPIOPinId::_15> {
            static constexpr uint32_t pn = 15;
        };
    #endif

    #ifdef HTL_GPIOB_EXIST
        template  <>
        struct GPIOPortTrait<GPIOPortId::B> {
            static constexpr uint32_t addr = GPIOB_BASE;
			#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
            	static constexpr uint32_t en_addr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
            	static constexpr uint32_t en_bit = RCC_AHB1ENR_GPIOBEN_Pos;
			#elif defined(EOS_PLATFORM_STM32G0)
            	static constexpr uint32_t en_addr = RCC_BASE + offsetof(RCC_TypeDef, IOPENR);
            	static constexpr uint32_t en_bit = RCC_IOPENR_GPIOBEN_Pos;
			#endif
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::B, GPIOPinId::_0> {
            static constexpr uint32_t pn = 0;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::B, GPIOPinId::_1> {
            static constexpr uint32_t pn = 1;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::B, GPIOPinId::_2> {
            static constexpr uint32_t pn = 2;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::B, GPIOPinId::_3> {
            static constexpr uint32_t pn = 3;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::B, GPIOPinId::_4> {
            static constexpr uint32_t pn = 4;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::B, GPIOPinId::_5> {
            static constexpr uint32_t pn = 5;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::B, GPIOPinId::_6> {
            static constexpr uint32_t pn = 6;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::B, GPIOPinId::_7> {
            static constexpr uint32_t pn = 7;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::B, GPIOPinId::_8> {
            static constexpr uint32_t pn = 8;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::B, GPIOPinId::_9> {
            static constexpr uint32_t pn = 9;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::B, GPIOPinId::_10> {
            static constexpr uint32_t pn = 10;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::B, GPIOPinId::_11> {
            static constexpr uint32_t pn = 11;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::B, GPIOPinId::_12> {
            static constexpr uint32_t pn = 12;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::B, GPIOPinId::_13> {
            static constexpr uint32_t pn = 13;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::B, GPIOPinId::_14> {
            static constexpr uint32_t pn = 14;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::B, GPIOPinId::_15> {
            static constexpr uint32_t pn = 15;
        };
    #endif

    #ifdef HTL_GPIOC_EXIST
        template  <>
        struct GPIOPortTrait<GPIOPortId::C> {
            static constexpr uint32_t addr = GPIOC_BASE;
			#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
            	static constexpr uint32_t en_addr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
            	static constexpr uint32_t en_bit = RCC_AHB1ENR_GPIOBEN_Pos;
			#elif defined(EOS_PLATFORM_STM32G0)
            	static constexpr uint32_t en_addr = RCC_BASE + offsetof(RCC_TypeDef, IOPENR);
            	static constexpr uint32_t en_bit = RCC_IOPENR_GPIOCEN_Pos;
			#endif
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::C, GPIOPinId::_0> {
            static constexpr uint32_t pn = 0;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::C, GPIOPinId::_1> {
            static constexpr uint32_t pn = 1;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::C, GPIOPinId::_2> {
            static constexpr uint32_t pn = 2;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::C, GPIOPinId::_3> {
            static constexpr uint32_t pn = 3;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::C, GPIOPinId::_4> {
            static constexpr uint32_t pn = 4;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::C, GPIOPinId::_5> {
            static constexpr uint32_t pn = 5;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::C, GPIOPinId::_6> {
            static constexpr uint32_t pn = 6;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::C, GPIOPinId::_7> {
            static constexpr uint32_t pn = 7;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::C, GPIOPinId::_8> {
            static constexpr uint32_t pn = 8;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::C, GPIOPinId::_9> {
            static constexpr uint32_t pn = 9;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::C, GPIOPinId::_10> {
            static constexpr uint32_t pn = 10;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::C, GPIOPinId::_11> {
            static constexpr uint32_t pn = 11;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::C, GPIOPinId::_12> {
            static constexpr uint32_t pn = 12;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::C, GPIOPinId::_13> {
            static constexpr uint32_t pn = 13;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::C, GPIOPinId::_14> {
            static constexpr uint32_t pn = 14;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::C, GPIOPinId::_15> {
            static constexpr uint32_t pn = 15;
        };
    #endif

    #ifdef HTL_GPIOD_EXIST
        template  <>
        struct GPIOPortTrait<GPIOPortId::D> {
            static constexpr uint32_t addr = GPIOD_BASE;
			#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
            	static constexpr uint32_t en_addr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
            	static constexpr uint32_t en_bit = RCC_AHB1ENR_GPIODEN_Pos;
			#elif defined(EOS_PLATFORM_STM32G0)
            	static constexpr uint32_t en_addr = RCC_BASE + offsetof(RCC_TypeDef, IOPENR);
            	static constexpr uint32_t en_bit = RCC_IOPENR_GPIODEN_Pos;
			#endif
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::D, GPIOPinId::_0> {
            static constexpr uint32_t pn = 0;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::D, GPIOPinId::_1> {
            static constexpr uint32_t pn = 1;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::D, GPIOPinId::_2> {
            static constexpr uint32_t pn = 2;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::D, GPIOPinId::_3> {
            static constexpr uint32_t pn = 3;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::D, GPIOPinId::_6> {
            static constexpr uint32_t pn = 6;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::D, GPIOPinId::_7> {
            static constexpr uint32_t pn = 7;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::D, GPIOPinId::_11> {
            static constexpr uint32_t pn = 11;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::D, GPIOPinId::_12> {
            static constexpr uint32_t pn = 12;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::D, GPIOPinId::_13> {
            static constexpr uint32_t pn = 13;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::D, GPIOPinId::_14> {
            static constexpr uint32_t pn = 14;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::D, GPIOPinId::_15> {
            static constexpr uint32_t pn = 15;
        };
    #endif

    #ifdef HTL_GPIOE_EXIST
        template  <>
        struct GPIOPortTrait<GPIOPortId::E> {
            static constexpr uint32_t addr = GPIOE_BASE;
			#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t en_addr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
				static constexpr uint32_t en_bit = RCC_AHB1ENR_GPIOEEN_Pos;
			#elif defined(EOS_PLATFORM_STM32G0)
				static constexpr uint32_t en_addr = RCC_BASE + offsetof(RCC_TypeDef, IOPENR);
				static constexpr uint32_t en_bit = RCC_IOPENR_GPIOEEN_Pos;
			#endif
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::E, GPIOPinId::_4> {
            static constexpr uint32_t pn = 4;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::E, GPIOPinId::_5> {
            static constexpr uint32_t pn = 5;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::E, GPIOPinId::_6> {
            static constexpr uint32_t pn = 6;
        };
    #endif

    #ifdef HTL_GPIOF_EXIST
        template  <>
        struct GPIOPortTrait<GPIOPortId::F> {
            static constexpr uint32_t addr = GPIOF_BASE;
			#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
            	static constexpr uint32_t en_addr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
            	static constexpr uint32_t en_bit = RCC_AHB1ENR_GPIOFEN_Pos;
			#elif defined(EOS_PLATFORM_STM32G0)
            	static constexpr uint32_t en_addr = RCC_BASE + offsetof(RCC_TypeDef, IOPENR);
            	static constexpr uint32_t en_bit = RCC_IOPENR_GPIOFEN_Pos;
			#endif
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::F, GPIOPinId::_0> {
            static constexpr uint32_t pn = 0;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::F, GPIOPinId::_1> {
            static constexpr uint32_t pn = 1;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::F, GPIOPinId::_2> {
            static constexpr uint32_t pn = 2;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::F, GPIOPinId::_3> {
            static constexpr uint32_t pn = 3;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::F, GPIOPinId::_4> {
            static constexpr uint32_t pn = 4;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::F, GPIOPinId::_5> {
            static constexpr uint32_t pn = 5;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::F, GPIOPinId::_6> {
            static constexpr uint32_t pn = 6;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::F, GPIOPinId::_7> {
            static constexpr uint32_t pn = 7;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::F, GPIOPinId::_8> {
            static constexpr uint32_t pn = 8;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::F, GPIOPinId::_9> {
            static constexpr uint32_t pn = 9;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::F, GPIOPinId::_10> {
            static constexpr uint32_t pn = 10;
        };
    #endif

    #ifdef HTL_GPIOG_EXIST
        template  <>
        struct GPIOPortTrait<GPIOPortId::G> {
            static constexpr uint32_t addr = GPIOG_BASE;
			#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t en_addr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
				static constexpr uint32_t en_bit = RCC_AHB1ENR_GPIOGEN_Pos;
			#elif defined(EOS_PLATFORM_STM32G0)
				static constexpr uint32_t en_addr = RCC_BASE + offsetof(RCC_TypeDef, IOPENR);
				static constexpr uint32_t en_bit = RCC_IOPENR_GPIOGEN_Pos;
			#endif
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::G, GPIOPinId::_6> {
            static constexpr uint32_t pn = 6;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::G, GPIOPinId::_7> {
            static constexpr uint32_t pn = 7;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::G, GPIOPinId::_9> {
            static constexpr uint32_t pn = 9;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::G, GPIOPinId::_10> {
            static constexpr uint32_t pn = 10;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::G, GPIOPinId::_11> {
            static constexpr uint32_t pn = 11;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::G, GPIOPinId::_12> {
            static constexpr uint32_t pn = 12;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::G, GPIOPinId::_13> {
            static constexpr uint32_t pn = 13;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::G, GPIOPinId::_14> {
            static constexpr uint32_t pn = 14;
        };
    #endif

    #ifdef HTL_GPIOH_EXIST
        template  <>
        struct GPIOPortTrait<GPIOPortId::H> {
            static constexpr uint32_t addr = GPIOH_BASE;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::H, GPIOPinId::_0> {
            static constexpr uint32_t pn = 0;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::H, GPIOPinId::_1> {
            static constexpr uint32_t pn = 1;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::H, GPIOPinId::_2> {
            static constexpr uint32_t pn = 2;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::H, GPIOPinId::_3> {
            static constexpr uint32_t pn = 3;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::H, GPIOPinId::_4> {
            static constexpr uint32_t pn = 4;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::H, GPIOPinId::_5> {
            static constexpr uint32_t pn = 5;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::H, GPIOPinId::_6> {
            static constexpr uint32_t pn = 6;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::H, GPIOPinId::_7> {
            static constexpr uint32_t pn = 7;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::H, GPIOPinId::_8> {
            static constexpr uint32_t pn = 8;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::H, GPIOPinId::_9> {
            static constexpr uint32_t pn = 9;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::H, GPIOPinId::_10> {
            static constexpr uint32_t pn = 10;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::H, GPIOPinId::_11> {
            static constexpr uint32_t pn = 11;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::H, GPIOPinId::_12> {
            static constexpr uint32_t pn = 12;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::H, GPIOPinId::_14> {
            static constexpr uint32_t pn = 14;
        };
    #endif

    #ifdef HTL_GPIOI_EXIST
        template  <>
        struct GPIOPortTrait<GPIOPortId::I> {
            static constexpr uint32_t addr = GPIOI_BASE;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::I, GPIOPinId::_0> {
            static constexpr uint32_t pn = 0;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::I, GPIOPinId::_1> {
            static constexpr uint32_t pn = 1;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::I, GPIOPinId::_2> {
            static constexpr uint32_t pn = 2;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::I, GPIOPinId::_3> {
            static constexpr uint32_t pn = 3;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::I, GPIOPinId::_4> {
            static constexpr uint32_t pn = 4;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::I, GPIOPinId::_5> {
            static constexpr uint32_t pn = 5;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::I, GPIOPinId::_6> {
            static constexpr uint32_t pn = 6;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::I, GPIOPinId::_9> {
            static constexpr uint32_t pn = 9;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::I, GPIOPinId::_10> {
            static constexpr uint32_t pn = 10;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::I, GPIOPinId::_11> {
            static constexpr uint32_t pn = 11;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::I, GPIOPinId::_12> {
            static constexpr uint32_t pn = 12;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::I, GPIOPinId::_13> {
            static constexpr uint32_t pn = 13;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::I, GPIOPinId::_14> {
            static constexpr uint32_t pn = 14;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::I, GPIOPinId::_15> {
            static constexpr uint32_t pn = 15;
        };
    #endif

    #ifdef HTL_GPIOJ_EXIST
        template  <>
        struct GPIOPortTrait<GPIOPortId::J> {
            static constexpr uint32_t addr = GPIOJ_BASE;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::J, GPIOPinId::_0> {
            static constexpr uint32_t pn = 0;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::J, GPIOPinId::_1> {
            static constexpr uint32_t pn = 1;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::J, GPIOPinId::_2> {
            static constexpr uint32_t pn = 2;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::J, GPIOPinId::_3> {
            static constexpr uint32_t pn = 3;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::J, GPIOPinId::_4> {
            static constexpr uint32_t pn = 4;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::J, GPIOPinId::_5> {
            static constexpr uint32_t pn = 5;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::J, GPIOPinId::_6> {
            static constexpr uint32_t pn = 6;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::J, GPIOPinId::_7> {
            static constexpr uint32_t pn = 7;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::J, GPIOPinId::_8> {
            static constexpr uint32_t pn = 8;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::J, GPIOPinId::_9> {
            static constexpr uint32_t pn = 9;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::J, GPIOPinId::_10> {
            static constexpr uint32_t pn = 10;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::J, GPIOPinId::_11> {
            static constexpr uint32_t pn = 11;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::J, GPIOPinId::_13> {
            static constexpr uint32_t pn = 13;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::J, GPIOPinId::_14> {
            static constexpr uint32_t pn = 14;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::J, GPIOPinId::_15> {
            static constexpr uint32_t pn = 15;
        };
    #endif

    #ifdef HTL_GPIOK_EXIST
        template  <>
        struct GPIOPortTrait<GPIOPortId::K> {
            static constexpr uint32_t addr = GPIOK_BASE;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::K, GPIOPinId::_0> {
            static constexpr uint32_t pn = 0;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::K, GPIOPinId::_1> {
            static constexpr uint32_t pn = 1;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::K, GPIOPinId::_2> {
            static constexpr uint32_t pn = 2;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::K, GPIOPinId::_3> {
            static constexpr uint32_t pn = 3;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::K, GPIOPinId::_4> {
            static constexpr uint32_t pn = 4;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::K, GPIOPinId::_5> {
            static constexpr uint32_t pn = 5;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::K, GPIOPinId::_6> {
            static constexpr uint32_t pn = 6;
        };

        template <>
        struct GPIOPinTrait<GPIOPortId::K, GPIOPinId::_7> {
            static constexpr uint32_t pn = 7;
        };
    #endif
}


#endif // __STM32_htlGPIO__

/// @}
/// @}
/// @}

