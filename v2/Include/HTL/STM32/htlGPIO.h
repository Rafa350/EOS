#pragma once
#ifndef __STM32_htlGPIO__
#define __STM32_htlGPIO__


/// \file      htlGPIO.h
/// \author    Rafael Serrano (rsr.openware@gmail.com)
/// \brief     GPIO device manager.


// EOS includes
//
#include "HTL/STM32/htl.h"


namespace htl {

    namespace gpio {

		/// Identificador dels ports.
	    ///
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

		/// Identificador dels pins.
		///
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

        /// Bit del pin
        ///
		class PinBit final {
		    private:
		        uint8_t _value;
            public:
                constexpr explicit PinBit(uint8_t value) : _value {value} {}
                constexpr operator uint8_t () const { return _value; }
		};

        /// Mascara de pins
        ///
        class PinMask final {
            private:
                uint16_t _value;
            public:
                constexpr explicit PinMask(uint16_t value) : _value {value} {}
                constexpr explicit PinMask(PinBit bit) : _value {(uint16_t)(1 << bit)} {}
                constexpr operator uint16_t () const { return _value; }
        };

		/// Identificador de la funcio alternativa.
        ///
		enum class AlternateFunction {
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

		/// Modus d'entrada.
		///
		enum class InputMode {
			floating,
			pullUp,
			pullDown
		};

		/// Modus de sortida.
		///
		enum class OutputMode {
			pushPull,
			openDrain,
			openDrainPullUp
		};

		/// Modus alternatiu
		///
		enum class AlternateMode {
			pushPull,
			openDrain,
			openDrainPullUp
		};

		/// Opcions de velocitat.
		///
		enum class Speed {
			low,
			medium,
			high,
			fast
		};

		/// Modus d'inicialitzacio.
		///
        enum class InitMode {
            input,
            output,
            alternate,
            analogic
        };

        /// \brief Parametres d'inicialitzacio.
        ///
        struct InitInfo {
            InitMode mode;
            union {
                struct {
                    InputMode mode;
                } input;
                struct {
                    OutputMode mode;
                    Speed speed;
                    bool state;
                } output;
                struct {
                    AlternateMode mode;
                    Speed speed;
                    AlternateFunction function;
                } alternate;
                struct {
                } analogic;
            };
        };

        /// \brief Edge interrupcion selection
        ///
		enum class Edge {
            none,
			falling,
			rising,
			all
		};


		namespace internal {

            void initialize(GPIO_TypeDef * const gpio, PinMask mask, const InitInfo *info);
		    void initInput(GPIO_TypeDef * const gpio, PinMask mask,
		            InputMode mode);
            void initInput(GPIO_TypeDef * const gpio, PinBit bit,
                    InputMode mode);
		    void initOutput(GPIO_TypeDef * const gpio, PinMask mask,
		            OutputMode mode, Speed speed, bool state);
            void initOutput(GPIO_TypeDef * const gpio, PinBit bit,
                    OutputMode mode, Speed speed, bool state);
		    void initAlternate(GPIO_TypeDef * const gpio, PinMask mask,
		            AlternateMode mode, Speed speed, AlternateFunction af);
            void initAlternate(GPIO_TypeDef * const gpio, PinBit bit,
                    AlternateMode mode, Speed speed, AlternateFunction af);
		    void initAnalogic(GPIO_TypeDef * const gpio, PinMask mask);
            void initAnalogic(GPIO_TypeDef * const gpio, PinBit bit);
		    void deinitialize(GPIO_TypeDef * const gpio, PinMask mask);
            void deinitialize(GPIO_TypeDef * const gpio, PinBit bit);
		}

        namespace internal {

            template <PortID>
            class Activator;

            template <PortID>
            struct PortTraits;

            template <PinID>
            struct PinTraits;
        }

        /// brief Clase que representa un port.
        ///
		class PortDevice {
			private:
				GPIO_TypeDef * const _gpio;
			private:
				PortDevice(const PortDevice &) = delete;
				PortDevice & operator = (const PortDevice &) = delete;
			protected:
				PortDevice(GPIO_TypeDef *gpio);
				virtual void activate(PinMask mask) const = 0;
				virtual void deactivate(PinMask mask) const = 0;
			public:
				void initInput(PinMask mask, InputMode mode) const;
				void initOutput(PinMask mask, OutputMode mode, Speed speed = Speed::medium) const;
				void deinitialize() const;
				inline void set(PinMask mask) const {
					_gpio->BSRR = mask;
				}
				inline void set(PinBit bit) const {
					_gpio->BSRR = 1 << bit;
				}
				inline void clear(PinMask mask) const {
					_gpio->BSRR = mask << 16;
				}
				inline void clear(PinBit bit) const {
					_gpio->BSRR = 1 << (bit + 16);
				}
				inline void toggle(PinMask mask) const {
					_gpio->ODR ^= mask;
				}
				inline void toggle(PinBit bit) const {
					_gpio->ODR ^= 1 << bit;
				}
				inline PinMask read() const {
					return PinMask(_gpio->IDR);
				}
				inline bool read(PinBit bit) const {
					return (_gpio->IDR & (1 << bit)) ? true : false;
				}
				inline void write(PinMask mask) const {
					_gpio->ODR = mask;
				}
				inline void write(PinMask clearMask, PinMask setMask) const {
				    _gpio->BSRR = (clearMask << 16) | setMask;
				}
				inline void write(PinBit bit, bool state) const {
					_gpio->BSRR = 1 << (bit + (state ? 0 : 16));
				}
		};

        /// brief Clase que representa un port.
        ///
        template <PortID portID_>
        class PortDeviceX final: public PortDevice {
            private:
                using PortTraits = internal::PortTraits<portID_>;
                using Activator = internal::Activator<portID_>;
            private:
                static PortDeviceX _instance;
            public:
                static constexpr auto portID = portID_;
                static constexpr PortDeviceX *pInst = &_instance;
                static constexpr PortDeviceX &rInst = _instance;
            private:
                PortDeviceX():
                    PortDevice(reinterpret_cast<GPIO_TypeDef *>(PortTraits::gpioAddr)) {
                }
            protected:
                void activate(PinMask mask) const override {
                    Activator::activate(mask);
                }
                void deactivate(PinMask mask) const override {
                    Activator::activate(mask);
                }
            public:
                inline static void interruptHandler() {
                    _instance.interruptService();
                }
        };
        template <PortID portID_>
        PortDeviceX<portID_> PortDeviceX<portID_>::_instance;


        /// brief Clase que representa un pin individual.
        ///
		class PinDevice {
			private:
		        GPIO_TypeDef * const _gpio;
		        PinMask const _mask;

			private:
				PinDevice(const PinDevice &) = delete;
				PinDevice & operator = (const PinDevice &) = delete;

			protected:
                PinDevice(GPIO_TypeDef *gpio, PinBit bit);
				virtual void activate() const = 0;
				virtual void deactivate() const = 0;

			public:
                void initInput(InputMode mode) const;
                void initOutput(OutputMode mode, Speed speed, bool state) const;
                void initAlternate(AlternateMode mode, Speed speed, AlternateFunction af) const;
                void initAnalogic() const;
                void initialize(const InitInfo &info) const;
                void deinitialize() const;

				inline void set() const {
                    _gpio->BSRR = _mask;
				}
				inline void clear() const {
                    _gpio->BSRR = _mask << 16;
				}
				inline void toggle() const {
                    _gpio->ODR ^= _mask;
				}
				inline void write(bool state) const {
                    _gpio->BSRR = _mask << (state ? 0 : 16);
				}
				inline bool read() const {
					return (_gpio->IDR & _mask) != 0;
				}
		};

        /// brief Clase que representa un pin individual.
        ///
        template <PortID portID_, PinID pinID_>
        class PinDeviceX final: public PinDevice {
            private:
                using PortTraits = internal::PortTraits<portID_>;
                using PinTraits = internal::PinTraits<pinID_>;
                using Activator = internal::Activator<portID_>;

            private:
                static PinDeviceX _instance;
                static constexpr auto _mask = PinMask(PinTraits::mask);
                static constexpr auto _bit = PinBit(PinTraits::bit);
                static constexpr auto _gpioAddr = PortTraits::gpioAddr;

            public:
                static constexpr auto portID = portID_;
                static constexpr auto pinID = pinID_;
                static constexpr PinDeviceX *pInst = &_instance;
                static constexpr PinDeviceX &rInst = _instance;

            private:
                inline PinDeviceX():
                    PinDevice(reinterpret_cast<GPIO_TypeDef*>(_gpioAddr), _bit) {
                }

            protected:
                void activate() const override {
                    Activator::activate(_mask);
                }
                void deactivate() const override {
                    Activator::activate(_mask);
                }
        };

        template <PortID portID_, PinID pinID_>
        PinDeviceX<portID_, pinID_> PinDeviceX<portID_, pinID_>::_instance;


        /// brief Clase que representa un pin individual.
        ///
        template <PortID portID_, PinID pinID_>
        class PinX {
            private:
                using PortTraits = internal::PortTraits<portID_>;
                using PinTraits = internal::PinTraits<pinID_>;
                using Activator = internal::Activator<portID_>;

            private:
                static constexpr auto _gpioAddr = PortTraits::gpioAddr;
                static constexpr auto _mask = PinTraits::mask;
                static constexpr auto _bit = PinTraits::bit;

            public:
                static constexpr auto portID = portID_;
                static constexpr auto pinID = pinID_;
                static constexpr auto pInst = PinDeviceX<portID_, pinID_>::pInst;

            public:
                static void initInput(InputMode mode) {
                    auto mask = PinMask(_mask);
                    Activator::activate(mask);
                    auto gpio = reinterpret_cast<GPIO_TypeDef*>(_gpioAddr);
                    auto bit = PinBit(_bit);
                    internal::initInput(gpio, bit, mode);
                }

                static void initOutput(OutputMode mode, Speed speed, bool state) {
                    auto mask = PinMask(_mask);
                    Activator::activate(mask);
                    auto gpio = reinterpret_cast<GPIO_TypeDef*>(_gpioAddr);
                    auto bit = PinBit(_bit);
                    internal::initOutput(gpio, bit, mode, speed, state);
                }

                static void initAnalogic() {
                    auto mask = PinMask(_mask);
                    Activator::activate(mask);
                    auto gpio = reinterpret_cast<GPIO_TypeDef*>(_gpioAddr);
                    auto bit = PinBit(_bit);
                    internal::initAnalogic(gpio, bit);
                }

                static void initAlternate(AlternateMode mode, Speed speed, AlternateFunction af) {
                    auto mask = PinMask(_mask);
                    Activator::activate(PinMask(mask));
                    auto gpio = reinterpret_cast<GPIO_TypeDef*>(_gpioAddr);
                    auto bit = PinBit(_bit);
                    internal::initAlternate(gpio, bit, mode, speed, af);
                }

                static constexpr void deinitialize() {
                    auto gpio = reinterpret_cast<GPIO_TypeDef*>(_gpioAddr);
                    auto bit = PinBit(_bit);
                    internal::deinitialize(gpio, bit);
                    auto mask = PinMask(_mask);
                    Activator::deactivate(mask);
                }

                static constexpr void set() {
                    auto gpio = reinterpret_cast<GPIO_TypeDef*>(_gpioAddr);
                    gpio->BSRR = _mask;
                }

                static constexpr void clear() {
                    auto gpio = reinterpret_cast<GPIO_TypeDef*>(_gpioAddr);
                    gpio->BSRR = _mask << 16;
                }

                static constexpr void toggle() {
                    auto gpio = reinterpret_cast<GPIO_TypeDef*>(_gpioAddr);
                    gpio->ODR ^= _mask;
                }

                static constexpr void write(bool state) {
                    auto gpio = reinterpret_cast<GPIO_TypeDef*>(_gpioAddr);
                    gpio->BSRR = _mask << (state ? 0 : 16);
                }

                static constexpr bool read() {
                    auto gpio = reinterpret_cast<GPIO_TypeDef*>(_gpioAddr);
                    return (gpio->IDR & _mask) != 0;
                }
        };


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
		using INotifyEvent = eos::ICallbackP2<const PinInterrupt*, NotifyEventArgs&>;
		template <typename Instance_> using NotifyEvent = eos::CallbackP2<Instance_, const PinInterrupt*, NotifyEventArgs&>;

		class PinInterrupt {
			private:
				uint8_t const _portNum;
				uint8_t const _pinNum;
				INotifyEvent *_notifyEvent;
				bool _notifyEventEnabled;

			private:
				PinInterrupt(const PinInterrupt &) = delete;
				PinInterrupt & operator = (const PinInterrupt &) = delete;
				void notifyRisingEdge() const;
				void notifyFallingEdge() const;

			protected:
				PinInterrupt(GPIO_TypeDef *gpio, PinID pinID);
				void interruptService() const;

			public:
				void enableInterruptPin(Edge edge) const;
				void disableInterruptPin() const;

				void setNotifyEvent(INotifyEvent &event, bool enabled = true);

				inline void enableNotifyEvent() {
					_notifyEventEnabled = _notifyEvent != nullptr;
				}

				inline void disableEventEvent() {
					_notifyEventEnabled = false;
				}
		};

		template <PortID portID_, PinID pinID_>
		class PinInterruptX final: public PinInterrupt {
			private:
				using PortTraits = internal::PortTraits<portID_>;
			private:
				static constexpr uint32_t _gpioAddr = PortTraits::gpioAddr;
				static PinInterruptX _instance;
			public:
				static constexpr PortID portID = portID_;
				static constexpr PinID pinID = pinID_;
				static constexpr PinInterruptX *pInst = &_instance;
                static constexpr PinInterruptX &rInst = _instance;
			private:
				PinInterruptX():
					PinInterrupt(reinterpret_cast<GPIO_TypeDef*>(_gpioAddr), pinID_) {
				}
			public:
				inline static void interruptHandler() {
					_instance.interruptService();
				}
		};

		template <PortID portID_, PinID pinID_>
		PinInterruptX<portID_, pinID_> PinInterruptX<portID_, pinID_>::_instance;

        #ifdef HTL_GPIOA_EXIST
        typedef PortDeviceX<PortID::A> PortA;
        #endif
        #ifdef HTL_GPIOB_EXIST
        typedef PortDeviceX<PortID::B> PortB;
        #endif
        #ifdef HTL_GPIOC_EXIST
        typedef PortDeviceX<PortID::C> PortC;
        #endif
        #ifdef HTL_GPIOD_EXIST
        typedef PortDeviceX<PortID::D> PortD;
        #endif
        #ifdef HTL_GPIOE_EXIST
        typedef PortDeviceX<PortID::E> PortE;
        #endif
        #ifdef HTL_GPIOF_EXIST
        typedef PortDeviceX<PortID::F> PortF;
        #endif
        #ifdef HTL_GPIOG_EXIST
        typedef PortDeviceX<PortID::G> PortG;
        #endif
        #ifdef HTL_GPIOH_EXIST
        typedef PortDeviceX<PortID::H> PortH;
        #endif
        #ifdef HTL_GPIOI_EXIST
        typedef PortDeviceX<PortID::I> PortI;
        #endif
        #ifdef HTL_GPIOJ_EXIST
        typedef PortDeviceX<PortID::J> PortJ;
        #endif
        #ifdef HTL_GPIOK_EXIST
        typedef PortDeviceX<PortID::K> PortK;
        #endif
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

        namespace internal {

			template <PortID portId_>
			class Activator final {
				private:
					using PortTraits = internal::PortTraits<portId_>;

                private:
					static constexpr uint32_t _rccEnableAddr = PortTraits::rccEnableAddr;
					static constexpr uint32_t _rccEnablePos = PortTraits::rccEnablePos;

                private:
					static PinMask _mask;

				public:
					static void activate(PinMask mask) {
					    uint16_t m = uint16_t(_mask);
						if (!m) {
							uint32_t *p = reinterpret_cast<uint32_t*>(_rccEnableAddr);
							*p |= 1 << _rccEnablePos;
							__DSB();
						}
						m |= uint16_t(mask);
						_mask = PinMask(m);
					}

					static void deactivate(PinMask mask) {
                        uint16_t m = uint16_t(_mask);
                        m &= ~uint16_t(mask);
						if (!m) {
							uint32_t *p = reinterpret_cast<uint32_t*>(_rccEnableAddr);
							*p &= ~(1 << _rccEnablePos);
						}
                        _mask = PinMask(m);
					}
			};

			template <PortID portId_>
			PinMask Activator<portId_>::_mask {0};


			#ifdef HTL_GPIOA_EXIST
			template<>
			struct PortTraits<PortID::A> {
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
				#endif
			};
			#endif

			#ifdef HTL_GPIOB_EXIST
			template  <>
			struct PortTraits<PortID::B> {
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
				#endif
			};
			#endif

			#ifdef HTL_GPIOC_EXIST
			template  <>
			struct PortTraits<PortID::C> {
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
				#endif
			};
			#endif

			#ifdef HTL_GPIOD_EXIST
			template  <>
			struct PortTraits<PortID::D> {
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
				#endif
			};
			#endif

			#ifdef HTL_GPIOE_EXIST
			template  <>
			struct PortTraits<PortID::E> {
				static constexpr uint32_t gpioAddr = GPIOE_BASE;
				#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
				static constexpr uint32_t rccEnablePos = RCC_AHB1ENR_GPIOEEN_Pos;
				#elif defined(EOS_PLATFORM_STM32G0)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPENR);
				static constexpr uint32_t rccEnablePos = RCC_IOPENR_GPIOEEN_Pos;
				#endif
			};
			#endif

			#ifdef HTL_GPIOF_EXIST
			template  <>
			struct PortTraits<PortID::F> {
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
				#endif
			};
			#endif

			#ifdef HTL_GPIOG_EXIST
			template  <>
			struct PortTraits<PortID::G> {
				static constexpr uint32_t gpioAddr = GPIOG_BASE;
				#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
				static constexpr uint32_t rccEnablePos = RCC_AHB1ENR_GPIOGEN_Pos;
				#elif defined(EOS_PLATFORM_STM32G0)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPENR);
				static constexpr uint32_t rccEnablePos = RCC_IOPENR_GPIOGEN_Pos;
				#endif
			};
			#endif

			#ifdef HTL_GPIOH_EXIST
			template  <>
			struct PortTraits<PortID::H> {
				static constexpr uint32_t gpioAddr = GPIOH_BASE;
				#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
				static constexpr uint32_t rccEnablePos = RCC_AHB1ENR_GPIOHEN_Pos;
				#endif
			};
			#endif

			#ifdef HTL_GPIOI_EXIST
			template  <>
			struct PortTraits<PortID::I> {
				static constexpr uint32_t gpioAddr = GPIOI_BASE;
				#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
				static constexpr uint32_t rccEnablePos = RCC_AHB1ENR_GPIOIEN_Pos;
				#endif
			};
			#endif

			#ifdef HTL_GPIOJ_EXIST
			template  <>
			struct PortTraits<PortID::J> {
				static constexpr uint32_t gpioAddr = GPIOJ_BASE;
				#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
				static constexpr uint32_t rccEnablePos = RCC_AHB1ENR_GPIOJEN_Pos;
				#endif
			};
			#endif

			#ifdef HTL_GPIOK_EXIST
			template  <>
			struct PortTraits<PortID::K> {
				static constexpr uint32_t gpioAddr = GPIOK_BASE;
				#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
				static constexpr uint32_t rccEnablePos = RCC_AHB1ENR_GPIOKEN_Pos;
				#endif
			};
			#endif


			template <>
			struct PinTraits<PinID::_0> {
		        static constexpr uint16_t mask {1 << 0};
		        static constexpr uint8_t bit {0};
			};

            template <>
			struct PinTraits<PinID::_1> {
                static constexpr uint16_t mask {1 << 1};
                static constexpr uint8_t bit {1};
            };

            template <>
            struct PinTraits<PinID::_2> {
                static constexpr uint16_t mask {1 << 2};
                static constexpr uint8_t bit {2};
            };

            template <>
            struct PinTraits<PinID::_3> {
                static constexpr uint16_t mask {1 << 3};
                static constexpr uint8_t bit {3};
            };

            template <>
            struct PinTraits<PinID::_4> {
                static constexpr uint16_t mask {1 << 4};
                static constexpr uint8_t bit {4};
            };

            template <>
            struct PinTraits<PinID::_5> {
                static constexpr uint16_t mask {1 << 5};
                static constexpr uint8_t bit {5};
            };

            template <>
            struct PinTraits<PinID::_6> {
                static constexpr uint16_t mask {1 << 6};
                static constexpr uint8_t bit {6};
            };

            template <>
            struct PinTraits<PinID::_7> {
                static constexpr uint16_t mask {1 << 7};
                static constexpr uint8_t bit {7};
            };

            template <>
            struct PinTraits<PinID::_8> {
                static constexpr uint16_t mask {1 << 8};
                static constexpr uint8_t bit {8};
            };

            template <>
            struct PinTraits<PinID::_9> {
                static constexpr uint16_t mask {1 << 9};
                static constexpr uint8_t bit {9};
            };

            template <>
            struct PinTraits<PinID::_10> {
                static constexpr uint16_t mask {1 << 10};
                static constexpr uint8_t bit {10};
            };

            template <>
            struct PinTraits<PinID::_11> {
                static constexpr uint16_t mask {1 << 11};
                static constexpr uint8_t bit {11};
            };

            template <>
            struct PinTraits<PinID::_12> {
                static constexpr uint16_t mask {1 << 12};
                static constexpr uint8_t bit {12};
            };

            template <>
            struct PinTraits<PinID::_13> {
                static constexpr uint16_t mask {1 << 13};
                static constexpr uint8_t bit {13};
            };

            template <>
            struct PinTraits<PinID::_14> {
                static constexpr uint16_t mask {1 << 14};
                static constexpr uint8_t bit {14};
            };

            template <>
            struct PinTraits<PinID::_15> {
                static constexpr uint16_t mask {1 << 15};
                static constexpr uint8_t bit {15};
            };
		}
	}
}


#endif // __STM32_htlGPIO__
