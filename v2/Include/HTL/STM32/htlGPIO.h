#pragma once
/// \file      htlGPIO.h
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
    enum class GPIOPortID {
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
    enum class GPIOPinID {
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

    typedef uint8_t GPIOPinNumber;
    typedef uint16_t GPIOPinMask;

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

    enum class GPIOInitPinState {
    	noChange,
		clear,
		set
    };

    enum class GPIOPinState {
		clear,
    	set
    };


    class GPIOPort {
		private:
			GPIO_TypeDef *_gpio;

		protected:
			GPIOPort(GPIO_TypeDef *gpio);
			GPIOPort(const GPIOPort&) = delete;
			virtual ~GPIOPort() = default;

			GPIOPort& operator = (const GPIOPort&) = delete;

			virtual void activateImpl() = 0;
			virtual void deactivateImpl() = 0;
			virtual void resetImpl() = 0;

		public:
			inline void activate() {
				activateImpl();
			}
			inline void deactivate() {
				activateImpl();
			}
			inline void reset() {
				resetImpl();
			}

			void initInput(GPIOPinMask mask, GPIOPull pull);
			void initOutput(GPIOPinID pinID, GPIODriver driver = GPIODriver::pushPull, GPIOSpeed speed = GPIOSpeed::medium) {
				initOutput(1 << int(pinID), driver, speed);
			}
			void initOutput(GPIOPinMask mask, GPIODriver driver = GPIODriver::pushPull, GPIOSpeed speed = GPIOSpeed::medium);

			inline void set(GPIOPinMask mask) {
				_gpio->BSRR = mask;
			}
			inline void set(GPIOPinID pinID) {
				_gpio->BSRR = 1 << int(pinID);
			}

			inline void clear(GPIOPinMask mask) {
				_gpio->BSRR = mask << 16;
			}
			inline void clear(GPIOPinID pinID) {
				_gpio->BSRR = 1 << (int(pinID) + 16);
			}

			inline void toggle(GPIOPinMask mask) {
				_gpio->ODR ^= mask;
			}
			inline void toggle(GPIOPinID pinID) {
				_gpio->ODR ^= 1 << int(pinID);
			}

			inline GPIOPinMask read() {
				return _gpio->IDR;
			}
			inline GPIOPinState read(GPIOPinID pinID) {
				return (_gpio->IDR & (1 << int(pinID))) ? GPIOPinState::set : GPIOPinState::clear;
			}

			inline void write(GPIOPinMask mask) {
				_gpio->ODR = mask;
			}
			inline void write(GPIOPinMask clearMask, GPIOPinMask setMask) {
				uint16_t r = _gpio->ODR;
				r &= ~clearMask;
				r |= setMask;
				_gpio->ODR = r;
			}
			inline void write(GPIOPinID pinID, GPIOPinState state) {
				if (state == GPIOPinState::set)
					_gpio->BSRR = 1 << int(pinID);
				else
					_gpio->BSRR = 1 << (int(pinID) + 16);
			}
	};

	typedef GPIOPort *GPIOPortHandler;

	class GPIOPin {
		private:
			GPIO_TypeDef *_gpio;
			GPIOPinID _pinID;

		protected:
			GPIOPin(GPIO_TypeDef *gpio, GPIOPinID pinID);
			GPIOPin(const GPIOPin&) = delete;

		public:
			void initOutput(GPIODriver driver, GPIOSpeed speed, GPIOInitPinState state);

			inline void set() {
				_gpio->BSRR = 1 << int(_pinID);
			}
			inline void clear() {
				_gpio->BSRR = 1 << (int(_pinID) + 16);
			}
			inline void toggle() {
				_gpio->ODR ^= 1 << int(_pinID);
			}
			inline void write(GPIOPinState state) {
				if (state == GPIOPinState::set)
					_gpio->BSRR = 1 << int(_pinID);
				else
					_gpio->BSRR = 1 << (int(_pinID) + 16);
			}
			inline GPIOPinState read() {
				return (_gpio->IDR & (1 << int(_pinID))) ? GPIOPinState::set : GPIOPinState::clear;
			}
	};

	typedef GPIOPin *GPIOPinHandler;

	template <GPIOPortID>
	struct GPIOInfo {
	};

	template <GPIOPortID portID_>
	class GPIOPort_X final: public GPIOPort {
		private:
			using Info = GPIOInfo<portID_>;
		private:
			static constexpr uint32_t _gpioAddr = Info::gpioAddr;
			static constexpr uint32_t _rccEnableAddr = Info::rccEnableAddr;
			static constexpr uint32_t _rccEnablePos = Info::rccEnablePos;
			static constexpr uint32_t _rccResetAddr = Info::rccResetAddr;
			static constexpr uint32_t _rccResetPos = Info::rccResetPos;
		private:
			GPIOPort_X():
				GPIOPort(reinterpret_cast<GPIO_TypeDef*>(_gpioAddr)) {
			}
		protected:
			void activateImpl() override {
				uint32_t *p = reinterpret_cast<uint32_t*>(_rccEnableAddr);
				*p |= 1 << _rccEnablePos;
				__DSB();
			}
			void deactivateImpl() override {
				uint32_t *p = reinterpret_cast<uint32_t*>(_rccEnableAddr);
				*p &= ~(1 << _rccEnablePos);
			}
			void resetImpl() override {
				uint32_t *p = reinterpret_cast<uint32_t*>(_rccResetAddr);
				*p |= 1 << _rccResetPos;
				*p &= ~(1 << _rccResetPos);
			}
		public:
			static GPIOPortHandler getHandler() {
				static GPIOPort_X port;
				return &port;
			}
	};

	#ifdef HTL_GPIOA_EXIST
	typedef GPIOPort_X<GPIOPortID::A> GPIOPort_A;
	#endif
	#ifdef HTL_GPIOB_EXIST
	typedef GPIOPort_X<GPIOPortID::B> GPIOPort_B;
	#endif
	#ifdef HTL_GPIOC_EXIST
	typedef GPIOPort_X<GPIOPortID::C> GPIOPort_C;
	#endif
	#ifdef HTL_GPIOD_EXIST
	typedef GPIOPort_X<GPIOPortID::D> GPIOPort_D;
	#endif
	#ifdef HTL_GPIOE_EXIST
	typedef GPIOPort_X<GPIOPortID::E> GPIOPort_E;
	#endif
	#ifdef HTL_GPIOF_EXIST
	typedef GPIOPort_X<GPIOPortID::F> GPIOPort_F;
	#endif
	#ifdef HTL_GPIOG_EXIST
	typedef GPIOPort_X<GPIOPortID::G> GPIOPort_G;
	#endif


	template <GPIOPortID portID_, GPIOPinID pinID_>
	class GPIOPin_X final: public GPIOPin {
		private:
			using Info = GPIOInfo<portID_>;
		private:
			static constexpr uint32_t _gpioAddr = Info::gpioAddr;
		private:
			GPIOPin_X():
				GPIOPin(reinterpret_cast<GPIO_TypeDef*>(_gpioAddr), pinID_) {
			}
		public:
			static GPIOPinHandler getHandler() {
				static GPIOPin_X pin;
				return &pin;
			}
	};

	#ifdef HTL_GPIOC_EXIST
	typedef GPIOPin_X<GPIOPortID::C, GPIOPinID::_0> GPIOPin_C0;
	typedef GPIOPin_X<GPIOPortID::C, GPIOPinID::_1> GPIOPin_C1;
	typedef GPIOPin_X<GPIOPortID::C, GPIOPinID::_2> GPIOPin_C2;
	typedef GPIOPin_X<GPIOPortID::C, GPIOPinID::_3> GPIOPin_C3;
	typedef GPIOPin_X<GPIOPortID::C, GPIOPinID::_4> GPIOPin_C4;
	typedef GPIOPin_X<GPIOPortID::C, GPIOPinID::_5> GPIOPin_C5;
	typedef GPIOPin_X<GPIOPortID::C, GPIOPinID::_6> GPIOPin_C6;
	typedef GPIOPin_X<GPIOPortID::C, GPIOPinID::_7> GPIOPin_C7;
	typedef GPIOPin_X<GPIOPortID::C, GPIOPinID::_8> GPIOPin_C8;
	typedef GPIOPin_X<GPIOPortID::C, GPIOPinID::_9> GPIOPin_C9;
	typedef GPIOPin_X<GPIOPortID::C, GPIOPinID::_10> GPIOPin_C10;
	typedef GPIOPin_X<GPIOPortID::C, GPIOPinID::_11> GPIOPin_C11;
	typedef GPIOPin_X<GPIOPortID::C, GPIOPinID::_12> GPIOPin_C12;
	typedef GPIOPin_X<GPIOPortID::C, GPIOPinID::_13> GPIOPin_C13;
	typedef GPIOPin_X<GPIOPortID::C, GPIOPinID::_14> GPIOPin_C14;
	typedef GPIOPin_X<GPIOPortID::C, GPIOPinID::_15> GPIOPin_C15;
	#endif


	#ifdef HTL_GPIOA_EXIST
	template <>
	struct GPIOInfo<GPIOPortID::A> {
		static constexpr uint32_t gpioAddr = GPIOA_BASE;
		#if defined(EOS_PLATFORM_STM32G0)
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPENR);
		static constexpr uint32_t rccEnablePos = RCC_IOPENR_GPIOAEN_Pos;
		static constexpr uint32_t rccResetAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPRSTR);
		static constexpr uint32_t rccResetPos = RCC_IOPRSTR_GPIOARST_Pos;
		#endif
	};
	#endif
	#ifdef HTL_GPIOB_EXIST
	template <>
	struct GPIOInfo<GPIOPortID::B> {
		static constexpr uint32_t gpioAddr = GPIOB_BASE;
		#if defined(EOS_PLATFORM_STM32G0)
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPENR);
		static constexpr uint32_t rccEnablePos = RCC_IOPENR_GPIOBEN_Pos;
		static constexpr uint32_t rccResetAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPRSTR);
		static constexpr uint32_t rccResetPos = RCC_IOPRSTR_GPIOBRST_Pos;
		#endif
	};
	#endif
	#ifdef HTL_GPIOC_EXIST
	template <>
	struct GPIOInfo<GPIOPortID::C> {
		static constexpr uint32_t gpioAddr = GPIOC_BASE;
		#if defined(EOS_PLATFORM_STM32G0)
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPENR);
		static constexpr uint32_t rccEnablePos = RCC_IOPENR_GPIOCEN_Pos;
		static constexpr uint32_t rccResetAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPRSTR);
		static constexpr uint32_t rccResetPos = RCC_IOPRSTR_GPIOCRST_Pos;
		#endif
	};
	#endif
	#ifdef HTL_GPIOD_EXIST
	template <>
	struct GPIOInfo<GPIOPortID::D> {
		static constexpr uint32_t gpioAddr = GPIOD_BASE;
		#if defined(EOS_PLATFORM_STM32G0)
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPENR);
		static constexpr uint32_t rccEnablePos = RCC_IOPENR_GPIODEN_Pos;
		static constexpr uint32_t rccResetAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPRSTR);
		static constexpr uint32_t rccResetPos = RCC_IOPRSTR_GPIODRST_Pos;
		#endif
	};
	#endif
	#ifdef HTL_GPIOE_EXIST
	template <>
	struct GPIOInfo<GPIOPortID::E> {
		static constexpr uint32_t gpioAddr = GPIOE_BASE;
		#if defined(EOS_PLATFORM_STM32G0)
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPENR);
		static constexpr uint32_t rccEnablePos = RCC_IOPENR_GPIOEEN_Pos;
		static constexpr uint32_t rccResetAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPRSTR);
		static constexpr uint32_t rccResetPos = RCC_IOPRSTR_GPIOERST_Pos;
		#endif
	};
	#endif
	#ifdef HTL_GPIOF_EXIST
	template <>
	struct GPIOInfo<GPIOPortID::F> {
		static constexpr uint32_t gpioAddr = GPIOF_BASE;
		#if defined(EOS_PLATFORM_STM32G0)
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPENR);
		static constexpr uint32_t rccEnablePos = RCC_IOPENR_GPIOFEN_Pos;
		static constexpr uint32_t rccResetAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPRSTR);
		static constexpr uint32_t rccResetPos = RCC_IOPRSTR_GPIOFRST_Pos;
		#endif
	};
	#endif
	#ifdef HTL_GPIOG_EXIST
	template <>
	struct GPIOInfo<GPIOPortID::G> {
		static constexpr uint32_t gpioAddr = GPIOG_BASE;
		#if defined(EOS_PLATFORM_STM32G0)
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPENR);
		static constexpr uint32_t rccEnablePos = RCC_IOPENR_GPIOGEN_Pos;
		static constexpr uint32_t rccResetAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPRSTR);
		static constexpr uint32_t rccResetPos = RCC_IOPRSTR_GPIOGRST_Pos;
		#endif
	};
	#endif


    template <GPIOPortID>
    struct GPIOPortTrait {
    };

    template <GPIOPortID, GPIOPinID>
    struct GPIOPinTrait {
    };

    template <GPIOPortID portId_>
    class GPIOPortActivator final {
    	private:
    		using PortTrait = GPIOPortTrait<portId_>;
    		static constexpr uint32_t _rccEnableAddr = PortTrait::rccEnableAddr;
    		static constexpr uint32_t _rccEnablePos = PortTrait::rccEnablePos;
    		static constexpr uint32_t _rccResetAddr = PortTrait::rccResetAddr;
    		static constexpr uint32_t _rccResetPos = PortTrait::rccResetPos;
    		static uint16_t _activated;

    	public:
    		static void activate(
    			uint16_t mask) {

    			if (!_activated) {
					uint32_t *p = reinterpret_cast<uint32_t*>(_rccEnableAddr);
					*p |= 1 << _rccEnablePos;
    				__DSB();
    			}
    			_activated |= mask;
    		}

    		static void deactivate(
    			uint16_t mask) {

    			_activated &= ~mask;
    			if (!_activated) {
					uint32_t *p = reinterpret_cast<uint32_t*>(_rccEnableAddr);
					*p &= ~(1 << _rccEnablePos);
    			}
    		}

    		static void reset() {

				uint32_t *p = reinterpret_cast<uint32_t*>(_rccResetAddr);
				*p |= 1 << _rccResetPos;
				*p &= ~(1 << _rccResetPos);

				_activated = 0;
    		}
    };

    template <GPIOPortID portId_> uint16_t GPIOPortActivator<portId_>::_activated = 0;
    
    
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
    template <GPIOPortID portId_>
    class GPIOPort_x final: public GPIOPortBase_x {
        private:
            using PortTrait = GPIOPortTrait<portId_>;
            using Activator = GPIOPortActivator<portId_>;
            static constexpr uint32_t _gpioAddr = PortTrait::gpioAddr;

        public:
            static constexpr GPIOPortID port = portId_;
            
        private:
            GPIOPort_x() = delete;
            GPIOPort_x(const GPIOPort_x &) = delete;
            GPIOPort_x(const GPIOPort_x &&) = delete;
            ~GPIOPort_x() = delete;

            GPIOPort_x & operator = (const GPIOPort_x &) = delete;
            GPIOPort_x & operator = (const GPIOPort_x &&) = delete;

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
                    reinterpret_cast<GPIO_TypeDef*>(_gpioAddr),
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
				GPIOInitPinState state = GPIOInitPinState::noChange) {

            	Activator::activate(mask);
                GPIOPortBase_x::initOutput(
                    reinterpret_cast<GPIO_TypeDef*>(_gpioAddr),
                    mask,
                    driver,
                    speed);
            }

            static void reset() {

            	Activator::reset();
            }

            /// \brief Set pins to set state
            /// \param mask: Pin mask.
            ///
            static void set(uint16_t mask) {
                GPIO_TypeDef *regs = reinterpret_cast<GPIO_TypeDef*>(_gpioAddr);
                regs->BSRR = mask;
            }

            /// \brief Set pins to clear state
            /// \param mask: Pin mask.
            ///
            static void clear(uint16_t mask) {
                GPIO_TypeDef *regs = reinterpret_cast<GPIO_TypeDef*>(_gpioAddr);
                regs->BSRR = mask << 16;
            }

            /// \brief Toggle pin state
            /// \param mask: Pin mask.
            ///
            static void toggle(uint16_t mask) {
                GPIO_TypeDef *regs = reinterpret_cast<GPIO_TypeDef*>(_gpioAddr);
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
    template <GPIOPortID portId_, GPIOPinID pinId_>
    class GPIO_x final: public GPIOBase_x {
        private:
            using PortTrait = GPIOPortTrait<portId_>;
            using PinTrait = GPIOPinTrait<portId_, pinId_>;
            using Activator = GPIOPortActivator<portId_>;
            static constexpr uint32_t _gpioAddr = PortTrait::gpioAddr;
            static constexpr uint32_t _pn = PinTrait::pn;

        public:
            static constexpr GPIOPortID port = portId_;
            static constexpr GPIOPinID pin = pinId_;

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
                    reinterpret_cast<GPIO_TypeDef*>(_gpioAddr),
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
				GPIOInitPinState state = GPIOInitPinState::noChange) {

            	Activator::activate(1 << _pn);

                GPIO_TypeDef *regs = reinterpret_cast<GPIO_TypeDef*>(_gpioAddr);

                if (state != GPIOInitPinState::noChange)
                	regs->BSRR = 1 << (_pn + (state == GPIOInitPinState::set ? 0 : 16));

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
                    reinterpret_cast<GPIO_TypeDef*>(_gpioAddr),
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
                    reinterpret_cast<GPIO_TypeDef*>(_gpioAddr),
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

                GPIO_TypeDef *regs = reinterpret_cast<GPIO_TypeDef*>(_gpioAddr);
                regs->BSRR = 1 << _pn;
            }

            /// \brief Set pin to OFF state.
            ///
            inline static void clear() {

                GPIO_TypeDef *regs = reinterpret_cast<GPIO_TypeDef*>(_gpioAddr);
                regs->BSRR = 1 << (_pn + 16);
            }

            /// \brief Toggle pin state.
            ///
            inline static void toggle() {

                GPIO_TypeDef *regs = reinterpret_cast<GPIO_TypeDef*>(_gpioAddr);
                regs->ODR ^= 1 << _pn;
            }

            /// \brief Read pin state
            /// \return Pin state.
            ///
            inline static GPIOPinState read() {

                GPIO_TypeDef *regs = reinterpret_cast<GPIO_TypeDef*>(_gpioAddr);
                return ((regs->IDR & (1 << _pn)) == 0) ? GPIOPinState::clear : GPIOPinState::set;
            }

            /// \brief Write pin state.
            /// \param state: State to write.
            ///
            inline static void write(
            	GPIOPinState state) {

                GPIO_TypeDef *regs = reinterpret_cast<GPIO_TypeDef*>(_gpioAddr);
                regs->BSRR = 1 << (_pn + (state == GPIOPinState::set ? 0 : 16));
            }
    };

    #ifdef HTL_GPIOA_EXIST
	using GPIO_A = GPIOPort_x<GPIOPortID::A>;
	typedef GPIO_x<GPIOPortID::A, GPIOPinID::_0> GPIO_A0;
	typedef GPIO_x<GPIOPortID::A, GPIOPinID::_1> GPIO_A1;
	typedef GPIO_x<GPIOPortID::A, GPIOPinID::_2> GPIO_A2;
	typedef GPIO_x<GPIOPortID::A, GPIOPinID::_3> GPIO_A3;
	typedef GPIO_x<GPIOPortID::A, GPIOPinID::_4> GPIO_A4;
	typedef GPIO_x<GPIOPortID::A, GPIOPinID::_5> GPIO_A5;
	typedef GPIO_x<GPIOPortID::A, GPIOPinID::_6> GPIO_A6;
	typedef GPIO_x<GPIOPortID::A, GPIOPinID::_7> GPIO_A7;
	typedef GPIO_x<GPIOPortID::A, GPIOPinID::_8> GPIO_A8;
	typedef GPIO_x<GPIOPortID::A, GPIOPinID::_9> GPIO_A9;
	typedef GPIO_x<GPIOPortID::A, GPIOPinID::_10> GPIO_A10;
	typedef GPIO_x<GPIOPortID::A, GPIOPinID::_11> GPIO_A11;
	typedef GPIO_x<GPIOPortID::A, GPIOPinID::_12> GPIO_A12;
	typedef GPIO_x<GPIOPortID::A, GPIOPinID::_13> GPIO_A13;
	typedef GPIO_x<GPIOPortID::A, GPIOPinID::_14> GPIO_A14;
	typedef GPIO_x<GPIOPortID::A, GPIOPinID::_15> GPIO_A15;
    #endif

    #ifdef HTL_GPIOB_EXIST
	using GPIO_B = GPIOPort_x<GPIOPortID::B>;
	typedef GPIO_x<GPIOPortID::B, GPIOPinID::_0> GPIO_B0;
	typedef GPIO_x<GPIOPortID::B, GPIOPinID::_1> GPIO_B1;
	typedef GPIO_x<GPIOPortID::B, GPIOPinID::_2> GPIO_B2;
	typedef GPIO_x<GPIOPortID::B, GPIOPinID::_3> GPIO_B3;
	typedef GPIO_x<GPIOPortID::B, GPIOPinID::_4> GPIO_B4;
	typedef GPIO_x<GPIOPortID::B, GPIOPinID::_5> GPIO_B5;
	typedef GPIO_x<GPIOPortID::B, GPIOPinID::_6> GPIO_B6;
	typedef GPIO_x<GPIOPortID::B, GPIOPinID::_7> GPIO_B7;
	typedef GPIO_x<GPIOPortID::B, GPIOPinID::_8> GPIO_B8;
	typedef GPIO_x<GPIOPortID::B, GPIOPinID::_9> GPIO_B9;
	typedef GPIO_x<GPIOPortID::B, GPIOPinID::_10> GPIO_B10;
	typedef GPIO_x<GPIOPortID::B, GPIOPinID::_11> GPIO_B11;
	typedef GPIO_x<GPIOPortID::B, GPIOPinID::_12> GPIO_B12;
	typedef GPIO_x<GPIOPortID::B, GPIOPinID::_13> GPIO_B13;
	typedef GPIO_x<GPIOPortID::B, GPIOPinID::_14> GPIO_B14;
	typedef GPIO_x<GPIOPortID::B, GPIOPinID::_15> GPIO_B15;
    #endif

    #ifdef HTL_GPIOC_EXIST
	using GPIO_C = GPIOPort_x<GPIOPortID::C>;
	typedef GPIO_x<GPIOPortID::C, GPIOPinID::_0> GPIO_C0;
	typedef GPIO_x<GPIOPortID::C, GPIOPinID::_1> GPIO_C1;
	typedef GPIO_x<GPIOPortID::C, GPIOPinID::_2> GPIO_C2;
	typedef GPIO_x<GPIOPortID::C, GPIOPinID::_3> GPIO_C3;
	typedef GPIO_x<GPIOPortID::C, GPIOPinID::_4> GPIO_C4;
	typedef GPIO_x<GPIOPortID::C, GPIOPinID::_5> GPIO_C5;
	typedef GPIO_x<GPIOPortID::C, GPIOPinID::_6> GPIO_C6;
	typedef GPIO_x<GPIOPortID::C, GPIOPinID::_7> GPIO_C7;
	typedef GPIO_x<GPIOPortID::C, GPIOPinID::_8> GPIO_C8;
	typedef GPIO_x<GPIOPortID::C, GPIOPinID::_9> GPIO_C9;
	typedef GPIO_x<GPIOPortID::C, GPIOPinID::_10> GPIO_C10;
	typedef GPIO_x<GPIOPortID::C, GPIOPinID::_11> GPIO_C11;
	typedef GPIO_x<GPIOPortID::C, GPIOPinID::_12> GPIO_C12;
	typedef GPIO_x<GPIOPortID::C, GPIOPinID::_13> GPIO_C13;
	typedef GPIO_x<GPIOPortID::C, GPIOPinID::_14> GPIO_C14;
	typedef GPIO_x<GPIOPortID::C, GPIOPinID::_15> GPIO_C15;
    #endif

    #ifdef HTL_GPIOD_EXIST
	using GPIO_D = GPIOPort_x<GPIOPortID::D>;
	typedef GPIO_x<GPIOPortID::D, GPIOPinID::_0> GPIO_D0;
	typedef GPIO_x<GPIOPortID::D, GPIOPinID::_1> GPIO_D1;
	typedef GPIO_x<GPIOPortID::D, GPIOPinID::_2> GPIO_D2;
	typedef GPIO_x<GPIOPortID::D, GPIOPinID::_3> GPIO_D3;
	typedef GPIO_x<GPIOPortID::D, GPIOPinID::_4> GPIO_D4;
	typedef GPIO_x<GPIOPortID::D, GPIOPinID::_5> GPIO_D5;
	typedef GPIO_x<GPIOPortID::D, GPIOPinID::_6> GPIO_D6;
	typedef GPIO_x<GPIOPortID::D, GPIOPinID::_7> GPIO_D7;
	typedef GPIO_x<GPIOPortID::D, GPIOPinID::_8> GPIO_D8;
	typedef GPIO_x<GPIOPortID::D, GPIOPinID::_9> GPIO_D9;
	typedef GPIO_x<GPIOPortID::D, GPIOPinID::_10> GPIO_D10;
	typedef GPIO_x<GPIOPortID::D, GPIOPinID::_11> GPIO_D11;
	typedef GPIO_x<GPIOPortID::D, GPIOPinID::_12> GPIO_D12;
	typedef GPIO_x<GPIOPortID::D, GPIOPinID::_13> GPIO_D13;
	typedef GPIO_x<GPIOPortID::D, GPIOPinID::_14> GPIO_D14;
	typedef GPIO_x<GPIOPortID::D, GPIOPinID::_15> GPIO_D15;
    #endif

    #ifdef HTL_GPIOE_EXIST
	using GPIO_E = GPIOPort_x<GPIOPortID::E>;
	typedef GPIO_x<GPIOPortID::E, GPIOPinID::_0> GPIO_E0;
	typedef GPIO_x<GPIOPortID::E, GPIOPinID::_1> GPIO_E1;
	typedef GPIO_x<GPIOPortID::E, GPIOPinID::_2> GPIO_E2;
	typedef GPIO_x<GPIOPortID::E, GPIOPinID::_3> GPIO_E3;
	typedef GPIO_x<GPIOPortID::E, GPIOPinID::_4> GPIO_E4;
	typedef GPIO_x<GPIOPortID::E, GPIOPinID::_5> GPIO_E5;
	typedef GPIO_x<GPIOPortID::E, GPIOPinID::_6> GPIO_E6;
	typedef GPIO_x<GPIOPortID::E, GPIOPinID::_7> GPIO_E7;
	typedef GPIO_x<GPIOPortID::E, GPIOPinID::_8> GPIO_E8;
	typedef GPIO_x<GPIOPortID::E, GPIOPinID::_9> GPIO_E9;
	typedef GPIO_x<GPIOPortID::E, GPIOPinID::_10> GPIO_E10;
	typedef GPIO_x<GPIOPortID::E, GPIOPinID::_11> GPIO_E11;
	typedef GPIO_x<GPIOPortID::E, GPIOPinID::_12> GPIO_E12;
	typedef GPIO_x<GPIOPortID::E, GPIOPinID::_13> GPIO_E13;
	typedef GPIO_x<GPIOPortID::E, GPIOPinID::_14> GPIO_E14;
	typedef GPIO_x<GPIOPortID::E, GPIOPinID::_15> GPIO_E15;
    #endif

    #ifdef HTL_GPIOF_EXIST
	using GPIO_F = GPIOPort_x<GPIOPortID::F>;
	typedef GPIO_x<GPIOPortID::F, GPIOPinID::_0> GPIO_F0;
	typedef GPIO_x<GPIOPortID::F, GPIOPinID::_1> GPIO_F1;
	typedef GPIO_x<GPIOPortID::F, GPIOPinID::_2> GPIO_F2;
	typedef GPIO_x<GPIOPortID::F, GPIOPinID::_3> GPIO_F3;
	typedef GPIO_x<GPIOPortID::F, GPIOPinID::_4> GPIO_F4;
	typedef GPIO_x<GPIOPortID::F, GPIOPinID::_5> GPIO_F5;
	typedef GPIO_x<GPIOPortID::F, GPIOPinID::_6> GPIO_F6;
	typedef GPIO_x<GPIOPortID::F, GPIOPinID::_7> GPIO_F7;
	typedef GPIO_x<GPIOPortID::F, GPIOPinID::_8> GPIO_F8;
	typedef GPIO_x<GPIOPortID::F, GPIOPinID::_9> GPIO_F9;
	typedef GPIO_x<GPIOPortID::F, GPIOPinID::_10> GPIO_F10;
	typedef GPIO_x<GPIOPortID::F, GPIOPinID::_11> GPIO_F11;
	typedef GPIO_x<GPIOPortID::F, GPIOPinID::_12> GPIO_F12;
	typedef GPIO_x<GPIOPortID::F, GPIOPinID::_13> GPIO_F13;
	typedef GPIO_x<GPIOPortID::F, GPIOPinID::_14> GPIO_F14;
	typedef GPIO_x<GPIOPortID::F, GPIOPinID::_15> GPIO_F15;
    #endif

    #ifdef HTL_GPIOG_EXIST
	using GPIO_G = GPIOPort_x<GPIOPortID::G>;
	typedef GPIO_x<GPIOPortID::G, GPIOPinID::_0> GPIO_G0;
	typedef GPIO_x<GPIOPortID::G, GPIOPinID::_1> GPIO_G1;
	typedef GPIO_x<GPIOPortID::G, GPIOPinID::_2> GPIO_G2;
	typedef GPIO_x<GPIOPortID::G, GPIOPinID::_3> GPIO_G3;
	typedef GPIO_x<GPIOPortID::G, GPIOPinID::_4> GPIO_G4;
	typedef GPIO_x<GPIOPortID::G, GPIOPinID::_5> GPIO_G5;
	typedef GPIO_x<GPIOPortID::G, GPIOPinID::_6> GPIO_G6;
	typedef GPIO_x<GPIOPortID::G, GPIOPinID::_7> GPIO_G7;
	typedef GPIO_x<GPIOPortID::G, GPIOPinID::_8> GPIO_G8;
	typedef GPIO_x<GPIOPortID::G, GPIOPinID::_9> GPIO_G9;
	typedef GPIO_x<GPIOPortID::G, GPIOPinID::_10> GPIO_G10;
	typedef GPIO_x<GPIOPortID::G, GPIOPinID::_11> GPIO_G11;
	typedef GPIO_x<GPIOPortID::G, GPIOPinID::_12> GPIO_G12;
	typedef GPIO_x<GPIOPortID::G, GPIOPinID::_13> GPIO_G13;
	typedef GPIO_x<GPIOPortID::G, GPIOPinID::_14> GPIO_G14;
	typedef GPIO_x<GPIOPortID::G, GPIOPinID::_15> GPIO_G15;
    #endif

    #ifdef HTL_GPIOH_EXIST
	using GPIO_H = GPIOPort_x<GPIOPortID::H>;
	typedef GPIO_x<GPIOPortID::H, GPIOPinID::_0> GPIO_H0;
	typedef GPIO_x<GPIOPortID::H, GPIOPinID::_1> GPIO_H1;
	typedef GPIO_x<GPIOPortID::H, GPIOPinID::_2> GPIO_H2;
	typedef GPIO_x<GPIOPortID::H, GPIOPinID::_3> GPIO_H3;
	typedef GPIO_x<GPIOPortID::H, GPIOPinID::_4> GPIO_H4;
	typedef GPIO_x<GPIOPortID::H, GPIOPinID::_5> GPIO_H5;
	typedef GPIO_x<GPIOPortID::H, GPIOPinID::_6> GPIO_H6;
	typedef GPIO_x<GPIOPortID::H, GPIOPinID::_7> GPIO_H7;
	typedef GPIO_x<GPIOPortID::H, GPIOPinID::_8> GPIO_H8;
	typedef GPIO_x<GPIOPortID::H, GPIOPinID::_9> GPIO_H9;
	typedef GPIO_x<GPIOPortID::H, GPIOPinID::_10> GPIO_H10;
	typedef GPIO_x<GPIOPortID::H, GPIOPinID::_11> GPIO_H11;
	typedef GPIO_x<GPIOPortID::H, GPIOPinID::_12> GPIO_H12;
	typedef GPIO_x<GPIOPortID::H, GPIOPinID::_13> GPIO_H13;
	typedef GPIO_x<GPIOPortID::H, GPIOPinID::_14> GPIO_H14;
	typedef GPIO_x<GPIOPortID::H, GPIOPinID::_15> GPIO_H15;
    #endif

    #ifdef HTL_GPIOI_EXIST
	using GPIO_I = GPIOPort_x<GPIOPortID::I>;
	typedef GPIO_x<GPIOPortID::I, GPIOPinID::_0> GPIO_I0;
	typedef GPIO_x<GPIOPortID::I, GPIOPinID::_1> GPIO_I1;
	typedef GPIO_x<GPIOPortID::I, GPIOPinID::_2> GPIO_I2;
	typedef GPIO_x<GPIOPortID::I, GPIOPinID::_3> GPIO_I3;
	typedef GPIO_x<GPIOPortID::I, GPIOPinID::_4> GPIO_I4;
	typedef GPIO_x<GPIOPortID::I, GPIOPinID::_5> GPIO_I5;
	typedef GPIO_x<GPIOPortID::I, GPIOPinID::_6> GPIO_I6;
	typedef GPIO_x<GPIOPortID::I, GPIOPinID::_7> GPIO_I7;
	typedef GPIO_x<GPIOPortID::I, GPIOPinID::_8> GPIO_I8;
	typedef GPIO_x<GPIOPortID::I, GPIOPinID::_9> GPIO_I9;
	typedef GPIO_x<GPIOPortID::I, GPIOPinID::_10> GPIO_I10;
	typedef GPIO_x<GPIOPortID::I, GPIOPinID::_11> GPIO_I11;
	typedef GPIO_x<GPIOPortID::I, GPIOPinID::_12> GPIO_I12;
	typedef GPIO_x<GPIOPortID::I, GPIOPinID::_13> GPIO_I13;
	typedef GPIO_x<GPIOPortID::I, GPIOPinID::_14> GPIO_I14;
	typedef GPIO_x<GPIOPortID::I, GPIOPinID::_15> GPIO_I15;
    #endif

    #ifdef HTL_GPIOJ_EXIST
	using GPIO_J = GPIOPort_x<GPIOPortID::J>;
	typedef GPIO_x<GPIOPortID::J, GPIOPinID::_0> GPIO_J0;
	typedef GPIO_x<GPIOPortID::J, GPIOPinID::_1> GPIO_J1;
	typedef GPIO_x<GPIOPortID::J, GPIOPinID::_2> GPIO_J2;
	typedef GPIO_x<GPIOPortID::J, GPIOPinID::_3> GPIO_J3;
	typedef GPIO_x<GPIOPortID::J, GPIOPinID::_4> GPIO_J4;
	typedef GPIO_x<GPIOPortID::J, GPIOPinID::_5> GPIO_J5;
	typedef GPIO_x<GPIOPortID::J, GPIOPinID::_6> GPIO_J6;
	typedef GPIO_x<GPIOPortID::J, GPIOPinID::_7> GPIO_J7;
	typedef GPIO_x<GPIOPortID::J, GPIOPinID::_8> GPIO_J8;
	typedef GPIO_x<GPIOPortID::J, GPIOPinID::_9> GPIO_J9;
	typedef GPIO_x<GPIOPortID::J, GPIOPinID::_10> GPIO_J10;
	typedef GPIO_x<GPIOPortID::J, GPIOPinID::_11> GPIO_J11;
	typedef GPIO_x<GPIOPortID::J, GPIOPinID::_12> GPIO_J12;
	typedef GPIO_x<GPIOPortID::J, GPIOPinID::_13> GPIO_J13;
	typedef GPIO_x<GPIOPortID::J, GPIOPinID::_14> GPIO_J14;
	typedef GPIO_x<GPIOPortID::J, GPIOPinID::_15> GPIO_J15;
    #endif

    #ifdef HTL_GPIOK_EXIST
	using GPIO_K = GPIOPort_x<GPIOPortID::K>;
	typedef GPIO_x<GPIOPortID::K, GPIOPinID::_0> GPIO_K0;
	typedef GPIO_x<GPIOPortID::K, GPIOPinID::_1> GPIO_K1;
	typedef GPIO_x<GPIOPortID::K, GPIOPinID::_2> GPIO_K2;
	typedef GPIO_x<GPIOPortID::K, GPIOPinID::_3> GPIO_K3;
	typedef GPIO_x<GPIOPortID::K, GPIOPinID::_4> GPIO_K4;
	typedef GPIO_x<GPIOPortID::K, GPIOPinID::_5> GPIO_K5;
	typedef GPIO_x<GPIOPortID::K, GPIOPinID::_6> GPIO_K6;
	typedef GPIO_x<GPIOPortID::K, GPIOPinID::_7> GPIO_K7;
	typedef GPIO_x<GPIOPortID::K, GPIOPinID::_8> GPIO_K8;
	typedef GPIO_x<GPIOPortID::K, GPIOPinID::_9> GPIO_K9;
	typedef GPIO_x<GPIOPortID::K, GPIOPinID::_10> GPIO_K10;
	typedef GPIO_x<GPIOPortID::K, GPIOPinID::_11> GPIO_K11;
	typedef GPIO_x<GPIOPortID::K, GPIOPinID::_12> GPIO_K12;
	typedef GPIO_x<GPIOPortID::K, GPIOPinID::_13> GPIO_K13;
	typedef GPIO_x<GPIOPortID::K, GPIOPinID::_14> GPIO_K14;
	typedef GPIO_x<GPIOPortID::K, GPIOPinID::_15> GPIO_K15;
    #endif


    #ifdef HTL_GPIOA_EXIST
	template<>
	struct GPIOPortTrait<GPIOPortID::A> {
		static constexpr uint32_t gpioAddr = GPIOA_BASE;
		#if defined(EOS_PLATFORM_STM32F0)
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, AHBENR);
		static constexpr uint32_t rccEnablePos = RCC_AHBENR_GPIOAEN_Pos;
		#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
		static constexpr uint32_t rccEnablePos = RCC_AHB1ENR_GPIOAEN_Pos;
		#elif defined(EOS_PLATFORM_STM32G0)
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPENR);
		static constexpr uint32_t rccEnablePos = RCC_IOPENR_GPIOAEN_Pos;
		static constexpr uint32_t rccResetAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPRSTR);
		static constexpr uint32_t rccResetPos = RCC_IOPRSTR_GPIOARST_Pos;
		#endif
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::A, GPIOPinID::_0> {
		static constexpr uint32_t pn = 0;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::A, GPIOPinID::_1> {
		static constexpr uint32_t pn = 1;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::A, GPIOPinID::_2> {
		static constexpr uint32_t pn = 2;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::A, GPIOPinID::_3> {
		static constexpr uint32_t pn = 3;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::A, GPIOPinID::_4> {
		static constexpr uint32_t pn = 4;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::A, GPIOPinID::_5> {
		static constexpr uint32_t pn = 5;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::A, GPIOPinID::_6> {
		static constexpr uint32_t pn = 6;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::A, GPIOPinID::_7> {
		static constexpr uint32_t pn = 7;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::A, GPIOPinID::_8> {
		static constexpr uint32_t pn = 8;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::A, GPIOPinID::_9> {
		static constexpr uint32_t pn = 9;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::A, GPIOPinID::_10> {
		static constexpr uint32_t pn = 10;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::A, GPIOPinID::_11> {
		static constexpr uint32_t pn = 11;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::A, GPIOPinID::_12> {
		static constexpr uint32_t pn = 12;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::A, GPIOPinID::_13> {
		static constexpr uint32_t pn = 13;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::A, GPIOPinID::_14> {
		static constexpr uint32_t pn = 14;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::A, GPIOPinID::_15> {
		static constexpr uint32_t pn = 15;
	};
    #endif

    #ifdef HTL_GPIOB_EXIST
	template  <>
	struct GPIOPortTrait<GPIOPortID::B> {
		static constexpr uint32_t gpioAddr = GPIOB_BASE;
		#if defined(EOS_PLATFORM_STM32F0)
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, AHBENR);
		static constexpr uint32_t rccEnablePos = RCC_AHBENR_GPIOBEN_Pos;
		#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
		static constexpr uint32_t rccEnablePos = RCC_AHB1ENR_GPIOBEN_Pos;
		#elif defined(EOS_PLATFORM_STM32G0)
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPENR);
		static constexpr uint32_t rccEnablePos = RCC_IOPENR_GPIOBEN_Pos;
		static constexpr uint32_t rccResetAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPRSTR);
		static constexpr uint32_t rccResetPos = RCC_IOPRSTR_GPIOBRST_Pos;
		#endif
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::B, GPIOPinID::_0> {
		static constexpr uint32_t pn = 0;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::B, GPIOPinID::_1> {
		static constexpr uint32_t pn = 1;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::B, GPIOPinID::_2> {
		static constexpr uint32_t pn = 2;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::B, GPIOPinID::_3> {
		static constexpr uint32_t pn = 3;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::B, GPIOPinID::_4> {
		static constexpr uint32_t pn = 4;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::B, GPIOPinID::_5> {
		static constexpr uint32_t pn = 5;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::B, GPIOPinID::_6> {
		static constexpr uint32_t pn = 6;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::B, GPIOPinID::_7> {
		static constexpr uint32_t pn = 7;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::B, GPIOPinID::_8> {
		static constexpr uint32_t pn = 8;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::B, GPIOPinID::_9> {
		static constexpr uint32_t pn = 9;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::B, GPIOPinID::_10> {
		static constexpr uint32_t pn = 10;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::B, GPIOPinID::_11> {
		static constexpr uint32_t pn = 11;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::B, GPIOPinID::_12> {
		static constexpr uint32_t pn = 12;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::B, GPIOPinID::_13> {
		static constexpr uint32_t pn = 13;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::B, GPIOPinID::_14> {
		static constexpr uint32_t pn = 14;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::B, GPIOPinID::_15> {
		static constexpr uint32_t pn = 15;
	};
    #endif

    #ifdef HTL_GPIOC_EXIST
	template  <>
	struct GPIOPortTrait<GPIOPortID::C> {
		static constexpr uint32_t gpioAddr = GPIOC_BASE;
		#if defined(EOS_PLATFORM_STM32F0)
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, AHBENR);
		static constexpr uint32_t rccEnablePos = RCC_AHBENR_GPIOCEN_Pos;
		#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
		static constexpr uint32_t rccEnablePos = RCC_AHB1ENR_GPIOCEN_Pos;
		#elif defined(EOS_PLATFORM_STM32G0)
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPENR);
		static constexpr uint32_t rccEnablePos = RCC_IOPENR_GPIOCEN_Pos;
		static constexpr uint32_t rccResetAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPRSTR);
		static constexpr uint32_t rccResetPos = RCC_IOPRSTR_GPIOCRST_Pos;
		#endif
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::C, GPIOPinID::_0> {
		static constexpr uint32_t pn = 0;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::C, GPIOPinID::_1> {
		static constexpr uint32_t pn = 1;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::C, GPIOPinID::_2> {
		static constexpr uint32_t pn = 2;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::C, GPIOPinID::_3> {
		static constexpr uint32_t pn = 3;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::C, GPIOPinID::_4> {
		static constexpr uint32_t pn = 4;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::C, GPIOPinID::_5> {
		static constexpr uint32_t pn = 5;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::C, GPIOPinID::_6> {
		static constexpr uint32_t pn = 6;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::C, GPIOPinID::_7> {
		static constexpr uint32_t pn = 7;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::C, GPIOPinID::_8> {
		static constexpr uint32_t pn = 8;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::C, GPIOPinID::_9> {
		static constexpr uint32_t pn = 9;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::C, GPIOPinID::_10> {
		static constexpr uint32_t pn = 10;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::C, GPIOPinID::_11> {
		static constexpr uint32_t pn = 11;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::C, GPIOPinID::_12> {
		static constexpr uint32_t pn = 12;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::C, GPIOPinID::_13> {
		static constexpr uint32_t pn = 13;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::C, GPIOPinID::_14> {
		static constexpr uint32_t pn = 14;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::C, GPIOPinID::_15> {
		static constexpr uint32_t pn = 15;
	};
    #endif

    #ifdef HTL_GPIOD_EXIST
	template  <>
	struct GPIOPortTrait<GPIOPortID::D> {
		static constexpr uint32_t gpioAddr = GPIOD_BASE;
		#if defined(EOS_PLATFORM_STM32F0)
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, AHBENR);
		static constexpr uint32_t rccEnablePos = RCC_AHBENR_GPIODEN_Pos;
		#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
		static constexpr uint32_t rccEnablePos = RCC_AHB1ENR_GPIODEN_Pos;
		#elif defined(EOS_PLATFORM_STM32G0)
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPENR);
		static constexpr uint32_t rccEnablePos = RCC_IOPENR_GPIODEN_Pos;
		static constexpr uint32_t rccResetAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPRSTR);
		static constexpr uint32_t rccResetPos = RCC_IOPRSTR_GPIODRST_Pos;
		#endif
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::D, GPIOPinID::_0> {
		static constexpr uint32_t pn = 0;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::D, GPIOPinID::_1> {
		static constexpr uint32_t pn = 1;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::D, GPIOPinID::_2> {
		static constexpr uint32_t pn = 2;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::D, GPIOPinID::_3> {
		static constexpr uint32_t pn = 3;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::D, GPIOPinID::_6> {
		static constexpr uint32_t pn = 6;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::D, GPIOPinID::_7> {
		static constexpr uint32_t pn = 7;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::D, GPIOPinID::_11> {
		static constexpr uint32_t pn = 11;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::D, GPIOPinID::_12> {
		static constexpr uint32_t pn = 12;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::D, GPIOPinID::_13> {
		static constexpr uint32_t pn = 13;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::D, GPIOPinID::_14> {
		static constexpr uint32_t pn = 14;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::D, GPIOPinID::_15> {
		static constexpr uint32_t pn = 15;
	};
    #endif

    #ifdef HTL_GPIOE_EXIST
	template  <>
	struct GPIOPortTrait<GPIOPortID::E> {
		static constexpr uint32_t gpioAddr = GPIOE_BASE;
		#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
		static constexpr uint32_t rccEnablePos = RCC_AHB1ENR_GPIOEEN_Pos;
		#elif defined(EOS_PLATFORM_STM32G0)
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPENR);
		static constexpr uint32_t rccEnablePos = RCC_IOPENR_GPIOEEN_Pos;
		static constexpr uint32_t rccResetAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPRSTR);
		static constexpr uint32_t rccResetPos = RCC_IOPRSTR_GPIOERST_Pos;
		#endif
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::E, GPIOPinID::_4> {
		static constexpr uint32_t pn = 4;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::E, GPIOPinID::_5> {
		static constexpr uint32_t pn = 5;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::E, GPIOPinID::_6> {
		static constexpr uint32_t pn = 6;
	};
    #endif

    #ifdef HTL_GPIOF_EXIST
	template  <>
	struct GPIOPortTrait<GPIOPortID::F> {
		static constexpr uint32_t gpioAddr = GPIOF_BASE;
		#if defined(EOS_PLATFORM_STM32F0)
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, AHBENR);
		static constexpr uint32_t rccEnablePos = RCC_AHBENR_GPIOFEN_Pos;
		#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
		static constexpr uint32_t rccEnablePos = RCC_AHB1ENR_GPIOFEN_Pos;
		#elif defined(EOS_PLATFORM_STM32G0)
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPENR);
		static constexpr uint32_t rccEnablePos = RCC_IOPENR_GPIOFEN_Pos;
		static constexpr uint32_t rccResetAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPRSTR);
		static constexpr uint32_t rccResetPos = RCC_IOPRSTR_GPIOFRST_Pos;
		#endif
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::F, GPIOPinID::_0> {
		static constexpr uint32_t pn = 0;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::F, GPIOPinID::_1> {
		static constexpr uint32_t pn = 1;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::F, GPIOPinID::_2> {
		static constexpr uint32_t pn = 2;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::F, GPIOPinID::_3> {
		static constexpr uint32_t pn = 3;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::F, GPIOPinID::_4> {
		static constexpr uint32_t pn = 4;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::F, GPIOPinID::_5> {
		static constexpr uint32_t pn = 5;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::F, GPIOPinID::_6> {
		static constexpr uint32_t pn = 6;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::F, GPIOPinID::_7> {
		static constexpr uint32_t pn = 7;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::F, GPIOPinID::_8> {
		static constexpr uint32_t pn = 8;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::F, GPIOPinID::_9> {
		static constexpr uint32_t pn = 9;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::F, GPIOPinID::_10> {
		static constexpr uint32_t pn = 10;
	};
    #endif

    #ifdef HTL_GPIOG_EXIST
	template  <>
	struct GPIOPortTrait<GPIOPortID::G> {
		static constexpr uint32_t gpioAddr = GPIOG_BASE;
		#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
		static constexpr uint32_t rccEnablePos = RCC_AHB1ENR_GPIOGEN_Pos;
		#elif defined(EOS_PLATFORM_STM32G0)
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPENR);
		static constexpr uint32_t rccEnablePos = RCC_IOPENR_GPIOGEN_Pos;
		static constexpr uint32_t rccResetAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPRSTR);
		static constexpr uint32_t rccResetPos = RCC_IOPRSTR_GPIOGRST_Pos;
		#endif
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::G, GPIOPinID::_6> {
		static constexpr uint32_t pn = 6;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::G, GPIOPinID::_7> {
		static constexpr uint32_t pn = 7;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::G, GPIOPinID::_9> {
		static constexpr uint32_t pn = 9;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::G, GPIOPinID::_10> {
		static constexpr uint32_t pn = 10;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::G, GPIOPinID::_11> {
		static constexpr uint32_t pn = 11;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::G, GPIOPinID::_12> {
		static constexpr uint32_t pn = 12;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::G, GPIOPinID::_13> {
		static constexpr uint32_t pn = 13;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::G, GPIOPinID::_14> {
		static constexpr uint32_t pn = 14;
	};
    #endif

    #ifdef HTL_GPIOH_EXIST
	template  <>
	struct GPIOPortTrait<GPIOPortID::H> {
		static constexpr uint32_t gpioAddr = GPIOH_BASE;
		#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
		static constexpr uint32_t rccEnablePos = RCC_AHB1ENR_GPIOHEN_Pos;
		#endif
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::H, GPIOPinID::_0> {
		static constexpr uint32_t pn = 0;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::H, GPIOPinID::_1> {
		static constexpr uint32_t pn = 1;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::H, GPIOPinID::_2> {
		static constexpr uint32_t pn = 2;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::H, GPIOPinID::_3> {
		static constexpr uint32_t pn = 3;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::H, GPIOPinID::_4> {
		static constexpr uint32_t pn = 4;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::H, GPIOPinID::_5> {
		static constexpr uint32_t pn = 5;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::H, GPIOPinID::_6> {
		static constexpr uint32_t pn = 6;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::H, GPIOPinID::_7> {
		static constexpr uint32_t pn = 7;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::H, GPIOPinID::_8> {
		static constexpr uint32_t pn = 8;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::H, GPIOPinID::_9> {
		static constexpr uint32_t pn = 9;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::H, GPIOPinID::_10> {
		static constexpr uint32_t pn = 10;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::H, GPIOPinID::_11> {
		static constexpr uint32_t pn = 11;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::H, GPIOPinID::_12> {
		static constexpr uint32_t pn = 12;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::H, GPIOPinID::_14> {
		static constexpr uint32_t pn = 14;
	};
    #endif

    #ifdef HTL_GPIOI_EXIST
	template  <>
	struct GPIOPortTrait<GPIOPortID::I> {
		static constexpr uint32_t gpioAddr = GPIOI_BASE;
		#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
		static constexpr uint32_t rccEnablePos = RCC_AHB1ENR_GPIOIEN_Pos;
		#endif
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::I, GPIOPinID::_0> {
		static constexpr uint32_t pn = 0;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::I, GPIOPinID::_1> {
		static constexpr uint32_t pn = 1;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::I, GPIOPinID::_2> {
		static constexpr uint32_t pn = 2;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::I, GPIOPinID::_3> {
		static constexpr uint32_t pn = 3;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::I, GPIOPinID::_4> {
		static constexpr uint32_t pn = 4;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::I, GPIOPinID::_5> {
		static constexpr uint32_t pn = 5;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::I, GPIOPinID::_6> {
		static constexpr uint32_t pn = 6;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::I, GPIOPinID::_9> {
		static constexpr uint32_t pn = 9;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::I, GPIOPinID::_10> {
		static constexpr uint32_t pn = 10;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::I, GPIOPinID::_11> {
		static constexpr uint32_t pn = 11;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::I, GPIOPinID::_12> {
		static constexpr uint32_t pn = 12;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::I, GPIOPinID::_13> {
		static constexpr uint32_t pn = 13;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::I, GPIOPinID::_14> {
		static constexpr uint32_t pn = 14;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::I, GPIOPinID::_15> {
		static constexpr uint32_t pn = 15;
	};
    #endif

    #ifdef HTL_GPIOJ_EXIST
	template  <>
	struct GPIOPortTrait<GPIOPortID::J> {
		static constexpr uint32_t gpioAddr = GPIOJ_BASE;
		#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
		static constexpr uint32_t rccEnablePos = RCC_AHB1ENR_GPIOJEN_Pos;
		#endif
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::J, GPIOPinID::_0> {
		static constexpr uint32_t pn = 0;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::J, GPIOPinID::_1> {
		static constexpr uint32_t pn = 1;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::J, GPIOPinID::_2> {
		static constexpr uint32_t pn = 2;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::J, GPIOPinID::_3> {
		static constexpr uint32_t pn = 3;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::J, GPIOPinID::_4> {
		static constexpr uint32_t pn = 4;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::J, GPIOPinID::_5> {
		static constexpr uint32_t pn = 5;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::J, GPIOPinID::_6> {
		static constexpr uint32_t pn = 6;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::J, GPIOPinID::_7> {
		static constexpr uint32_t pn = 7;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::J, GPIOPinID::_8> {
		static constexpr uint32_t pn = 8;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::J, GPIOPinID::_9> {
		static constexpr uint32_t pn = 9;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::J, GPIOPinID::_10> {
		static constexpr uint32_t pn = 10;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::J, GPIOPinID::_11> {
		static constexpr uint32_t pn = 11;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::J, GPIOPinID::_13> {
		static constexpr uint32_t pn = 13;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::J, GPIOPinID::_14> {
		static constexpr uint32_t pn = 14;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::J, GPIOPinID::_15> {
		static constexpr uint32_t pn = 15;
	};
    #endif

    #ifdef HTL_GPIOK_EXIST
	template  <>
	struct GPIOPortTrait<GPIOPortID::K> {
		static constexpr uint32_t gpioAddr = GPIOK_BASE;
		#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
		static constexpr uint32_t rccEnablePos = RCC_AHB1ENR_GPIOKEN_Pos;
		#endif
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::K, GPIOPinID::_0> {
		static constexpr uint32_t pn = 0;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::K, GPIOPinID::_1> {
		static constexpr uint32_t pn = 1;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::K, GPIOPinID::_2> {
		static constexpr uint32_t pn = 2;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::K, GPIOPinID::_3> {
		static constexpr uint32_t pn = 3;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::K, GPIOPinID::_4> {
		static constexpr uint32_t pn = 4;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::K, GPIOPinID::_5> {
		static constexpr uint32_t pn = 5;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::K, GPIOPinID::_6> {
		static constexpr uint32_t pn = 6;
	};

	template <>
	struct GPIOPinTrait<GPIOPortID::K, GPIOPinID::_7> {
		static constexpr uint32_t pn = 7;
	};
    #endif
}


#endif // __STM32_htlGPIO__

/// @}
/// @}
/// @}

