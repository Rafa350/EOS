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
		enum class PinFunctionID {
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

		enum class Edge {
			falling,
			rising,
			all
		};


		class Port {
			private:
				GPIO_TypeDef * const _gpio;
			private:
				Port(const Port &) = delete;
				Port & operator = (const Port &) = delete;
			protected:
				Port(GPIO_TypeDef *gpio);
				virtual void activate(PinMask mask) = 0;
				virtual void deactivate(PinMask mask) = 0;
				virtual void reset() = 0;
			public:
				void initInput(PinMask mask, PullUpDn pull);
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
				virtual void activate() = 0;
				virtual void deactivate() = 0;
			public:
				void initInput(PullUpDn pull);
				void initOutput(OutDriver driver, Speed speed, InitPinState state = InitPinState::noChange);
				void initAnalogic();
				void initAlt(OutDriver driver, Speed speed, PinFunctionID pinFunctionID);
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


		enum class NotifyID {
			null,
			risingEdge,
			fallingEdge
		};

		struct NotifyEventArgs {
			NotifyID id;
			bool isr;
			union {
				struct {

				} RissingEdge;
				struct {

				} FallingEdge;
			};
		};

		class PinInterrupt;
		using INotifyEvent = eos::ICallbackP2<PinInterrupt*, NotifyEventArgs&>;
		template <typename instance_> using NotifyEvent = eos::CallbackP2<instance_, PinInterrupt*, NotifyEventArgs&>;


		class PinInterrupt {
			private:
				uint32_t _portNum;
				uint32_t _pinNum;
				INotifyEvent *_notifyEvent;
				bool _notifyEventEnabled;
			private:
				PinInterrupt(const PinInterrupt &) = delete;
				PinInterrupt & operator = (const PinInterrupt &) = delete;
				void notifyRisingEdge();
				void notifyFallingEdge();
			protected:
				PinInterrupt(GPIO_TypeDef *gpio, PinID pinID);
				void interruptService();
			public:
				void enableInterruptPin(Edge edge);
				void disableInterruptPin();
				void setNotifyEvent(INotifyEvent &event, bool enabled = true);
				inline void enableNotifyEvent() {
					_notifyEventEnabled = _notifyEvent != nullptr;
				}
				inline void disableEventEvent() {
					_notifyEventEnabled = false;
				}
		};

		typedef PinInterrupt *PinInterruptHandler;


		namespace internal {

			template <PortID>
			class PortActivator;

			template <PortID>
			struct HardwareInfo;
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
				void activate(PinMask mask) override {
					Activator::activate(mask);
				}
				void deactivate(PinMask mask) override {
					Activator::activate(mask);
				}
				void reset() override {
				}
			public:
				static constexpr PortX * getHandler() {
					return &_port;
				}
				inline static void interruptHandler() {
					getHandler()->interruptService();
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
		#ifdef HTL_GPIOH_EXIST
		typedef PortX<PortID::H> PortH;
		#endif
		#ifdef HTL_GPIOI_EXIST
		typedef PortX<PortID::I> PortI;
		#endif
		#ifdef HTL_GPIOJ_EXIST
		typedef PortX<PortID::J> PortJ;
		#endif
		#ifdef HTL_GPIOK_EXIST
		typedef PortX<PortID::K> PortK;
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
				void activate() override {
					Activator::activate(1 << uint32_t(pinID_));
				}
				void deactivate() override {
					Activator::activate(1 << uint32_t(pinID_));
				}
			public:
				static constexpr PinX * getHandler() {
					return &_pin;
				}
		};

		template <PortID portID_, PinID pinID_>
		PinX<portID_, pinID_> PinX<portID_, pinID_>::_pin;

		template <PortID portID_, PinID pinID_>
		inline PinX<portID_, pinID_> * getPinHandler() {
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
		#ifdef HTL_GPIOG_EXIST
		typedef PinX<PortID::G, PinID::_0> PinG0;
		typedef PinX<PortID::G, PinID::_1> PinG1;
		typedef PinX<PortID::G, PinID::_2> PinG2;
		typedef PinX<PortID::G, PinID::_3> PinG3;
		typedef PinX<PortID::G, PinID::_4> PinG4;
		typedef PinX<PortID::G, PinID::_5> PinG5;
		typedef PinX<PortID::G, PinID::_6> PinG6;
		typedef PinX<PortID::G, PinID::_7> PinG7;
		typedef PinX<PortID::G, PinID::_8> PinG8;
		typedef PinX<PortID::G, PinID::_9> PinG9;
		typedef PinX<PortID::G, PinID::_10> PinG10;
		typedef PinX<PortID::G, PinID::_11> PinG11;
		typedef PinX<PortID::G, PinID::_12> PinG12;
		typedef PinX<PortID::G, PinID::_13> PinG13;
		typedef PinX<PortID::G, PinID::_14> PinG14;
		typedef PinX<PortID::G, PinID::_15> PinG15;
		#endif
		#ifdef HTL_GPIOH_EXIST
		typedef PinX<PortID::H, PinID::_0> PinH0;
		typedef PinX<PortID::H, PinID::_1> PinH1;
		typedef PinX<PortID::H, PinID::_2> PinH2;
		typedef PinX<PortID::H, PinID::_3> PinH3;
		typedef PinX<PortID::H, PinID::_4> PinH4;
		typedef PinX<PortID::H, PinID::_5> PinH5;
		typedef PinX<PortID::H, PinID::_6> PinH6;
		typedef PinX<PortID::H, PinID::_7> PinH7;
		typedef PinX<PortID::H, PinID::_8> PinH8;
		typedef PinX<PortID::H, PinID::_9> PinH9;
		typedef PinX<PortID::H, PinID::_10> PinH10;
		typedef PinX<PortID::H, PinID::_11> PinH11;
		typedef PinX<PortID::H, PinID::_12> PinH12;
		typedef PinX<PortID::H, PinID::_13> PinH13;
		typedef PinX<PortID::H, PinID::_14> PinH14;
		typedef PinX<PortID::H, PinID::_15> PinH15;
		#endif
		#ifdef HTL_GPIOI_EXIST
		typedef PinX<PortID::I, PinID::_0> PinI0;
		typedef PinX<PortID::I, PinID::_1> PinI1;
		typedef PinX<PortID::I, PinID::_2> PinI2;
		typedef PinX<PortID::I, PinID::_3> PinI3;
		typedef PinX<PortID::I, PinID::_4> PinI4;
		typedef PinX<PortID::I, PinID::_5> PinI5;
		typedef PinX<PortID::I, PinID::_6> PinI6;
		typedef PinX<PortID::I, PinID::_7> PinI7;
		typedef PinX<PortID::I, PinID::_8> PinI8;
		typedef PinX<PortID::I, PinID::_9> PinI9;
		typedef PinX<PortID::I, PinID::_10> PinI10;
		typedef PinX<PortID::I, PinID::_11> PinI11;
		typedef PinX<PortID::I, PinID::_12> PinI12;
		typedef PinX<PortID::I, PinID::_13> PinI13;
		typedef PinX<PortID::I, PinID::_14> PinI14;
		typedef PinX<PortID::I, PinID::_15> PinI15;
		#endif
		#ifdef HTL_GPIOJ_EXIST
		typedef PinX<PortID::J, PinID::_0> PinJ0;
		typedef PinX<PortID::J, PinID::_1> PinJ1;
		typedef PinX<PortID::J, PinID::_2> PinJ2;
		typedef PinX<PortID::J, PinID::_3> PinJ3;
		typedef PinX<PortID::J, PinID::_4> PinJ4;
		typedef PinX<PortID::J, PinID::_5> PinJ5;
		typedef PinX<PortID::J, PinID::_6> PinJ6;
		typedef PinX<PortID::J, PinID::_7> PinJ7;
		typedef PinX<PortID::J, PinID::_8> PinJ8;
		typedef PinX<PortID::J, PinID::_9> PinJ9;
		typedef PinX<PortID::J, PinID::_10> PinJ10;
		typedef PinX<PortID::J, PinID::_11> PinJ11;
		typedef PinX<PortID::J, PinID::_12> PinJ12;
		typedef PinX<PortID::J, PinID::_13> PinJ13;
		typedef PinX<PortID::J, PinID::_14> PinJ14;
		typedef PinX<PortID::J, PinID::_15> PinJ15;
		#endif
		#ifdef HTL_GPIOK_EXIST
		typedef PinX<PortID::K, PinID::_0> PinK0;
		typedef PinX<PortID::K, PinID::_1> PinK1;
		typedef PinX<PortID::K, PinID::_2> PinK2;
		typedef PinX<PortID::K, PinID::_3> PinK3;
		typedef PinX<PortID::K, PinID::_4> PinK4;
		typedef PinX<PortID::K, PinID::_5> PinK5;
		typedef PinX<PortID::K, PinID::_6> PinK6;
		typedef PinX<PortID::K, PinID::_7> PinK7;
		typedef PinX<PortID::K, PinID::_8> PinK8;
		typedef PinX<PortID::K, PinID::_9> PinK9;
		typedef PinX<PortID::K, PinID::_10> PinK10;
		typedef PinX<PortID::K, PinID::_11> PinK11;
		typedef PinX<PortID::K, PinID::_12> PinK12;
		typedef PinX<PortID::K, PinID::_13> PinK13;
		typedef PinX<PortID::K, PinID::_14> PinK14;
		typedef PinX<PortID::K, PinID::_15> PinK15;
		#endif


		template <PortID portID_, PinID pinID_>
		class PinInterruptX final: public PinInterrupt {
			private:
				using HI = internal::HardwareInfo<portID_>;
			private:
				static constexpr uint32_t _gpioAddr = HI::gpioAddr;
				static PinInterruptX _pin;
			public:
				static constexpr PortID portID = portID_;
				static constexpr PinID pinID = pinID_;
			private:
				PinInterruptX():
					PinInterrupt(reinterpret_cast<GPIO_TypeDef*>(_gpioAddr), pinID_) {
				}
			public:
				static constexpr PinInterruptX * getHandler() {
					return &_pin;
				}
				inline static void interruptHandler() {
					getHandler()->interruptService();
				}
		};

		template <PortID portID_, PinID pinID_>
		PinInterruptX<portID_, pinID_> PinInterruptX<portID_, pinID_>::_pin;

		template <PortID portID_, PinID pinID_>
		inline PinInterruptX<portID_, pinID_> * getPinInterruptHandler() {
			return PinInterruptX<portID_, pinID_>::getHandler();
		}


		namespace internal {

			template <PortID portId_>
			class PortActivator final {
				private:
					using HI = internal::HardwareInfo<portId_>;
					static constexpr uint32_t _rccEnableAddr = HI::rccEnableAddr;
					static constexpr uint32_t _rccEnablePos = HI::rccEnablePos;
					static constexpr uint32_t _rccResetAddr = HI::rccResetAddr;
					static constexpr uint32_t _rccResetPos = HI::rccResetPos;
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
			#endif
		}
	}
}


#endif // __STM32_htlGPIO__

/// @}
/// @}
/// @}

