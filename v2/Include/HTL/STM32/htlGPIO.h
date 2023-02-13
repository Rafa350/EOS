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


#if defined(EOS_PLATFORM_STM32G0)
	#define HTL_GPIOA_CLK_ENABLE()     RCC->IOPENR |= RCC_IOPENR_GPIOAEN
	#define HTL_GPIOB_CLK_ENABLE()     RCC->IOPENR |= RCC_IOPENR_GPIOBEN
	#define HTL_GPIOC_CLK_ENABLE()     RCC->IOPENR |= RCC_IOPENR_GPIOCEN
	#define HTL_GPIOD_CLK_ENABLE()     RCC->IOPENR |= RCC_IOPENR_GPIODEN
	#define HTL_GPIOE_CLK_ENABLE()     RCC->IOPENR |= RCC_IOPENR_GPIOEEN
	#define HTL_GPIOF_CLK_ENABLE()     RCC->IOPENR |= RCC_IOPENR_GPIOFEN
	#define HTL_GPIOA_CLK_DISABLE()    RCC->IOPENR &= ~RCC_IOPENR_GPIOAEN
	#define HTL_GPIOB_CLK_DISABLE()    RCC->IOPENR &= ~RCC_IOPENR_GPIOBEN
	#define HTL_GPIOC_CLK_DISABLE()    RCC->IOPENR &= ~RCC_IOPENR_GPIOCEN
	#define HTL_GPIOD_CLK_DISABLE()    RCC->IOPENR &= ~RCC_IOPENR_GPIODEN
	#define HTL_GPIOE_CLK_DISABLE()    RCC->IOPENR &= ~RCC_IOPENR_GPIOEEN
	#define HTL_GPIOF_CLK_DISABLE()    RCC->IOPENR &= ~RCC_IOPENR_GPIOFEN

#elif defined(EOS_PLATFORM_STM32F0)
	#define HTL_GPIOA_CLK_ENABLE()     RCC->AHBENR |= RCC_AHBENR_GPIOAEN
	#define HTL_GPIOB_CLK_ENABLE()     RCC->AHBENR |= RCC_AHBENR_GPIOBEN
	#define HTL_GPIOC_CLK_ENABLE()     RCC->AHBENR |= RCC_AHBENR_GPIOCEN
	#define HTL_GPIOD_CLK_ENABLE()     RCC->AHBENR |= RCC_AHBENR_GPIODEN
	#define HTL_GPIOE_CLK_ENABLE()     RCC->AHBENR |= RCC_AHBENR_GPIOEEN
	#define HTL_GPIOF_CLK_ENABLE()     RCC->AHBENR |= RCC_AHBENR_GPIOFEN
	#define HTL_GPIOA_CLK_DISABLE()    RCC->AHBENR &= ~RCC_AHBENR_GPIOAEN
	#define HTL_GPIOB_CLK_DISABLE()    RCC->AHBENR &= ~RCC_AHBENR_GPIOBEN
	#define HTL_GPIOC_CLK_DISABLE()    RCC->AHBENR &= ~RCC_AHBENR_GPIOCEN
	#define HTL_GPIOD_CLK_DISABLE()    RCC->AHBENR &= ~RCC_AHBENR_GPIODEN
	#define HTL_GPIOE_CLK_DISABLE()    RCC->AHBENR &= ~RCC_AHBENR_GPIOEEN
	#define HTL_GPIOF_CLK_DISABLE()    RCC->AHBENR &= ~RCC_AHBENR_GPIOFEN

#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
	#define HTL_GPIOA_CLK_ENABLE()     RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN
	#define HTL_GPIOB_CLK_ENABLE()     RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN
	#define HTL_GPIOC_CLK_ENABLE()     RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN
	#define HTL_GPIOD_CLK_ENABLE()     RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN
	#define HTL_GPIOE_CLK_ENABLE()     RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN
	#define HTL_GPIOF_CLK_ENABLE()     RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN
	#define HTL_GPIOG_CLK_ENABLE()     RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN
	#define HTL_GPIOH_CLK_ENABLE()     RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN
	#define HTL_GPIOI_CLK_ENABLE()     RCC->AHB1ENR |= RCC_AHB1ENR_GPIOIEN
	#define HTL_GPIOJ_CLK_ENABLE()     RCC->AHB1ENR |= RCC_AHB1ENR_GPIOJEN
	#define HTL_GPIOK_CLK_ENABLE()     RCC->AHB1ENR |= RCC_AHB1ENR_GPIOKEN
	#define HTL_GPIOA_CLK_DISABLE()    RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOAEN
	#define HTL_GPIOB_CLK_DISABLE()    RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOBEN
	#define HTL_GPIOC_CLK_DISABLE()    RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOCEN
	#define HTL_GPIOD_CLK_DISABLE()    RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIODEN
	#define HTL_GPIOE_CLK_DISABLE()    RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOEEN
	#define HTL_GPIOF_CLK_DISABLE()    RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOFEN
	#define HTL_GPIOG_CLK_DISABLE()    RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOGEN
	#define HTL_GPIOH_CLK_DISABLE()    RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOHEN
	#define HTL_GPIOI_CLK_DISABLE()    RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOIEN
	#define HTL_GPIOJ_CLK_DISABLE()    RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOJEN
	#define HTL_GPIOK_CLK_DISABLE()    RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOKEN
#endif


namespace htl {

    /// \brief Port identifiers.
    enum class GPIOPort {
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
					#ifdef HTL_GPIOA_EXIST
    					if constexpr (port_ == GPIOPort::A)
    						HTL_GPIOA_CLK_ENABLE();
					#endif
					#ifdef HTL_GPIOB_EXIST
    					if constexpr (port_ == GPIOPort::B)
    						HTL_GPIOB_CLK_ENABLE();
					#endif
					#ifdef HTL_GPIOC_EXIST
    					if constexpr (port_ == GPIOPort::C)
							HTL_GPIOC_CLK_ENABLE();
					#endif
					#ifdef HTL_GPIOD_EXIST
    					if constexpr (port_ == GPIOPort::D)
							HTL_GPIOD_CLK_ENABLE();
					#endif
					#ifdef HTL_GPIOE_EXIST
    					if constexpr (port_ == GPIOPort::E)
							HTL_GPIOE_CLK_ENABLE();
					#endif
					#ifdef HTL_GPIOF_EXIST
    					if constexpr (port_ == GPIOPort::F)
							HTL_GPIOF_CLK_ENABLE();
					#endif
					#ifdef HTL_GPIOG_EXIST
    					if constexpr (port_ == GPIOPort::G)
							HTL_GPIOG_CLK_ENABLE();
					#endif
					#ifdef HTL_GPIOH_EXIST
    					if constexpr (port_ == GPIOPort::H)
							HTL_GPIOH_CLK_ENABLE();
					#endif
					#ifdef HTL_GPIOI_EXIST
    					if constexpr (port_ == GPIOPort::I)
							HTL_GPIOI_CLK_ENABLE();
					#endif
					#ifdef HTL_GPIOJ_EXIST
    					if constexpr (port_ == GPIOPort::J)
							HTL_GPIOJ_CLK_ENABLE();
					#endif
					#ifdef HTL_GPIOK_EXIST
    					if constexpr (port_ == GPIOPort::K)
							HTL_GPIOK_CLK_ENABLE();
					#endif
    				__DSB();
    			}
    			_activated |= mask;
    		}

    		static void deactivate(
    			uint16_t mask) {

    			_activated &= ~mask;
    			if (!_activated) {
					#ifdef HTL_GPIOA_EXIST
    					if constexpr (port_ == GPIOPort::A)
    						HTL_GPIOA_CLK_DISABLE();
					#endif
					#ifdef HTL_GPIOB_EXIST
    					if constexpr (port_ == GPIOPort::B)
    	    				HTL_GPIOB_CLK_DISABLE();
					#endif
					#ifdef HTL_GPIOC_EXIST
    					if constexpr(port_ == GPIOPort::C)
    	    				HTL_GPIOC_CLK_DISABLE();
					#endif
					#ifdef HTL_GPIOD_EXIST
    					if constexpr (port_ == GPIOPort::D)
    	    				HTL_GPIOD_CLK_DISABLE();
					#endif
					#ifdef HTL_GPIOE_EXIST
    					if constexpr (port_ == GPIOPort::E)
    	    				HTL_GPIOE_CLK_DISABLE();
					#endif
					#ifdef HTL_GPIOF_EXIST
    					if constexpr (port_ == GPIOPort::F)
    	    				HTL_GPIOF_CLK_DISABLE();
					#endif
					#ifdef HTL_GPIOG_EXIST
    					if constexpr (port_ == GPIOPort::G)
    	    				HTL_GPIOG_CLK_DISABLE();
					#endif
					#ifdef HTL_GPIOH_EXIST
    					if constexpr (port_ == GPIOPort::H)
    	    				HTL_GPIOH_CLK_DISABLE();
					#endif
					#ifdef HTL_GPIOI_EXIST
    					if constexpr (port_ == GPIOPort::I)
    	    				HTL_GPIOI_CLK_DISABLE();
					#endif
					#ifdef HTL_GPIOJ_EXIST
    					if constexpr (port_ == GPIOPort::J)
    	    				HTL_GPIOJ_CLK_DISABLE();
					#endif
					#ifdef HTL_GPIOK_EXIST
    					if constexpr (port_ == GPIOPort::K)
    	    				HTL_GPIOK_CLK_DISABLE();
					#endif
    			}
    		}
    };

    template <GPIOPort port_> uint16_t GPIOPortActivator<port_>::_activated = 0;


    /// \class GPIOBase_x
    /// \brief Base class for gpio
    ///
    class GPIOBase_x {
    	protected:
			static void initInput(GPIO_TypeDef *regs, uint32_t pn, GPIOPull pullMode);
			static void initOutput(GPIO_TypeDef *regs, uint32_t pn, GPIODriver driver, GPIOSpeed speed);
			static void initAlt(GPIO_TypeDef *regs, uint32_t pn, GPIODriver driver, GPIOSpeed speed, GPIOAlt alt);
            static void initAnalogic(GPIO_TypeDef *regs, uint32_t pn);
    };

    /// \class GPIO_x
    /// \brief Class for gpio pins
    ///
    template <GPIOPort port_, GPIOPin pin_>
    class GPIO_x final: public GPIOBase_x {
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

    #ifdef HTL_GPIOB_EXIST
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

    #ifdef HTL_GPIOC_EXIST
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

    #ifdef HTL_GPIOD_EXIST
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

    #ifdef HTL_GPIOE_EXIST
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

    #ifdef HTL_GPIOF_EXIST
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

    #ifdef HTL_GPIOG_EXIST
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

    #ifdef HTL_GPIOH_EXIST
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

    #ifdef HTL_GPIOI_EXIST
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

    #ifdef HTL_GPIOJ_EXIST
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

    #ifdef HTL_GPIOK_EXIST
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


    #ifdef HTL_GPIOA_EXIST
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
        struct GPIOPinTrait<GPIOPort::A, GPIOPin::_2> {
            static constexpr uint32_t pn = 2;
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

    #ifdef HTL_GPIOB_EXIST
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
        struct GPIOPinTrait<GPIOPort::B, GPIOPin::_12> {
            static constexpr uint32_t pn = 12;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::B, GPIOPin::_13> {
            static constexpr uint32_t pn = 13;
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

    #ifdef HTL_GPIOC_EXIST
        template  <>
        struct GPIOPortTrait<GPIOPort::C> {
            static constexpr uint32_t addr = GPIOC_BASE;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::C, GPIOPin::_0> {
            static constexpr uint32_t pn = 0;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::C, GPIOPin::_1> {
            static constexpr uint32_t pn = 1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::C, GPIOPin::_2> {
            static constexpr uint32_t pn = 2;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::C, GPIOPin::_3> {
            static constexpr uint32_t pn = 3;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::C, GPIOPin::_4> {
            static constexpr uint32_t pn = 4;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::C, GPIOPin::_5> {
            static constexpr uint32_t pn = 5;
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
        struct GPIOPinTrait<GPIOPort::C, GPIOPin::_8> {
            static constexpr uint32_t pn = 8;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::C, GPIOPin::_9> {
            static constexpr uint32_t pn = 9;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::C, GPIOPin::_10> {
            static constexpr uint32_t pn = 10;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::C, GPIOPin::_11> {
            static constexpr uint32_t pn = 11;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::C, GPIOPin::_12> {
            static constexpr uint32_t pn = 12;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::C, GPIOPin::_13> {
            static constexpr uint32_t pn = 13;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::C, GPIOPin::_14> {
            static constexpr uint32_t pn = 14;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::C, GPIOPin::_15> {
            static constexpr uint32_t pn = 15;
        };
    #endif

    #ifdef HTL_GPIOD_EXIST
        template  <>
        struct GPIOPortTrait<GPIOPort::D> {
            static constexpr uint32_t addr = GPIOD_BASE;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::D, GPIOPin::_0> {
            static constexpr uint32_t pn = 0;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::D, GPIOPin::_1> {
            static constexpr uint32_t pn = 1;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::D, GPIOPin::_2> {
            static constexpr uint32_t pn = 2;
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
        struct GPIOPinTrait<GPIOPort::D, GPIOPin::_11> {
            static constexpr uint32_t pn = 11;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::D, GPIOPin::_12> {
            static constexpr uint32_t pn = 12;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::D, GPIOPin::_13> {
            static constexpr uint32_t pn = 13;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::D, GPIOPin::_14> {
            static constexpr uint32_t pn = 14;
        };

        template <>
        struct GPIOPinTrait<GPIOPort::D, GPIOPin::_15> {
            static constexpr uint32_t pn = 15;
        };
    #endif

    #ifdef HTL_GPIOE_EXIST
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

    #ifdef HTL_GPIOF_EXIST
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

    #ifdef HTL_GPIOG_EXIST
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

    #ifdef HTL_GPIOH_EXIST
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

    #ifdef HTL_GPIOI_EXIST
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

    #ifdef HTL_GPIOJ_EXIST
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

    #ifdef HTL_GPIOK_EXIST
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
}


#endif // __STM32_htlGPIO__

/// @}
/// @}
/// @}

