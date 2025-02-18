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
			portA,
			#endif
			#ifdef HTL_GPIOB_EXIST
			portB,
			#endif
			#ifdef HTL_GPIOC_EXIST
			portC,
			#endif
			#ifdef HTL_GPIOD_EXIST
			portD,
			#endif
			#ifdef HTL_GPIOE_EXIST
			portE,
			#endif
			#ifdef HTL_GPIOF_EXIST
			portF,
			#endif
			#ifdef HTL_GPIOG_EXIST
			portG,
			#endif
			#ifdef HTL_GPIOH_EXIST
			portH,
			#endif
			#ifdef HTL_GPIOI_EXIST
			portI,
			#endif
			#ifdef HTL_GPIOJ_EXIST
			portJ,
			#endif
			#ifdef HTL_GPIOK_EXIST
			portK,
			#endif
		};

		/// Identificador dels pins.
		///
		enum class PinID {
			pin0,
			pin1,
			pin2,
			pin3,
			pin4,
			pin5,
			pin6,
			pin7,
			pin8,
			pin9,
			pin10,
			pin11,
			pin12,
			pin13,
			pin14,
			pin15
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
        typedef PortDeviceX<PortID::portA> PortA;
        #endif
        #ifdef HTL_GPIOB_EXIST
        typedef PortDeviceX<PortID::portB> PortB;
        #endif
        #ifdef HTL_GPIOC_EXIST
        typedef PortDeviceX<PortID::portC> PortC;
        #endif
        #ifdef HTL_GPIOD_EXIST
        typedef PortDeviceX<PortID::portD> PortD;
        #endif
        #ifdef HTL_GPIOE_EXIST
        typedef PortDeviceX<PortID::portE> PortE;
        #endif
        #ifdef HTL_GPIOF_EXIST
        typedef PortDeviceX<PortID::portF> PortF;
        #endif
        #ifdef HTL_GPIOG_EXIST
        typedef PortDeviceX<PortID::portG> PortG;
        #endif
        #ifdef HTL_GPIOH_EXIST
        typedef PortDeviceX<PortID::portH> PortH;
        #endif
        #ifdef HTL_GPIOI_EXIST
        typedef PortDeviceX<PortID::portI> PortI;
        #endif
        #ifdef HTL_GPIOJ_EXIST
        typedef PortDeviceX<PortID::portJ> PortJ;
        #endif
        #ifdef HTL_GPIOK_EXIST
        typedef PortDeviceX<PortID::portK> PortK;
        #endif
        #ifdef HTL_GPIOA_EXIST

        typedef PinX<PortID::portA, PinID::pin0> PinA0;
        typedef PinX<PortID::portA, PinID::pin1> PinA1;
        typedef PinX<PortID::portA, PinID::pin2> PinA2;
        typedef PinX<PortID::portA, PinID::pin3> PinA3;
        typedef PinX<PortID::portA, PinID::pin4> PinA4;
        typedef PinX<PortID::portA, PinID::pin5> PinA5;
        typedef PinX<PortID::portA, PinID::pin6> PinA6;
        typedef PinX<PortID::portA, PinID::pin7> PinA7;
        typedef PinX<PortID::portA, PinID::pin8> PinA8;
        typedef PinX<PortID::portA, PinID::pin9> PinA9;
        typedef PinX<PortID::portA, PinID::pin10> PinA10;
        typedef PinX<PortID::portA, PinID::pin11> PinA11;
        typedef PinX<PortID::portA, PinID::pin12> PinA12;
        typedef PinX<PortID::portA, PinID::pin13> PinA13;
        typedef PinX<PortID::portA, PinID::pin14> PinA14;
        typedef PinX<PortID::portA, PinID::pin15> PinA15;
        #endif
        #ifdef HTL_GPIOB_EXIST
        typedef PinX<PortID::portB, PinID::pin0> PinB0;
        typedef PinX<PortID::portB, PinID::pin1> PinB1;
        typedef PinX<PortID::portB, PinID::pin2> PinB2;
        typedef PinX<PortID::portB, PinID::pin3> PinB3;
        typedef PinX<PortID::portB, PinID::pin4> PinB4;
        typedef PinX<PortID::portB, PinID::pin5> PinB5;
        typedef PinX<PortID::portB, PinID::pin6> PinB6;
        typedef PinX<PortID::portB, PinID::pin7> PinB7;
        typedef PinX<PortID::portB, PinID::pin8> PinB8;
        typedef PinX<PortID::portB, PinID::pin9> PinB9;
        typedef PinX<PortID::portB, PinID::pin10> PinB10;
        typedef PinX<PortID::portB, PinID::pin11> PinB11;
        typedef PinX<PortID::portB, PinID::pin12> PinB12;
        typedef PinX<PortID::portB, PinID::pin13> PinB13;
        typedef PinX<PortID::portB, PinID::pin14> PinB14;
        typedef PinX<PortID::portB, PinID::pin15> PinB15;
        #endif
        #ifdef HTL_GPIOC_EXIST
        typedef PinX<PortID::portC, PinID::pin0> PinC0;
        typedef PinX<PortID::portC, PinID::pin1> PinC1;
        typedef PinX<PortID::portC, PinID::pin2> PinC2;
        typedef PinX<PortID::portC, PinID::pin3> PinC3;
        typedef PinX<PortID::portC, PinID::pin4> PinC4;
        typedef PinX<PortID::portC, PinID::pin5> PinC5;
        typedef PinX<PortID::portC, PinID::pin6> PinC6;
        typedef PinX<PortID::portC, PinID::pin7> PinC7;
        typedef PinX<PortID::portC, PinID::pin8> PinC8;
        typedef PinX<PortID::portC, PinID::pin9> PinC9;
        typedef PinX<PortID::portC, PinID::pin10> PinC10;
        typedef PinX<PortID::portC, PinID::pin11> PinC11;
        typedef PinX<PortID::portC, PinID::pin12> PinC12;
        typedef PinX<PortID::portC, PinID::pin13> PinC13;
        typedef PinX<PortID::portC, PinID::pin14> PinC14;
        typedef PinX<PortID::portC, PinID::pin15> PinC15;
        #endif
        #ifdef HTL_GPIOD_EXIST
        typedef PinX<PortID::portD, PinID::pin0> PinD0;
        typedef PinX<PortID::portD, PinID::pin1> PinD1;
        typedef PinX<PortID::portD, PinID::pin2> PinD2;
        typedef PinX<PortID::portD, PinID::pin3> PinD3;
        typedef PinX<PortID::portD, PinID::pin4> PinD4;
        typedef PinX<PortID::portD, PinID::pin5> PinD5;
        typedef PinX<PortID::portD, PinID::pin6> PinD6;
        typedef PinX<PortID::portD, PinID::pin7> PinD7;
        typedef PinX<PortID::portD, PinID::pin8> PinD8;
        typedef PinX<PortID::portD, PinID::pin9> PinD9;
        typedef PinX<PortID::portD, PinID::pin10> PinD10;
        typedef PinX<PortID::portD, PinID::pin11> PinD11;
        typedef PinX<PortID::portD, PinID::pin12> PinD12;
        typedef PinX<PortID::portD, PinID::pin13> PinD13;
        typedef PinX<PortID::portD, PinID::pin14> PinD14;
        typedef PinX<PortID::portD, PinID::pin15> PinD15;
        #endif
        #ifdef HTL_GPIOE_EXIST
        typedef PinX<PortID::portE, PinID::pin0> PinE0;
        typedef PinX<PortID::portE, PinID::pin1> PinE1;
        typedef PinX<PortID::portE, PinID::pin2> PinE2;
        typedef PinX<PortID::portE, PinID::pin3> PinE3;
        typedef PinX<PortID::portE, PinID::pin4> PinE4;
        typedef PinX<PortID::portE, PinID::pin5> PinE5;
        typedef PinX<PortID::portE, PinID::pin6> PinE6;
        typedef PinX<PortID::portE, PinID::pin7> PinE7;
        typedef PinX<PortID::portE, PinID::pin8> PinE8;
        typedef PinX<PortID::portE, PinID::pin9> PinE9;
        typedef PinX<PortID::portE, PinID::pin10> PinE10;
        typedef PinX<PortID::portE, PinID::pin11> PinE11;
        typedef PinX<PortID::portE, PinID::pin12> PinE12;
        typedef PinX<PortID::portE, PinID::pin13> PinE13;
        typedef PinX<PortID::portE, PinID::pin14> PinE14;
        typedef PinX<PortID::portE, PinID::pin15> PinE15;
        #endif
        #ifdef HTL_GPIOF_EXIST
        typedef PinX<PortID::portF, PinID::pin0> PinF0;
        typedef PinX<PortID::portF, PinID::pin1> PinF1;
        typedef PinX<PortID::portF, PinID::pin2> PinF2;
        typedef PinX<PortID::portF, PinID::pin3> PinF3;
        typedef PinX<PortID::portF, PinID::pin4> PinF4;
        typedef PinX<PortID::portF, PinID::pin5> PinF5;
        typedef PinX<PortID::portF, PinID::pin6> PinF6;
        typedef PinX<PortID::portF, PinID::pin7> PinF7;
        typedef PinX<PortID::portF, PinID::pin8> PinF8;
        typedef PinX<PortID::portF, PinID::pin9> PinF9;
        typedef PinX<PortID::portF, PinID::pin10> PinF10;
        typedef PinX<PortID::portF, PinID::pin11> PinF11;
        typedef PinX<PortID::portF, PinID::pin12> PinF12;
        typedef PinX<PortID::portF, PinID::pin13> PinF13;
        typedef PinX<PortID::portF, PinID::pin14> PinF14;
        typedef PinX<PortID::portF, PinID::pin15> PinF15;
        #endif
        #ifdef HTL_GPIOG_EXIST
        typedef PinX<PortID::portG, PinID::pin0> PinG0;
        typedef PinX<PortID::portG, PinID::pin1> PinG1;
        typedef PinX<PortID::portG, PinID::pin2> PinG2;
        typedef PinX<PortID::portG, PinID::pin3> PinG3;
        typedef PinX<PortID::portG, PinID::pin4> PinG4;
        typedef PinX<PortID::portG, PinID::pin5> PinG5;
        typedef PinX<PortID::portG, PinID::pin6> PinG6;
        typedef PinX<PortID::portG, PinID::pin7> PinG7;
        typedef PinX<PortID::portG, PinID::pin8> PinG8;
        typedef PinX<PortID::portG, PinID::pin9> PinG9;
        typedef PinX<PortID::portG, PinID::pin10> PinG10;
        typedef PinX<PortID::portG, PinID::pin11> PinG11;
        typedef PinX<PortID::portG, PinID::pin12> PinG12;
        typedef PinX<PortID::portG, PinID::pin13> PinG13;
        typedef PinX<PortID::portG, PinID::pin14> PinG14;
        typedef PinX<PortID::portG, PinID::pin15> PinG15;
        #endif
        #ifdef HTL_GPIOH_EXIST
        typedef PinX<PortID::portH, PinID::pin0> PinH0;
        typedef PinX<PortID::portH, PinID::pin1> PinH1;
        typedef PinX<PortID::portH, PinID::pin2> PinH2;
        typedef PinX<PortID::portH, PinID::pin3> PinH3;
        typedef PinX<PortID::portH, PinID::pin4> PinH4;
        typedef PinX<PortID::portH, PinID::pin5> PinH5;
        typedef PinX<PortID::portH, PinID::pin6> PinH6;
        typedef PinX<PortID::portH, PinID::pin7> PinH7;
        typedef PinX<PortID::portH, PinID::pin8> PinH8;
        typedef PinX<PortID::portH, PinID::pin9> PinH9;
        typedef PinX<PortID::portH, PinID::pin10> PinH10;
        typedef PinX<PortID::portH, PinID::pin11> PinH11;
        typedef PinX<PortID::portH, PinID::pin12> PinH12;
        typedef PinX<PortID::portH, PinID::pin13> PinH13;
        typedef PinX<PortID::portH, PinID::pin14> PinH14;
        typedef PinX<PortID::portH, PinID::pin15> PinH15;
        #endif
        #ifdef HTL_GPIOI_EXIST
        typedef PinX<PortID::portI, PinID::pin0> PinI0;
        typedef PinX<PortID::portI, PinID::pin1> PinI1;
        typedef PinX<PortID::portI, PinID::pin2> PinI2;
        typedef PinX<PortID::portI, PinID::pin3> PinI3;
        typedef PinX<PortID::portI, PinID::pin4> PinI4;
        typedef PinX<PortID::portI, PinID::pin5> PinI5;
        typedef PinX<PortID::portI, PinID::pin6> PinI6;
        typedef PinX<PortID::portI, PinID::pin7> PinI7;
        typedef PinX<PortID::portI, PinID::pin8> PinI8;
        typedef PinX<PortID::portI, PinID::pin9> PinI9;
        typedef PinX<PortID::portI, PinID::pin10> PinI10;
        typedef PinX<PortID::portI, PinID::pin11> PinI11;
        typedef PinX<PortID::portI, PinID::pin12> PinI12;
        typedef PinX<PortID::portI, PinID::pin13> PinI13;
        typedef PinX<PortID::portI, PinID::pin14> PinI14;
        typedef PinX<PortID::portI, PinID::pin15> PinI15;
        #endif
        #ifdef HTL_GPIOJ_EXIST
        typedef PinX<PortID::portJ, PinID::pin0> PinJ0;
        typedef PinX<PortID::portJ, PinID::pin1> PinJ1;
        typedef PinX<PortID::portJ, PinID::pin2> PinJ2;
        typedef PinX<PortID::portJ, PinID::pin3> PinJ3;
        typedef PinX<PortID::portJ, PinID::pin4> PinJ4;
        typedef PinX<PortID::portJ, PinID::pin5> PinJ5;
        typedef PinX<PortID::portJ, PinID::pin6> PinJ6;
        typedef PinX<PortID::portJ, PinID::pin7> PinJ7;
        typedef PinX<PortID::portJ, PinID::pin8> PinJ8;
        typedef PinX<PortID::portJ, PinID::pin9> PinJ9;
        typedef PinX<PortID::portJ, PinID::pin10> PinJ10;
        typedef PinX<PortID::portJ, PinID::pin11> PinJ11;
        typedef PinX<PortID::portJ, PinID::pin12> PinJ12;
        typedef PinX<PortID::portJ, PinID::pin13> PinJ13;
        typedef PinX<PortID::portJ, PinID::pin14> PinJ14;
        typedef PinX<PortID::portJ, PinID::pin15> PinJ15;
        #endif
        #ifdef HTL_GPIOK_EXIST
        typedef PinX<PortID::portK, PinID::pin0> PinK0;
        typedef PinX<PortID::portK, PinID::pin1> PinK1;
        typedef PinX<PortID::portK, PinID::pin2> PinK2;
        typedef PinX<PortID::portK, PinID::pin3> PinK3;
        typedef PinX<PortID::portK, PinID::pin4> PinK4;
        typedef PinX<PortID::portK, PinID::pin5> PinK5;
        typedef PinX<PortID::portK, PinID::pin6> PinK6;
        typedef PinX<PortID::portK, PinID::pin7> PinK7;
        typedef PinX<PortID::portK, PinID::pin8> PinK8;
        typedef PinX<PortID::portK, PinID::pin9> PinK9;
        typedef PinX<PortID::portK, PinID::pin10> PinK10;
        typedef PinX<PortID::portK, PinID::pin11> PinK11;
        typedef PinX<PortID::portK, PinID::pin12> PinK12;
        typedef PinX<PortID::portK, PinID::pin13> PinK13;
        typedef PinX<PortID::portK, PinID::pin14> PinK14;
        typedef PinX<PortID::portK, PinID::pin15> PinK15;
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
			struct PortTraits<PortID::portA> {
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
			struct PortTraits<PortID::portB> {
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
			struct PortTraits<PortID::portC> {
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
			struct PortTraits<PortID::portD> {
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
			struct PortTraits<PortID::portE> {
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
			struct PortTraits<PortID::portF> {
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
			struct PortTraits<PortID::portG> {
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
			struct PortTraits<PortID::portH> {
				static constexpr uint32_t gpioAddr = GPIOH_BASE;
				#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
				static constexpr uint32_t rccEnablePos = RCC_AHB1ENR_GPIOHEN_Pos;
				#endif
			};
			#endif

			#ifdef HTL_GPIOI_EXIST
			template  <>
			struct PortTraits<PortID::portI> {
				static constexpr uint32_t gpioAddr = GPIOI_BASE;
				#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
				static constexpr uint32_t rccEnablePos = RCC_AHB1ENR_GPIOIEN_Pos;
				#endif
			};
			#endif

			#ifdef HTL_GPIOJ_EXIST
			template  <>
			struct PortTraits<PortID::portJ> {
				static constexpr uint32_t gpioAddr = GPIOJ_BASE;
				#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
				static constexpr uint32_t rccEnablePos = RCC_AHB1ENR_GPIOJEN_Pos;
				#endif
			};
			#endif

			#ifdef HTL_GPIOK_EXIST
			template  <>
			struct PortTraits<PortID::portK> {
				static constexpr uint32_t gpioAddr = GPIOK_BASE;
				#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
				static constexpr uint32_t rccEnablePos = RCC_AHB1ENR_GPIOKEN_Pos;
				#endif
			};
			#endif


			template <>
			struct PinTraits<PinID::pin0> {
		        static constexpr uint16_t mask {1 << 0};
		        static constexpr uint8_t bit {0};
			};

            template <>
			struct PinTraits<PinID::pin1> {
                static constexpr uint16_t mask {1 << 1};
                static constexpr uint8_t bit {1};
            };

            template <>
            struct PinTraits<PinID::pin2> {
                static constexpr uint16_t mask {1 << 2};
                static constexpr uint8_t bit {2};
            };

            template <>
            struct PinTraits<PinID::pin3> {
                static constexpr uint16_t mask {1 << 3};
                static constexpr uint8_t bit {3};
            };

            template <>
            struct PinTraits<PinID::pin4> {
                static constexpr uint16_t mask {1 << 4};
                static constexpr uint8_t bit {4};
            };

            template <>
            struct PinTraits<PinID::pin5> {
                static constexpr uint16_t mask {1 << 5};
                static constexpr uint8_t bit {5};
            };

            template <>
            struct PinTraits<PinID::pin6> {
                static constexpr uint16_t mask {1 << 6};
                static constexpr uint8_t bit {6};
            };

            template <>
            struct PinTraits<PinID::pin7> {
                static constexpr uint16_t mask {1 << 7};
                static constexpr uint8_t bit {7};
            };

            template <>
            struct PinTraits<PinID::pin8> {
                static constexpr uint16_t mask {1 << 8};
                static constexpr uint8_t bit {8};
            };

            template <>
            struct PinTraits<PinID::pin9> {
                static constexpr uint16_t mask {1 << 9};
                static constexpr uint8_t bit {9};
            };

            template <>
            struct PinTraits<PinID::pin10> {
                static constexpr uint16_t mask {1 << 10};
                static constexpr uint8_t bit {10};
            };

            template <>
            struct PinTraits<PinID::pin11> {
                static constexpr uint16_t mask {1 << 11};
                static constexpr uint8_t bit {11};
            };

            template <>
            struct PinTraits<PinID::pin12> {
                static constexpr uint16_t mask {1 << 12};
                static constexpr uint8_t bit {12};
            };

            template <>
            struct PinTraits<PinID::pin13> {
                static constexpr uint16_t mask {1 << 13};
                static constexpr uint8_t bit {13};
            };

            template <>
            struct PinTraits<PinID::pin14> {
                static constexpr uint16_t mask {1 << 14};
                static constexpr uint8_t bit {14};
            };

            template <>
            struct PinTraits<PinID::pin15> {
                static constexpr uint16_t mask {1 << 15};
                static constexpr uint8_t bit {15};
            };
		}
	}
}


#endif // __STM32_htlGPIO__
