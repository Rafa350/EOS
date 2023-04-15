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

	namespace gpio {

		/// \brief Port identifiers.
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
		enum class PullUpDn {
			noChange,
			none,
			up,
			down
		};

		/// \brief Driver type identifier.
		enum class OutDriver {
			noChange,
			pushPull,
			openDrain
		};

		/// \brief Speed identifier.
		enum class Speed {
			noChange,
			low,
			medium,
			high,
			fast
		};

		/// \brief Initial pin state.
		enum class InitPinState {
			noChange,
			clear,
			set
		};

		/// \brief Pin state.
		enum class PinState {
			clear,
			set
		};


		class Port {
			private:
				GPIO_TypeDef * const _gpio;
			private:
				Port(const Port &) = delete;
				Port & operator = (const Port &) = delete;
			protected:
				Port(GPIO_TypeDef *gpio);
				virtual void activateImpl(PinMask mask) = 0;
				virtual void deactivateImpl(PinMask mask) = 0;
				virtual void resetImpl() = 0;
			public:
				inline void activate(PinMask mask) {
					activateImpl(mask);
				}
				inline void deactivate(PinMask mask) {
					activateImpl(mask);
				}
				inline void reset() {
					resetImpl();
				}
				void initInput(PinMask mask, PullUpDn pull);
				void initOutput(PinID pinID, OutDriver driver = OutDriver::pushPull, Speed speed = Speed::medium) {
					initOutput(1 << int(pinID), driver, speed);
				}
				void initOutput(PinMask mask, OutDriver driver = OutDriver::pushPull, Speed speed = Speed::medium);
				inline void set(PinMask mask) {
					_gpio->BSRR = mask;
				}
				inline void set(PinID pinID) {
					_gpio->BSRR = 1 << int(pinID);
				}
				inline void clear(PinMask mask) {
					_gpio->BSRR = mask << 16;
				}
				inline void clear(PinID pinID) {
					_gpio->BSRR = 1 << (int(pinID) + 16);
				}
				inline void toggle(PinMask mask) {
					_gpio->ODR ^= mask;
				}
				inline void toggle(PinID pinID) {
					_gpio->ODR ^= 1 << int(pinID);
				}
				inline PinMask read() {
					return _gpio->IDR;
				}
				inline PinState read(PinID pinID) {
					return (_gpio->IDR & (1 << int(pinID))) ? PinState::set : PinState::clear;
				}
				inline void write(PinMask mask) {
					_gpio->ODR = mask;
				}
				inline void write(PinMask clearMask, PinMask setMask) {
					uint16_t r = _gpio->ODR;
					r &= ~clearMask;
					r |= setMask;
					_gpio->ODR = r;
				}
				inline void write(PinID pinID, PinState state) {
					if (state == PinState::set)
						_gpio->BSRR = 1 << int(pinID);
					else
						_gpio->BSRR = 1 << (int(pinID) + 16);
				}
		};

		typedef Port *PortHandler;


		class Pin {
			private:
				GPIO_TypeDef * const _gpio;
				PinMask const _mask;
			private:
				Pin(const Pin &) = delete;
				Pin & operator = (const Pin &) = delete;
			protected:
				Pin(GPIO_TypeDef *gpio, PinID pinID);
				virtual void activateImpl() = 0;
				virtual void deactivateImpl() = 0;
			public:
				void initInput(PullUpDn pull);
				void initOutput(OutDriver driver, Speed speed, InitPinState state = InitPinState::noChange);
				void initAlt(OutDriver driver, Speed speed, GPIOAlt alt);
				inline void set() {
					_gpio->BSRR = _mask;
				}
				inline void clear() {
					_gpio->BSRR = _mask << 16;
				}
				inline void toggle() {
					_gpio->ODR ^= _mask;
				}
				inline void write(PinState state) {
					if (state == PinState::set)
						_gpio->BSRR = _mask;
					else
						_gpio->BSRR = _mask << 16;
				}
				inline PinState read() {
					return (_gpio->IDR & _mask) ? PinState::set : PinState::clear;
				}
		};

		typedef Pin *PinHandler;


		namespace internal {

			template <PortID>
			class PortActivator;

			template <PortID>
			struct HardwareInfo;

			template <PortID, PinID>
			struct GPIOPinTrait;
		}


		template <PortID portID_>
		class PortX final: public Port {
			private:
				using HI = internal::HardwareInfo<portID_>;
				using Activator = internal::PortActivator<portID_>;
			private:
				static constexpr uint32_t _gpioAddr = HI::gpioAddr;
				static PortX _port;
			public:
				static constexpr PortID portID = portID_;
			private:
				PortX():
					Port(reinterpret_cast<GPIO_TypeDef *>(_gpioAddr)) {
				}
			protected:
				void activateImpl(PinMask mask) override {
					Activator::activate(mask);
				}
				void deactivateImpl(PinMask mask) override {
					Activator::activate(mask);
				}
				void resetImpl() override {
					Activator::reset();
				}
			public:
				inline static PortHandler getHandler() {
					return &_port;
				}
		};

		template <PortID portID_>
		PortX<portID_> PortX<portID_>::_port;

		template <PortID portID_>
		inline PortHandler getPortHandler() {
			return PortX<portID_>::getHandler();
		}


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


		template <PortID portID_, PinID pinID_>
		class PinX final: public Pin {
			private:
				using HI = internal::HardwareInfo<portID_>;
				using Activator = internal::PortActivator<portID_>;
			private:
				static constexpr uint32_t _gpioAddr = HI::gpioAddr;
				static PinX _pin;
			public:
				static constexpr PortID portID = portID_;
				static constexpr PinID pinID = pinID_;
			private:
				PinX():
					Pin(reinterpret_cast<GPIO_TypeDef *>(_gpioAddr), pinID_) {
				}
			protected:
				void activateImpl() override {
					Activator::activate(1 << int(pinID_));
				}
				void deactivateImpl() override {
					Activator::activate(1 << int(pinID_));
				}
			public:
				inline static PinHandler getHandler() {
					return &_pin;
				}
		};

		template <PortID portID_, PinID pinID_>
		PinX<portID_, pinID_> PinX<portID_, pinID_>::_pin;

		template <PortID portID_, PinID pinID_>
		inline PinHandler getPinHandler() {
			return PinX<portID_, pinID_>::getHandler();
		}

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
		typedef PinX<PortID::B, PinID::_14> PinB14;
		typedef PinX<PortID::B, PinID::_15> PinB15;
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
		typedef PinX<PortID::C, PinID::_14> PinC14;
		typedef PinX<PortID::C, PinID::_15> PinC15;
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
		typedef PinX<PortID::D, PinID::_14> PinD14;
		typedef PinX<PortID::D, PinID::_15> PinD15;
		#endif
		#ifdef HTL_GPIOE_EXIST
		typedef PinX<PortID::E, PinID::_0> PinE0;
		typedef PinX<PortID::E, PinID::_1> PinE1;
		typedef PinX<PortID::E, PinID::_2> PinE2;
		typedef PinX<PortID::E, PinID::_3> PinE3;
		typedef PinX<PortID::E, PinID::_4> PinE4;
		typedef PinX<PortID::E, PinID::_5> PinE5;
		typedef PinX<PortID::E, PinID::_6> PinE6;
		typedef PinX<PortID::E, PinID::_7> PinE7;
		typedef PinX<PortID::E, PinID::_8> PinE8;
		typedef PinX<PortID::E, PinID::_9> PinE9;
		typedef PinX<PortID::E, PinID::_10> PinE10;
		typedef PinX<PortID::E, PinID::_11> PinE11;
		typedef PinX<PortID::E, PinID::_12> PinE12;
		typedef PinX<PortID::E, PinID::_13> PinE13;
		typedef PinX<PortID::E, PinID::_14> PinE14;
		typedef PinX<PortID::E, PinID::_15> PinE15;
		#endif
		#ifdef HTL_GPIOF_EXIST
		typedef PinX<PortID::F, PinID::_0> PinF0;
		typedef PinX<PortID::F, PinID::_1> PinF1;
		typedef PinX<PortID::F, PinID::_2> PinF2;
		typedef PinX<PortID::F, PinID::_3> PinF3;
		typedef PinX<PortID::F, PinID::_4> PinF4;
		typedef PinX<PortID::F, PinID::_5> PinF5;
		typedef PinX<PortID::F, PinID::_6> PinF6;
		typedef PinX<PortID::F, PinID::_7> PinF7;
		typedef PinX<PortID::F, PinID::_8> PinF8;
		typedef PinX<PortID::F, PinID::_9> PinF9;
		typedef PinX<PortID::F, PinID::_10> PinF10;
		typedef PinX<PortID::F, PinID::_11> PinF11;
		typedef PinX<PortID::F, PinID::_12> PinF12;
		typedef PinX<PortID::F, PinID::_13> PinF13;
		typedef PinX<PortID::F, PinID::_14> PinF14;
		typedef PinX<PortID::F, PinID::_15> PinF15;
		#endif


		namespace internal {

			template <PortID portId_>
			class PortActivator final {
				private:
					using PortTrait = internal::HardwareInfo<portId_>;
					static constexpr uint32_t _rccEnableAddr = PortTrait::rccEnableAddr;
					static constexpr uint32_t _rccEnablePos = PortTrait::rccEnablePos;
					static constexpr uint32_t _rccResetAddr = PortTrait::rccResetAddr;
					static constexpr uint32_t _rccResetPos = PortTrait::rccResetPos;
					static PinMask _activated;
				public:
					static void activate(PinMask mask) {
						if (!_activated) {
							uint32_t *p = reinterpret_cast<uint32_t*>(_rccEnableAddr);
							*p |= 1 << _rccEnablePos;
							__DSB();
						}
						_activated |= mask;
					}
					static void deactivate(PinMask mask) {
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

			template <PortID portId_>
			PinMask PortActivator<portId_>::_activated = 0;
		}


		/// \class GPIOBase_x
		/// \brief Base class for gpio pins
		///
		class GPIOBase_x {
			protected:
				static void initInput(GPIO_TypeDef *regs, uint32_t pn, PullUpDn pull);
				static void initOutput(GPIO_TypeDef *regs, uint32_t pn, OutDriver driver, Speed speed);
				static void initAlt(GPIO_TypeDef *regs, uint32_t pn, OutDriver driver, Speed speed, GPIOAlt alt);
				static void initAnalogic(GPIO_TypeDef *regs, uint32_t pn);
		};

		/// \class GPIO_x
		/// \brief Class for gpio pins
		///
		template <PortID portId_, PinID pinId_>
		class GPIO_x final: public GPIOBase_x {
			private:
				using PortTrait = internal::HardwareInfo<portId_>;
				using PinTrait = internal::GPIOPinTrait<portId_, pinId_>;
				using Activator = internal::PortActivator<portId_>;
				static constexpr uint32_t _gpioAddr = PortTrait::gpioAddr;
				static constexpr uint32_t _pn = PinTrait::pn;

			public:
				static constexpr PortID port = portId_;
				static constexpr PinID pin = pinId_;

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
					PullUpDn pull = PullUpDn::none) {

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
					OutDriver driver,
					Speed speed = Speed::medium,
					InitPinState state = InitPinState::noChange) {

					Activator::activate(1 << _pn);

					GPIO_TypeDef *regs = reinterpret_cast<GPIO_TypeDef*>(_gpioAddr);

					if (state != InitPinState::noChange)
						regs->BSRR = 1 << (_pn + (state == InitPinState::set ? 0 : 16));

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
					OutDriver driver,
					Speed speed,
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
				inline static PinState read() {

					GPIO_TypeDef *regs = reinterpret_cast<GPIO_TypeDef*>(_gpioAddr);
					return ((regs->IDR & (1 << _pn)) == 0) ? PinState::clear : PinState::set;
				}

				/// \brief Write pin state.
				/// \param state: State to write.
				///
				inline static void write(
					PinState state) {

					GPIO_TypeDef *regs = reinterpret_cast<GPIO_TypeDef*>(_gpioAddr);
					regs->BSRR = 1 << (_pn + (state == PinState::set ? 0 : 16));
				}
		};

		#ifdef HTL_GPIOA_EXIST
		typedef GPIO_x<PortID::A, PinID::_0> GPIO_A0;
		typedef GPIO_x<PortID::A, PinID::_1> GPIO_A1;
		typedef GPIO_x<PortID::A, PinID::_2> GPIO_A2;
		typedef GPIO_x<PortID::A, PinID::_3> GPIO_A3;
		typedef GPIO_x<PortID::A, PinID::_4> GPIO_A4;
		typedef GPIO_x<PortID::A, PinID::_5> GPIO_A5;
		typedef GPIO_x<PortID::A, PinID::_6> GPIO_A6;
		typedef GPIO_x<PortID::A, PinID::_7> GPIO_A7;
		typedef GPIO_x<PortID::A, PinID::_8> GPIO_A8;
		typedef GPIO_x<PortID::A, PinID::_9> GPIO_A9;
		typedef GPIO_x<PortID::A, PinID::_10> GPIO_A10;
		typedef GPIO_x<PortID::A, PinID::_11> GPIO_A11;
		typedef GPIO_x<PortID::A, PinID::_12> GPIO_A12;
		typedef GPIO_x<PortID::A, PinID::_13> GPIO_A13;
		typedef GPIO_x<PortID::A, PinID::_14> GPIO_A14;
		typedef GPIO_x<PortID::A, PinID::_15> GPIO_A15;
		#endif

		#ifdef HTL_GPIOB_EXIST
		typedef GPIO_x<PortID::B, PinID::_0> GPIO_B0;
		typedef GPIO_x<PortID::B, PinID::_1> GPIO_B1;
		typedef GPIO_x<PortID::B, PinID::_2> GPIO_B2;
		typedef GPIO_x<PortID::B, PinID::_3> GPIO_B3;
		typedef GPIO_x<PortID::B, PinID::_4> GPIO_B4;
		typedef GPIO_x<PortID::B, PinID::_5> GPIO_B5;
		typedef GPIO_x<PortID::B, PinID::_6> GPIO_B6;
		typedef GPIO_x<PortID::B, PinID::_7> GPIO_B7;
		typedef GPIO_x<PortID::B, PinID::_8> GPIO_B8;
		typedef GPIO_x<PortID::B, PinID::_9> GPIO_B9;
		typedef GPIO_x<PortID::B, PinID::_10> GPIO_B10;
		typedef GPIO_x<PortID::B, PinID::_11> GPIO_B11;
		typedef GPIO_x<PortID::B, PinID::_12> GPIO_B12;
		typedef GPIO_x<PortID::B, PinID::_13> GPIO_B13;
		typedef GPIO_x<PortID::B, PinID::_14> GPIO_B14;
		typedef GPIO_x<PortID::B, PinID::_15> GPIO_B15;
		#endif

		#ifdef HTL_GPIOC_EXIST
		typedef GPIO_x<PortID::C, PinID::_0> GPIO_C0;
		typedef GPIO_x<PortID::C, PinID::_1> GPIO_C1;
		typedef GPIO_x<PortID::C, PinID::_2> GPIO_C2;
		typedef GPIO_x<PortID::C, PinID::_3> GPIO_C3;
		typedef GPIO_x<PortID::C, PinID::_4> GPIO_C4;
		typedef GPIO_x<PortID::C, PinID::_5> GPIO_C5;
		typedef GPIO_x<PortID::C, PinID::_6> GPIO_C6;
		typedef GPIO_x<PortID::C, PinID::_7> GPIO_C7;
		typedef GPIO_x<PortID::C, PinID::_8> GPIO_C8;
		typedef GPIO_x<PortID::C, PinID::_9> GPIO_C9;
		typedef GPIO_x<PortID::C, PinID::_10> GPIO_C10;
		typedef GPIO_x<PortID::C, PinID::_11> GPIO_C11;
		typedef GPIO_x<PortID::C, PinID::_12> GPIO_C12;
		typedef GPIO_x<PortID::C, PinID::_13> GPIO_C13;
		typedef GPIO_x<PortID::C, PinID::_14> GPIO_C14;
		typedef GPIO_x<PortID::C, PinID::_15> GPIO_C15;
		#endif

		#ifdef HTL_GPIOD_EXIST
		typedef GPIO_x<PortID::D, PinID::_0> GPIO_D0;
		typedef GPIO_x<PortID::D, PinID::_1> GPIO_D1;
		typedef GPIO_x<PortID::D, PinID::_2> GPIO_D2;
		typedef GPIO_x<PortID::D, PinID::_3> GPIO_D3;
		typedef GPIO_x<PortID::D, PinID::_4> GPIO_D4;
		typedef GPIO_x<PortID::D, PinID::_5> GPIO_D5;
		typedef GPIO_x<PortID::D, PinID::_6> GPIO_D6;
		typedef GPIO_x<PortID::D, PinID::_7> GPIO_D7;
		typedef GPIO_x<PortID::D, PinID::_8> GPIO_D8;
		typedef GPIO_x<PortID::D, PinID::_9> GPIO_D9;
		typedef GPIO_x<PortID::D, PinID::_10> GPIO_D10;
		typedef GPIO_x<PortID::D, PinID::_11> GPIO_D11;
		typedef GPIO_x<PortID::D, PinID::_12> GPIO_D12;
		typedef GPIO_x<PortID::D, PinID::_13> GPIO_D13;
		typedef GPIO_x<PortID::D, PinID::_14> GPIO_D14;
		typedef GPIO_x<PortID::D, PinID::_15> GPIO_D15;
		#endif

		#ifdef HTL_GPIOE_EXIST
		typedef GPIO_x<PortID::E, PinID::_0> GPIO_E0;
		typedef GPIO_x<PortID::E, PinID::_1> GPIO_E1;
		typedef GPIO_x<PortID::E, PinID::_2> GPIO_E2;
		typedef GPIO_x<PortID::E, PinID::_3> GPIO_E3;
		typedef GPIO_x<PortID::E, PinID::_4> GPIO_E4;
		typedef GPIO_x<PortID::E, PinID::_5> GPIO_E5;
		typedef GPIO_x<PortID::E, PinID::_6> GPIO_E6;
		typedef GPIO_x<PortID::E, PinID::_7> GPIO_E7;
		typedef GPIO_x<PortID::E, PinID::_8> GPIO_E8;
		typedef GPIO_x<PortID::E, PinID::_9> GPIO_E9;
		typedef GPIO_x<PortID::E, PinID::_10> GPIO_E10;
		typedef GPIO_x<PortID::E, PinID::_11> GPIO_E11;
		typedef GPIO_x<PortID::E, PinID::_12> GPIO_E12;
		typedef GPIO_x<PortID::E, PinID::_13> GPIO_E13;
		typedef GPIO_x<PortID::E, PinID::_14> GPIO_E14;
		typedef GPIO_x<PortID::E, PinID::_15> GPIO_E15;
		#endif

		#ifdef HTL_GPIOF_EXIST
		typedef GPIO_x<PortID::F, PinID::_0> GPIO_F0;
		typedef GPIO_x<PortID::F, PinID::_1> GPIO_F1;
		typedef GPIO_x<PortID::F, PinID::_2> GPIO_F2;
		typedef GPIO_x<PortID::F, PinID::_3> GPIO_F3;
		typedef GPIO_x<PortID::F, PinID::_4> GPIO_F4;
		typedef GPIO_x<PortID::F, PinID::_5> GPIO_F5;
		typedef GPIO_x<PortID::F, PinID::_6> GPIO_F6;
		typedef GPIO_x<PortID::F, PinID::_7> GPIO_F7;
		typedef GPIO_x<PortID::F, PinID::_8> GPIO_F8;
		typedef GPIO_x<PortID::F, PinID::_9> GPIO_F9;
		typedef GPIO_x<PortID::F, PinID::_10> GPIO_F10;
		typedef GPIO_x<PortID::F, PinID::_11> GPIO_F11;
		typedef GPIO_x<PortID::F, PinID::_12> GPIO_F12;
		typedef GPIO_x<PortID::F, PinID::_13> GPIO_F13;
		typedef GPIO_x<PortID::F, PinID::_14> GPIO_F14;
		typedef GPIO_x<PortID::F, PinID::_15> GPIO_F15;
		#endif

		#ifdef HTL_GPIOG_EXIST
		typedef GPIO_x<PortID::G, PinID::_0> GPIO_G0;
		typedef GPIO_x<PortID::G, PinID::_1> GPIO_G1;
		typedef GPIO_x<PortID::G, PinID::_2> GPIO_G2;
		typedef GPIO_x<PortID::G, PinID::_3> GPIO_G3;
		typedef GPIO_x<PortID::G, PinID::_4> GPIO_G4;
		typedef GPIO_x<PortID::G, PinID::_5> GPIO_G5;
		typedef GPIO_x<PortID::G, PinID::_6> GPIO_G6;
		typedef GPIO_x<PortID::G, PinID::_7> GPIO_G7;
		typedef GPIO_x<PortID::G, PinID::_8> GPIO_G8;
		typedef GPIO_x<PortID::G, PinID::_9> GPIO_G9;
		typedef GPIO_x<PortID::G, PinID::_10> GPIO_G10;
		typedef GPIO_x<PortID::G, PinID::_11> GPIO_G11;
		typedef GPIO_x<PortID::G, PinID::_12> GPIO_G12;
		typedef GPIO_x<PortID::G, PinID::_13> GPIO_G13;
		typedef GPIO_x<PortID::G, PinID::_14> GPIO_G14;
		typedef GPIO_x<PortID::G, PinID::_15> GPIO_G15;
		#endif

		#ifdef HTL_GPIOH_EXIST
		typedef GPIO_x<PortID::H, PinID::_0> GPIO_H0;
		typedef GPIO_x<PortID::H, PinID::_1> GPIO_H1;
		typedef GPIO_x<PortID::H, PinID::_2> GPIO_H2;
		typedef GPIO_x<PortID::H, PinID::_3> GPIO_H3;
		typedef GPIO_x<PortID::H, PinID::_4> GPIO_H4;
		typedef GPIO_x<PortID::H, PinID::_5> GPIO_H5;
		typedef GPIO_x<PortID::H, PinID::_6> GPIO_H6;
		typedef GPIO_x<PortID::H, PinID::_7> GPIO_H7;
		typedef GPIO_x<PortID::H, PinID::_8> GPIO_H8;
		typedef GPIO_x<PortID::H, PinID::_9> GPIO_H9;
		typedef GPIO_x<PortID::H, PinID::_10> GPIO_H10;
		typedef GPIO_x<PortID::H, PinID::_11> GPIO_H11;
		typedef GPIO_x<PortID::H, PinID::_12> GPIO_H12;
		typedef GPIO_x<PortID::H, PinID::_13> GPIO_H13;
		typedef GPIO_x<PortID::H, PinID::_14> GPIO_H14;
		typedef GPIO_x<PortID::H, PinID::_15> GPIO_H15;
		#endif

		#ifdef HTL_GPIOI_EXIST
		typedef GPIO_x<PortID::I, PinID::_0> GPIO_I0;
		typedef GPIO_x<PortID::I, PinID::_1> GPIO_I1;
		typedef GPIO_x<PortID::I, PinID::_2> GPIO_I2;
		typedef GPIO_x<PortID::I, PinID::_3> GPIO_I3;
		typedef GPIO_x<PortID::I, PinID::_4> GPIO_I4;
		typedef GPIO_x<PortID::I, PinID::_5> GPIO_I5;
		typedef GPIO_x<PortID::I, PinID::_6> GPIO_I6;
		typedef GPIO_x<PortID::I, PinID::_7> GPIO_I7;
		typedef GPIO_x<PortID::I, PinID::_8> GPIO_I8;
		typedef GPIO_x<PortID::I, PinID::_9> GPIO_I9;
		typedef GPIO_x<PortID::I, PinID::_10> GPIO_I10;
		typedef GPIO_x<PortID::I, PinID::_11> GPIO_I11;
		typedef GPIO_x<PortID::I, PinID::_12> GPIO_I12;
		typedef GPIO_x<PortID::I, PinID::_13> GPIO_I13;
		typedef GPIO_x<PortID::I, PinID::_14> GPIO_I14;
		typedef GPIO_x<PortID::I, PinID::_15> GPIO_I15;
		#endif

		#ifdef HTL_GPIOJ_EXIST
		typedef GPIO_x<PortID::J, PinID::_0> GPIO_J0;
		typedef GPIO_x<PortID::J, PinID::_1> GPIO_J1;
		typedef GPIO_x<PortID::J, PinID::_2> GPIO_J2;
		typedef GPIO_x<PortID::J, PinID::_3> GPIO_J3;
		typedef GPIO_x<PortID::J, PinID::_4> GPIO_J4;
		typedef GPIO_x<PortID::J, PinID::_5> GPIO_J5;
		typedef GPIO_x<PortID::J, PinID::_6> GPIO_J6;
		typedef GPIO_x<PortID::J, PinID::_7> GPIO_J7;
		typedef GPIO_x<PortID::J, PinID::_8> GPIO_J8;
		typedef GPIO_x<PortID::J, PinID::_9> GPIO_J9;
		typedef GPIO_x<PortID::J, PinID::_10> GPIO_J10;
		typedef GPIO_x<PortID::J, PinID::_11> GPIO_J11;
		typedef GPIO_x<PortID::J, PinID::_12> GPIO_J12;
		typedef GPIO_x<PortID::J, PinID::_13> GPIO_J13;
		typedef GPIO_x<PortID::J, PinID::_14> GPIO_J14;
		typedef GPIO_x<PortID::J, PinID::_15> GPIO_J15;
		#endif

		#ifdef HTL_GPIOK_EXIST
		typedef GPIO_x<PortID::K, PinID::_0> GPIO_K0;
		typedef GPIO_x<PortID::K, PinID::_1> GPIO_K1;
		typedef GPIO_x<PortID::K, PinID::_2> GPIO_K2;
		typedef GPIO_x<PortID::K, PinID::_3> GPIO_K3;
		typedef GPIO_x<PortID::K, PinID::_4> GPIO_K4;
		typedef GPIO_x<PortID::K, PinID::_5> GPIO_K5;
		typedef GPIO_x<PortID::K, PinID::_6> GPIO_K6;
		typedef GPIO_x<PortID::K, PinID::_7> GPIO_K7;
		typedef GPIO_x<PortID::K, PinID::_8> GPIO_K8;
		typedef GPIO_x<PortID::K, PinID::_9> GPIO_K9;
		typedef GPIO_x<PortID::K, PinID::_10> GPIO_K10;
		typedef GPIO_x<PortID::K, PinID::_11> GPIO_K11;
		typedef GPIO_x<PortID::K, PinID::_12> GPIO_K12;
		typedef GPIO_x<PortID::K, PinID::_13> GPIO_K13;
		typedef GPIO_x<PortID::K, PinID::_14> GPIO_K14;
		typedef GPIO_x<PortID::K, PinID::_15> GPIO_K15;
		#endif


		namespace internal {
		#ifdef HTL_GPIOA_EXIST
		template<>
		struct HardwareInfo<PortID::A> {
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
		struct GPIOPinTrait<PortID::A, PinID::_0> {
			static constexpr uint32_t pn = 0;
		};

		template <>
		struct GPIOPinTrait<PortID::A, PinID::_1> {
			static constexpr uint32_t pn = 1;
		};

		template <>
		struct GPIOPinTrait<PortID::A, PinID::_2> {
			static constexpr uint32_t pn = 2;
		};

		template <>
		struct GPIOPinTrait<PortID::A, PinID::_3> {
			static constexpr uint32_t pn = 3;
		};

		template <>
		struct GPIOPinTrait<PortID::A, PinID::_4> {
			static constexpr uint32_t pn = 4;
		};

		template <>
		struct GPIOPinTrait<PortID::A, PinID::_5> {
			static constexpr uint32_t pn = 5;
		};

		template <>
		struct GPIOPinTrait<PortID::A, PinID::_6> {
			static constexpr uint32_t pn = 6;
		};

		template <>
		struct GPIOPinTrait<PortID::A, PinID::_7> {
			static constexpr uint32_t pn = 7;
		};

		template <>
		struct GPIOPinTrait<PortID::A, PinID::_8> {
			static constexpr uint32_t pn = 8;
		};

		template <>
		struct GPIOPinTrait<PortID::A, PinID::_9> {
			static constexpr uint32_t pn = 9;
		};

		template <>
		struct GPIOPinTrait<PortID::A, PinID::_10> {
			static constexpr uint32_t pn = 10;
		};

		template <>
		struct GPIOPinTrait<PortID::A, PinID::_11> {
			static constexpr uint32_t pn = 11;
		};

		template <>
		struct GPIOPinTrait<PortID::A, PinID::_12> {
			static constexpr uint32_t pn = 12;
		};

		template <>
		struct GPIOPinTrait<PortID::A, PinID::_13> {
			static constexpr uint32_t pn = 13;
		};

		template <>
		struct GPIOPinTrait<PortID::A, PinID::_14> {
			static constexpr uint32_t pn = 14;
		};

		template <>
		struct GPIOPinTrait<PortID::A, PinID::_15> {
			static constexpr uint32_t pn = 15;
		};
		#endif

		#ifdef HTL_GPIOB_EXIST
		template  <>
		struct HardwareInfo<PortID::B> {
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
		struct GPIOPinTrait<PortID::B, PinID::_0> {
			static constexpr uint32_t pn = 0;
		};

		template <>
		struct GPIOPinTrait<PortID::B, PinID::_1> {
			static constexpr uint32_t pn = 1;
		};

		template <>
		struct GPIOPinTrait<PortID::B, PinID::_2> {
			static constexpr uint32_t pn = 2;
		};

		template <>
		struct GPIOPinTrait<PortID::B, PinID::_3> {
			static constexpr uint32_t pn = 3;
		};

		template <>
		struct GPIOPinTrait<PortID::B, PinID::_4> {
			static constexpr uint32_t pn = 4;
		};

		template <>
		struct GPIOPinTrait<PortID::B, PinID::_5> {
			static constexpr uint32_t pn = 5;
		};

		template <>
		struct GPIOPinTrait<PortID::B, PinID::_6> {
			static constexpr uint32_t pn = 6;
		};

		template <>
		struct GPIOPinTrait<PortID::B, PinID::_7> {
			static constexpr uint32_t pn = 7;
		};

		template <>
		struct GPIOPinTrait<PortID::B, PinID::_8> {
			static constexpr uint32_t pn = 8;
		};

		template <>
		struct GPIOPinTrait<PortID::B, PinID::_9> {
			static constexpr uint32_t pn = 9;
		};

		template <>
		struct GPIOPinTrait<PortID::B, PinID::_10> {
			static constexpr uint32_t pn = 10;
		};

		template <>
		struct GPIOPinTrait<PortID::B, PinID::_11> {
			static constexpr uint32_t pn = 11;
		};

		template <>
		struct GPIOPinTrait<PortID::B, PinID::_12> {
			static constexpr uint32_t pn = 12;
		};

		template <>
		struct GPIOPinTrait<PortID::B, PinID::_13> {
			static constexpr uint32_t pn = 13;
		};

		template <>
		struct GPIOPinTrait<PortID::B, PinID::_14> {
			static constexpr uint32_t pn = 14;
		};

		template <>
		struct GPIOPinTrait<PortID::B, PinID::_15> {
			static constexpr uint32_t pn = 15;
		};
		#endif

		#ifdef HTL_GPIOC_EXIST
		template  <>
		struct HardwareInfo<PortID::C> {
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
		struct GPIOPinTrait<PortID::C, PinID::_0> {
			static constexpr uint32_t pn = 0;
		};

		template <>
		struct GPIOPinTrait<PortID::C, PinID::_1> {
			static constexpr uint32_t pn = 1;
		};

		template <>
		struct GPIOPinTrait<PortID::C, PinID::_2> {
			static constexpr uint32_t pn = 2;
		};

		template <>
		struct GPIOPinTrait<PortID::C, PinID::_3> {
			static constexpr uint32_t pn = 3;
		};

		template <>
		struct GPIOPinTrait<PortID::C, PinID::_4> {
			static constexpr uint32_t pn = 4;
		};

		template <>
		struct GPIOPinTrait<PortID::C, PinID::_5> {
			static constexpr uint32_t pn = 5;
		};

		template <>
		struct GPIOPinTrait<PortID::C, PinID::_6> {
			static constexpr uint32_t pn = 6;
		};

		template <>
		struct GPIOPinTrait<PortID::C, PinID::_7> {
			static constexpr uint32_t pn = 7;
		};

		template <>
		struct GPIOPinTrait<PortID::C, PinID::_8> {
			static constexpr uint32_t pn = 8;
		};

		template <>
		struct GPIOPinTrait<PortID::C, PinID::_9> {
			static constexpr uint32_t pn = 9;
		};

		template <>
		struct GPIOPinTrait<PortID::C, PinID::_10> {
			static constexpr uint32_t pn = 10;
		};

		template <>
		struct GPIOPinTrait<PortID::C, PinID::_11> {
			static constexpr uint32_t pn = 11;
		};

		template <>
		struct GPIOPinTrait<PortID::C, PinID::_12> {
			static constexpr uint32_t pn = 12;
		};

		template <>
		struct GPIOPinTrait<PortID::C, PinID::_13> {
			static constexpr uint32_t pn = 13;
		};

		template <>
		struct GPIOPinTrait<PortID::C, PinID::_14> {
			static constexpr uint32_t pn = 14;
		};

		template <>
		struct GPIOPinTrait<PortID::C, PinID::_15> {
			static constexpr uint32_t pn = 15;
		};
		#endif

		#ifdef HTL_GPIOD_EXIST
		template  <>
		struct HardwareInfo<PortID::D> {
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
		struct GPIOPinTrait<PortID::D, PinID::_0> {
			static constexpr uint32_t pn = 0;
		};

		template <>
		struct GPIOPinTrait<PortID::D, PinID::_1> {
			static constexpr uint32_t pn = 1;
		};

		template <>
		struct GPIOPinTrait<PortID::D, PinID::_2> {
			static constexpr uint32_t pn = 2;
		};

		template <>
		struct GPIOPinTrait<PortID::D, PinID::_3> {
			static constexpr uint32_t pn = 3;
		};

		template <>
		struct GPIOPinTrait<PortID::D, PinID::_6> {
			static constexpr uint32_t pn = 6;
		};

		template <>
		struct GPIOPinTrait<PortID::D, PinID::_7> {
			static constexpr uint32_t pn = 7;
		};

		template <>
		struct GPIOPinTrait<PortID::D, PinID::_11> {
			static constexpr uint32_t pn = 11;
		};

		template <>
		struct GPIOPinTrait<PortID::D, PinID::_12> {
			static constexpr uint32_t pn = 12;
		};

		template <>
		struct GPIOPinTrait<PortID::D, PinID::_13> {
			static constexpr uint32_t pn = 13;
		};

		template <>
		struct GPIOPinTrait<PortID::D, PinID::_14> {
			static constexpr uint32_t pn = 14;
		};

		template <>
		struct GPIOPinTrait<PortID::D, PinID::_15> {
			static constexpr uint32_t pn = 15;
		};
		#endif

		#ifdef HTL_GPIOE_EXIST
		template  <>
		struct HardwareInfo<PortID::E> {
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
		struct GPIOPinTrait<PortID::E, PinID::_4> {
			static constexpr uint32_t pn = 4;
		};

		template <>
		struct GPIOPinTrait<PortID::E, PinID::_5> {
			static constexpr uint32_t pn = 5;
		};

		template <>
		struct GPIOPinTrait<PortID::E, PinID::_6> {
			static constexpr uint32_t pn = 6;
		};
		#endif

		#ifdef HTL_GPIOF_EXIST
		template  <>
		struct HardwareInfo<PortID::F> {
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
		struct GPIOPinTrait<PortID::F, PinID::_0> {
			static constexpr uint32_t pn = 0;
		};

		template <>
		struct GPIOPinTrait<PortID::F, PinID::_1> {
			static constexpr uint32_t pn = 1;
		};

		template <>
		struct GPIOPinTrait<PortID::F, PinID::_2> {
			static constexpr uint32_t pn = 2;
		};

		template <>
		struct GPIOPinTrait<PortID::F, PinID::_3> {
			static constexpr uint32_t pn = 3;
		};

		template <>
		struct GPIOPinTrait<PortID::F, PinID::_4> {
			static constexpr uint32_t pn = 4;
		};

		template <>
		struct GPIOPinTrait<PortID::F, PinID::_5> {
			static constexpr uint32_t pn = 5;
		};

		template <>
		struct GPIOPinTrait<PortID::F, PinID::_6> {
			static constexpr uint32_t pn = 6;
		};

		template <>
		struct GPIOPinTrait<PortID::F, PinID::_7> {
			static constexpr uint32_t pn = 7;
		};

		template <>
		struct GPIOPinTrait<PortID::F, PinID::_8> {
			static constexpr uint32_t pn = 8;
		};

		template <>
		struct GPIOPinTrait<PortID::F, PinID::_9> {
			static constexpr uint32_t pn = 9;
		};

		template <>
		struct GPIOPinTrait<PortID::F, PinID::_10> {
			static constexpr uint32_t pn = 10;
		};
		#endif

		#ifdef HTL_GPIOG_EXIST
		template  <>
		struct HardwareInfo<PortID::G> {
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
		struct GPIOPinTrait<PortID::G, PinID::_6> {
			static constexpr uint32_t pn = 6;
		};

		template <>
		struct GPIOPinTrait<PortID::G, PinID::_7> {
			static constexpr uint32_t pn = 7;
		};

		template <>
		struct GPIOPinTrait<PortID::G, PinID::_9> {
			static constexpr uint32_t pn = 9;
		};

		template <>
		struct GPIOPinTrait<PortID::G, PinID::_10> {
			static constexpr uint32_t pn = 10;
		};

		template <>
		struct GPIOPinTrait<PortID::G, PinID::_11> {
			static constexpr uint32_t pn = 11;
		};

		template <>
		struct GPIOPinTrait<PortID::G, PinID::_12> {
			static constexpr uint32_t pn = 12;
		};

		template <>
		struct GPIOPinTrait<PortID::G, PinID::_13> {
			static constexpr uint32_t pn = 13;
		};

		template <>
		struct GPIOPinTrait<PortID::G, PinID::_14> {
			static constexpr uint32_t pn = 14;
		};
		#endif

		#ifdef HTL_GPIOH_EXIST
		template  <>
		struct HardwareInfo<PortID::H> {
			static constexpr uint32_t gpioAddr = GPIOH_BASE;
			#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
			static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
			static constexpr uint32_t rccEnablePos = RCC_AHB1ENR_GPIOHEN_Pos;
			#endif
		};

		template <>
		struct GPIOPinTrait<PortID::H, PinID::_0> {
			static constexpr uint32_t pn = 0;
		};

		template <>
		struct GPIOPinTrait<PortID::H, PinID::_1> {
			static constexpr uint32_t pn = 1;
		};

		template <>
		struct GPIOPinTrait<PortID::H, PinID::_2> {
			static constexpr uint32_t pn = 2;
		};

		template <>
		struct GPIOPinTrait<PortID::H, PinID::_3> {
			static constexpr uint32_t pn = 3;
		};

		template <>
		struct GPIOPinTrait<PortID::H, PinID::_4> {
			static constexpr uint32_t pn = 4;
		};

		template <>
		struct GPIOPinTrait<PortID::H, PinID::_5> {
			static constexpr uint32_t pn = 5;
		};

		template <>
		struct GPIOPinTrait<PortID::H, PinID::_6> {
			static constexpr uint32_t pn = 6;
		};

		template <>
		struct GPIOPinTrait<PortID::H, PinID::_7> {
			static constexpr uint32_t pn = 7;
		};

		template <>
		struct GPIOPinTrait<PortID::H, PinID::_8> {
			static constexpr uint32_t pn = 8;
		};

		template <>
		struct GPIOPinTrait<PortID::H, PinID::_9> {
			static constexpr uint32_t pn = 9;
		};

		template <>
		struct GPIOPinTrait<PortID::H, PinID::_10> {
			static constexpr uint32_t pn = 10;
		};

		template <>
		struct GPIOPinTrait<PortID::H, PinID::_11> {
			static constexpr uint32_t pn = 11;
		};

		template <>
		struct GPIOPinTrait<PortID::H, PinID::_12> {
			static constexpr uint32_t pn = 12;
		};

		template <>
		struct GPIOPinTrait<PortID::H, PinID::_14> {
			static constexpr uint32_t pn = 14;
		};
		#endif

		#ifdef HTL_GPIOI_EXIST
		template  <>
		struct HardwareInfo<PortID::I> {
			static constexpr uint32_t gpioAddr = GPIOI_BASE;
			#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
			static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
			static constexpr uint32_t rccEnablePos = RCC_AHB1ENR_GPIOIEN_Pos;
			#endif
		};

		template <>
		struct GPIOPinTrait<PortID::I, PinID::_0> {
			static constexpr uint32_t pn = 0;
		};

		template <>
		struct GPIOPinTrait<PortID::I, PinID::_1> {
			static constexpr uint32_t pn = 1;
		};

		template <>
		struct GPIOPinTrait<PortID::I, PinID::_2> {
			static constexpr uint32_t pn = 2;
		};

		template <>
		struct GPIOPinTrait<PortID::I, PinID::_3> {
			static constexpr uint32_t pn = 3;
		};

		template <>
		struct GPIOPinTrait<PortID::I, PinID::_4> {
			static constexpr uint32_t pn = 4;
		};

		template <>
		struct GPIOPinTrait<PortID::I, PinID::_5> {
			static constexpr uint32_t pn = 5;
		};

		template <>
		struct GPIOPinTrait<PortID::I, PinID::_6> {
			static constexpr uint32_t pn = 6;
		};

		template <>
		struct GPIOPinTrait<PortID::I, PinID::_9> {
			static constexpr uint32_t pn = 9;
		};

		template <>
		struct GPIOPinTrait<PortID::I, PinID::_10> {
			static constexpr uint32_t pn = 10;
		};

		template <>
		struct GPIOPinTrait<PortID::I, PinID::_11> {
			static constexpr uint32_t pn = 11;
		};

		template <>
		struct GPIOPinTrait<PortID::I, PinID::_12> {
			static constexpr uint32_t pn = 12;
		};

		template <>
		struct GPIOPinTrait<PortID::I, PinID::_13> {
			static constexpr uint32_t pn = 13;
		};

		template <>
		struct GPIOPinTrait<PortID::I, PinID::_14> {
			static constexpr uint32_t pn = 14;
		};

		template <>
		struct GPIOPinTrait<PortID::I, PinID::_15> {
			static constexpr uint32_t pn = 15;
		};
		#endif

		#ifdef HTL_GPIOJ_EXIST
		template  <>
		struct HardwareInfo<PortID::J> {
			static constexpr uint32_t gpioAddr = GPIOJ_BASE;
			#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
			static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
			static constexpr uint32_t rccEnablePos = RCC_AHB1ENR_GPIOJEN_Pos;
			#endif
		};

		template <>
		struct GPIOPinTrait<PortID::J, PinID::_0> {
			static constexpr uint32_t pn = 0;
		};

		template <>
		struct GPIOPinTrait<PortID::J, PinID::_1> {
			static constexpr uint32_t pn = 1;
		};

		template <>
		struct GPIOPinTrait<PortID::J, PinID::_2> {
			static constexpr uint32_t pn = 2;
		};

		template <>
		struct GPIOPinTrait<PortID::J, PinID::_3> {
			static constexpr uint32_t pn = 3;
		};

		template <>
		struct GPIOPinTrait<PortID::J, PinID::_4> {
			static constexpr uint32_t pn = 4;
		};

		template <>
		struct GPIOPinTrait<PortID::J, PinID::_5> {
			static constexpr uint32_t pn = 5;
		};

		template <>
		struct GPIOPinTrait<PortID::J, PinID::_6> {
			static constexpr uint32_t pn = 6;
		};

		template <>
		struct GPIOPinTrait<PortID::J, PinID::_7> {
			static constexpr uint32_t pn = 7;
		};

		template <>
		struct GPIOPinTrait<PortID::J, PinID::_8> {
			static constexpr uint32_t pn = 8;
		};

		template <>
		struct GPIOPinTrait<PortID::J, PinID::_9> {
			static constexpr uint32_t pn = 9;
		};

		template <>
		struct GPIOPinTrait<PortID::J, PinID::_10> {
			static constexpr uint32_t pn = 10;
		};

		template <>
		struct GPIOPinTrait<PortID::J, PinID::_11> {
			static constexpr uint32_t pn = 11;
		};

		template <>
		struct GPIOPinTrait<PortID::J, PinID::_13> {
			static constexpr uint32_t pn = 13;
		};

		template <>
		struct GPIOPinTrait<PortID::J, PinID::_14> {
			static constexpr uint32_t pn = 14;
		};

		template <>
		struct GPIOPinTrait<PortID::J, PinID::_15> {
			static constexpr uint32_t pn = 15;
		};
		#endif

		#ifdef HTL_GPIOK_EXIST
		template  <>
		struct HardwareInfo<PortID::K> {
			static constexpr uint32_t gpioAddr = GPIOK_BASE;
			#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
			static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
			static constexpr uint32_t rccEnablePos = RCC_AHB1ENR_GPIOKEN_Pos;
			#endif
		};

		template <>
		struct GPIOPinTrait<PortID::K, PinID::_0> {
			static constexpr uint32_t pn = 0;
		};

		template <>
		struct GPIOPinTrait<PortID::K, PinID::_1> {
			static constexpr uint32_t pn = 1;
		};

		template <>
		struct GPIOPinTrait<PortID::K, PinID::_2> {
			static constexpr uint32_t pn = 2;
		};

		template <>
		struct GPIOPinTrait<PortID::K, PinID::_3> {
			static constexpr uint32_t pn = 3;
		};

		template <>
		struct GPIOPinTrait<PortID::K, PinID::_4> {
			static constexpr uint32_t pn = 4;
		};

		template <>
		struct GPIOPinTrait<PortID::K, PinID::_5> {
			static constexpr uint32_t pn = 5;
		};

		template <>
		struct GPIOPinTrait<PortID::K, PinID::_6> {
			static constexpr uint32_t pn = 6;
		};

		template <>
		struct GPIOPinTrait<PortID::K, PinID::_7> {
			static constexpr uint32_t pn = 7;
		};
		#endif
		}
	}
}


#endif // __STM32_htlGPIO__

/// @}
/// @}
/// @}

