#pragma once
#ifndef __STM32_htlGPIO__
#define __STM32_htlGPIO__


/// \file      htlGPIO.h
/// \author    Rafael Serrano (rsr.openware@gmail.com)
/// \brief     GPIO device manager.


// EOS includes
//
#include "HTL/htlBits.h"
#include "HTL/STM32/htl.h"


// Default options
//
#ifndef HTL_GPIO_OPTION_DEACTIVATE
	#define HTL_GPIO_OPTION_DEACTIVATE HTL_GPIO_DEFAULT_OPTION_DEACTIVATE
#endif


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

		/// Opcions de velocitat.
		///
		enum class Speed {
			low,
			medium,
			high,
			fast
		};

		// Opcio de resistencies pull up/down.
		//
		enum class PullUpDown {
			none,
			up,
			down
		};

		// Opcions del driver de sortida.
		//
		enum class OutputType {
			pushPull,
			openDrain
		};

		/// Modus d'inicialitzacio.
		///
        enum class InitMode {
            input,
            output,
            alternate,
            analogic
        };

		namespace internal {

            template <PortID>
            class PortActivator;

            template <PortID>
            struct PortTraits;

            template <PinID>
            struct PinTraits;
        }

#if HTL_GPIO_OPTION_DEACTIVATE == 1
		void deinitialize(GPIO_TypeDef * const gpio, PinMask mask);
		void deinitialize(GPIO_TypeDef * const gpio, PinBit bit);
#endif

		void initInput(GPIO_TypeDef * const gpio, PinMask mask, PullUpDown pupd);
		void initInput(GPIO_TypeDef * const gpio, PinBit bit, PullUpDown pupd);

		void initOutput(GPIO_TypeDef * const gpio, PinMask mask, OutputType type, PullUpDown pupd, Speed speed, bool state);
		void initOutput(GPIO_TypeDef * const gpio, PinBit bit, OutputType, PullUpDown pupd, Speed speed, bool state);

		void initAnalogic(GPIO_TypeDef * const gpio, PinMask mask);
		void initAnalogic(GPIO_TypeDef * const gpio, PinBit bit);

		void initAlternate(GPIO_TypeDef * const gpio, PinMask mask, OutputType type, PullUpDown pull, Speed speed, AlternateFunction af);
		void initAlternate(GPIO_TypeDef * const gpio, PinBit bit, OutputType type, PullUpDown pull, Speed speed, AlternateFunction af);

		template <PortID portID_, PinID pinID_>
		void initAlternate(OutputType type, PullUpDown pupd, Speed speed, AlternateFunction af) {

			using PortTraits = internal::PortTraits<portID_>;
            using PinTraits = internal::PinTraits<pinID_>;
            using PortActivator = internal::PortActivator<portID_>;

            PortActivator::activate(PinMask(PinTraits::mask));

            auto gpio = reinterpret_cast<GPIO_TypeDef*>(PortTraits::gpioAddr);
            initAlternate(gpio, PinBit(PinTraits::bit), type, pupd, speed, af);
		}

        /// brief Clase que representa un port.
        ///
		class PortDevice {
			private:
				GPIO_TypeDef * const _gpio;

			private:
				PortDevice(const PortDevice &) = delete;
				PortDevice & operator = (const PortDevice &) = delete;

			private:
				void activate(PinMask mask) const {
					activateImpl(mask);
				}
#if HTL_GPIO_OPTION_DEACTIVATE == 1
				void deactivate(PinMask mask) const {
					deactivateImpl(mask);
				}
#endif

			protected:
				PortDevice(GPIO_TypeDef *gpio);
				virtual void activateImpl(PinMask mask) const = 0;
#if HTL_GPIO_OPTION_DEACTIVATE == 1
				virtual void deactivateImpl(PinMask mask) const = 0;
#endif

			public:
				void initInput(PinMask mask, PullUpDown pupd) const;
				void initOutput(PinMask mask, OutputType type, PullUpDown pupd, Speed speed = Speed::medium) const;
#if HTL_GPIO_OPTION_DEACTIVATE == 1
				void deinitialize() const;
#endif
				void set(PinMask mask) const {
					_gpio->BSRR = mask;
				}
				void set(PinBit bit) const {
					_gpio->BSRR = 1 << bit;
				}
				void clear(PinMask mask) const {
					_gpio->BSRR = mask << 16;
				}
				void clear(PinBit bit) const {
					_gpio->BSRR = 1 << (bit + 16);
				}
				void toggle(PinMask mask) const {
					_gpio->ODR ^= mask;
				}
				void toggle(PinBit bit) const {
					_gpio->ODR ^= 1 << bit;
				}
				PinMask read() const {
					return PinMask(_gpio->IDR);
				}
				bool read(PinBit bit) const {
					return (_gpio->IDR & (1 << bit)) ? true : false;
				}
				void write(PinMask mask) const {
					_gpio->ODR = mask;
				}
				void write(PinMask clearMask, PinMask setMask) const {
				    _gpio->BSRR = (clearMask << 16) | setMask;
				}
				void write(PinBit bit, bool state) const {
					_gpio->BSRR = 1 << (bit + (state ? 0 : 16));
				}
		};

        /// brief Clase que representa un port.
        ///
        template <PortID portID_>
        class PortDeviceX final: public PortDevice {
            private:
                using PortTraits = internal::PortTraits<portID_>;
                using PortActivator = internal::PortActivator<portID_>;

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
                void activateImpl(PinMask mask) const override {
                    PortActivator::activate(mask);
                }
#if HTL_GPIO_OPTION_DEACTIVATE == 1
                void deactivateImpl(PinMask mask) const override {
                    PortActivator::deactivate(mask);
                }
#endif

            public:
                static void interruptHandler() {
                    _instance.interruptService();
                }
        };

        template <PortID portID_>
        PortDeviceX<portID_> PortDeviceX<portID_>::_instance;


        /// brief Clase que representa un pin individual.
        ///
		class PinDevice {
			public:
                struct InitParams {
                    InitMode mode;
                    union {
                        struct {
                            PullUpDown pupd;
                        } input;
                        struct {
                            OutputType type;
                            PullUpDown pupd;
                            Speed speed;
                            bool state;
                        } output;
                        struct {
                            OutputType type;
                            PullUpDown pupd;
                            Speed speed;
                            AlternateFunction function;
                        } alternate;
                        struct {
                        } analogic;
                    };
                };
			private:
		        GPIO_TypeDef * const _gpio;
		        PinMask const _mask;

			private:
				PinDevice(const PinDevice &) = delete;
				PinDevice & operator = (const PinDevice &) = delete;

			private:
                inline void activate() const {
                	activateImpl();
                }
#if HTL_GPIO_OPTION_DEACTIVATE == 1
                inline void deactivate() const {
                	deactivateImpl();
                }
#endif

			protected:
                PinDevice(GPIO_TypeDef *gpio, PinBit bit);

                virtual void activateImpl() const = 0;
#if HTL_GPIO_OPTION_DEACTIVATE == 1
                virtual void deactivateImpl() const = 0;
#endif
			public:
                void initInput(PullUpDown pupd) const;
                void initOutput(OutputType type, PullUpDown pupd, Speed speed, bool state) const;
                void initAlternate(OutputType outputType, PullUpDown pupd, Speed speed, AlternateFunction af) const;
                void initAnalogic() const;
                void initialize(const InitParams &params) const;
#if HTL_GPIO_OPTION_DEACTIVATE == 1
                void deinitialize() const;
#endif

				void set() const {
                    _gpio->BSRR = _mask;
				}
				void clear() const {
                    _gpio->BSRR = _mask << 16;
				}
				void toggle() const {
					  auto odr = _gpio->ODR;
					  _gpio->BSRR = ((odr & _mask) << 16) | (~odr & _mask);
				}
				void write(bool state) const {
                    _gpio->BSRR = state ? _mask : _mask << 16;
				}
				bool read() const {
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
                using PortActivator = internal::PortActivator<portID_>;

            private:
                static PinDeviceX _instance;
                static constexpr auto _mask = PinTraits::mask;
                static constexpr auto _bit = PinTraits::bit;
                static constexpr auto _gpioAddr = PortTraits::gpioAddr;

            public:
                static constexpr auto portID = portID_;
                static constexpr auto pinID = pinID_;
                static constexpr PinDeviceX *pInst = &_instance;
                static constexpr PinDeviceX &rInst = _instance;

            private:
                PinDeviceX():
                    PinDevice(reinterpret_cast<GPIO_TypeDef*>(_gpioAddr), PinBit(_bit)) {
                }

            protected:
                void activateImpl() const override {
                	PortActivator::activate(PinMask(_mask));
                }
#if HTL_GPIO_OPTION_DEACTIVATE == 1
                void deactivateImpl() const override {
                	PortActivator::deactivate(PinMask(_mask));
                }
#endif
        };

        template <PortID portID_, PinID pinID_>
        PinDeviceX<portID_, pinID_> PinDeviceX<portID_, pinID_>::_instance;


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
        typedef PinDeviceX<PortID::portA, PinID::pin0> PinA0;
        typedef PinDeviceX<PortID::portA, PinID::pin1> PinA1;
        typedef PinDeviceX<PortID::portA, PinID::pin2> PinA2;
        typedef PinDeviceX<PortID::portA, PinID::pin3> PinA3;
        typedef PinDeviceX<PortID::portA, PinID::pin4> PinA4;
        typedef PinDeviceX<PortID::portA, PinID::pin5> PinA5;
        typedef PinDeviceX<PortID::portA, PinID::pin6> PinA6;
        typedef PinDeviceX<PortID::portA, PinID::pin7> PinA7;
        typedef PinDeviceX<PortID::portA, PinID::pin8> PinA8;
        typedef PinDeviceX<PortID::portA, PinID::pin9> PinA9;
        typedef PinDeviceX<PortID::portA, PinID::pin10> PinA10;
        typedef PinDeviceX<PortID::portA, PinID::pin11> PinA11;
        typedef PinDeviceX<PortID::portA, PinID::pin12> PinA12;
        typedef PinDeviceX<PortID::portA, PinID::pin13> PinA13;
        typedef PinDeviceX<PortID::portA, PinID::pin14> PinA14;
        typedef PinDeviceX<PortID::portA, PinID::pin15> PinA15;
#endif
#ifdef HTL_GPIOB_EXIST
        typedef PinDeviceX<PortID::portB, PinID::pin0> PinB0;
        typedef PinDeviceX<PortID::portB, PinID::pin1> PinB1;
        typedef PinDeviceX<PortID::portB, PinID::pin2> PinB2;
        typedef PinDeviceX<PortID::portB, PinID::pin3> PinB3;
        typedef PinDeviceX<PortID::portB, PinID::pin4> PinB4;
        typedef PinDeviceX<PortID::portB, PinID::pin5> PinB5;
        typedef PinDeviceX<PortID::portB, PinID::pin6> PinB6;
        typedef PinDeviceX<PortID::portB, PinID::pin7> PinB7;
        typedef PinDeviceX<PortID::portB, PinID::pin8> PinB8;
        typedef PinDeviceX<PortID::portB, PinID::pin9> PinB9;
        typedef PinDeviceX<PortID::portB, PinID::pin10> PinB10;
        typedef PinDeviceX<PortID::portB, PinID::pin11> PinB11;
        typedef PinDeviceX<PortID::portB, PinID::pin12> PinB12;
        typedef PinDeviceX<PortID::portB, PinID::pin13> PinB13;
        typedef PinDeviceX<PortID::portB, PinID::pin14> PinB14;
        typedef PinDeviceX<PortID::portB, PinID::pin15> PinB15;
#endif
#ifdef HTL_GPIOC_EXIST
        typedef PinDeviceX<PortID::portC, PinID::pin0> PinC0;
        typedef PinDeviceX<PortID::portC, PinID::pin1> PinC1;
        typedef PinDeviceX<PortID::portC, PinID::pin2> PinC2;
        typedef PinDeviceX<PortID::portC, PinID::pin3> PinC3;
        typedef PinDeviceX<PortID::portC, PinID::pin4> PinC4;
        typedef PinDeviceX<PortID::portC, PinID::pin5> PinC5;
        typedef PinDeviceX<PortID::portC, PinID::pin6> PinC6;
        typedef PinDeviceX<PortID::portC, PinID::pin7> PinC7;
        typedef PinDeviceX<PortID::portC, PinID::pin8> PinC8;
        typedef PinDeviceX<PortID::portC, PinID::pin9> PinC9;
        typedef PinDeviceX<PortID::portC, PinID::pin10> PinC10;
        typedef PinDeviceX<PortID::portC, PinID::pin11> PinC11;
        typedef PinDeviceX<PortID::portC, PinID::pin12> PinC12;
        typedef PinDeviceX<PortID::portC, PinID::pin13> PinC13;
        typedef PinDeviceX<PortID::portC, PinID::pin14> PinC14;
        typedef PinDeviceX<PortID::portC, PinID::pin15> PinC15;
#endif
#ifdef HTL_GPIOD_EXIST
        typedef PinDeviceX<PortID::portD, PinID::pin0> PinD0;
        typedef PinDeviceX<PortID::portD, PinID::pin1> PinD1;
        typedef PinDeviceX<PortID::portD, PinID::pin2> PinD2;
        typedef PinDeviceX<PortID::portD, PinID::pin3> PinD3;
        typedef PinDeviceX<PortID::portD, PinID::pin4> PinD4;
        typedef PinDeviceX<PortID::portD, PinID::pin5> PinD5;
        typedef PinDeviceX<PortID::portD, PinID::pin6> PinD6;
        typedef PinDeviceX<PortID::portD, PinID::pin7> PinD7;
        typedef PinDeviceX<PortID::portD, PinID::pin8> PinD8;
        typedef PinDeviceX<PortID::portD, PinID::pin9> PinD9;
        typedef PinDeviceX<PortID::portD, PinID::pin10> PinD10;
        typedef PinDeviceX<PortID::portD, PinID::pin11> PinD11;
        typedef PinDeviceX<PortID::portD, PinID::pin12> PinD12;
        typedef PinDeviceX<PortID::portD, PinID::pin13> PinD13;
        typedef PinDeviceX<PortID::portD, PinID::pin14> PinD14;
        typedef PinDeviceX<PortID::portD, PinID::pin15> PinD15;
#endif
#ifdef HTL_GPIOE_EXIST
        typedef PinDeviceX<PortID::portE, PinID::pin0> PinE0;
        typedef PinDeviceX<PortID::portE, PinID::pin1> PinE1;
        typedef PinDeviceX<PortID::portE, PinID::pin2> PinE2;
        typedef PinDeviceX<PortID::portE, PinID::pin3> PinE3;
        typedef PinDeviceX<PortID::portE, PinID::pin4> PinE4;
        typedef PinDeviceX<PortID::portE, PinID::pin5> PinE5;
        typedef PinDeviceX<PortID::portE, PinID::pin6> PinE6;
        typedef PinDeviceX<PortID::portE, PinID::pin7> PinE7;
        typedef PinDeviceX<PortID::portE, PinID::pin8> PinE8;
        typedef PinDeviceX<PortID::portE, PinID::pin9> PinE9;
        typedef PinDeviceX<PortID::portE, PinID::pin10> PinE10;
        typedef PinDeviceX<PortID::portE, PinID::pin11> PinE11;
        typedef PinDeviceX<PortID::portE, PinID::pin12> PinE12;
        typedef PinDeviceX<PortID::portE, PinID::pin13> PinE13;
        typedef PinDeviceX<PortID::portE, PinID::pin14> PinE14;
        typedef PinDeviceX<PortID::portE, PinID::pin15> PinE15;
#endif
#ifdef HTL_GPIOF_EXIST
        typedef PinDeviceX<PortID::portF, PinID::pin0> PinF0;
        typedef PinDeviceX<PortID::portF, PinID::pin1> PinF1;
        typedef PinDeviceX<PortID::portF, PinID::pin2> PinF2;
        typedef PinDeviceX<PortID::portF, PinID::pin3> PinF3;
        typedef PinDeviceX<PortID::portF, PinID::pin4> PinF4;
        typedef PinDeviceX<PortID::portF, PinID::pin5> PinF5;
        typedef PinDeviceX<PortID::portF, PinID::pin6> PinF6;
        typedef PinDeviceX<PortID::portF, PinID::pin7> PinF7;
        typedef PinDeviceX<PortID::portF, PinID::pin8> PinF8;
        typedef PinDeviceX<PortID::portF, PinID::pin9> PinF9;
        typedef PinDeviceX<PortID::portF, PinID::pin10> PinF10;
        typedef PinDeviceX<PortID::portF, PinID::pin11> PinF11;
        typedef PinDeviceX<PortID::portF, PinID::pin12> PinF12;
        typedef PinDeviceX<PortID::portF, PinID::pin13> PinF13;
        typedef PinDeviceX<PortID::portF, PinID::pin14> PinF14;
        typedef PinDeviceX<PortID::portF, PinID::pin15> PinF15;
#endif
#ifdef HTL_GPIOG_EXIST
        typedef PinDeviceX<PortID::portG, PinID::pin0> PinG0;
        typedef PinDeviceX<PortID::portG, PinID::pin1> PinG1;
        typedef PinDeviceX<PortID::portG, PinID::pin2> PinG2;
        typedef PinDeviceX<PortID::portG, PinID::pin3> PinG3;
        typedef PinDeviceX<PortID::portG, PinID::pin4> PinG4;
        typedef PinDeviceX<PortID::portG, PinID::pin5> PinG5;
        typedef PinDeviceX<PortID::portG, PinID::pin6> PinG6;
        typedef PinDeviceX<PortID::portG, PinID::pin7> PinG7;
        typedef PinDeviceX<PortID::portG, PinID::pin8> PinG8;
        typedef PinDeviceX<PortID::portG, PinID::pin9> PinG9;
        typedef PinDeviceX<PortID::portG, PinID::pin10> PinG10;
        typedef PinDeviceX<PortID::portG, PinID::pin11> PinG11;
        typedef PinDeviceX<PortID::portG, PinID::pin12> PinG12;
        typedef PinDeviceX<PortID::portG, PinID::pin13> PinG13;
        typedef PinDeviceX<PortID::portG, PinID::pin14> PinG14;
        typedef PinDeviceX<PortID::portG, PinID::pin15> PinG15;
#endif
#ifdef HTL_GPIOH_EXIST
        typedef PinDeviceX<PortID::portH, PinID::pin0> PinH0;
        typedef PinDeviceX<PortID::portH, PinID::pin1> PinH1;
        typedef PinDeviceX<PortID::portH, PinID::pin2> PinH2;
        typedef PinDeviceX<PortID::portH, PinID::pin3> PinH3;
        typedef PinDeviceX<PortID::portH, PinID::pin4> PinH4;
        typedef PinDeviceX<PortID::portH, PinID::pin5> PinH5;
        typedef PinDeviceX<PortID::portH, PinID::pin6> PinH6;
        typedef PinDeviceX<PortID::portH, PinID::pin7> PinH7;
        typedef PinDeviceX<PortID::portH, PinID::pin8> PinH8;
        typedef PinDeviceX<PortID::portH, PinID::pin9> PinH9;
        typedef PinDeviceX<PortID::portH, PinID::pin10> PinH10;
        typedef PinDeviceX<PortID::portH, PinID::pin11> PinH11;
        typedef PinDeviceX<PortID::portH, PinID::pin12> PinH12;
        typedef PinDeviceX<PortID::portH, PinID::pin13> PinH13;
        typedef PinDeviceX<PortID::portH, PinID::pin14> PinH14;
        typedef PinDeviceX<PortID::portH, PinID::pin15> PinH15;
#endif
#ifdef HTL_GPIOI_EXIST
        typedef PinDeviceX<PortID::portI, PinID::pin0> PinI0;
        typedef PinDeviceX<PortID::portI, PinID::pin1> PinI1;
        typedef PinDeviceX<PortID::portI, PinID::pin2> PinI2;
        typedef PinDeviceX<PortID::portI, PinID::pin3> PinI3;
        typedef PinDeviceX<PortID::portI, PinID::pin4> PinI4;
        typedef PinDeviceX<PortID::portI, PinID::pin5> PinI5;
        typedef PinDeviceX<PortID::portI, PinID::pin6> PinI6;
        typedef PinDeviceX<PortID::portI, PinID::pin7> PinI7;
        typedef PinDeviceX<PortID::portI, PinID::pin8> PinI8;
        typedef PinDeviceX<PortID::portI, PinID::pin9> PinI9;
        typedef PinDeviceX<PortID::portI, PinID::pin10> PinI10;
        typedef PinDeviceX<PortID::portI, PinID::pin11> PinI11;
        typedef PinDeviceX<PortID::portI, PinID::pin12> PinI12;
        typedef PinDeviceX<PortID::portI, PinID::pin13> PinI13;
        typedef PinDeviceX<PortID::portI, PinID::pin14> PinI14;
        typedef PinDeviceX<PortID::portI, PinID::pin15> PinI15;
#endif
#ifdef HTL_GPIOJ_EXIST
        typedef PinDeviceX<PortID::portJ, PinID::pin0> PinJ0;
        typedef PinDeviceX<PortID::portJ, PinID::pin1> PinJ1;
        typedef PinDeviceX<PortID::portJ, PinID::pin2> PinJ2;
        typedef PinDeviceX<PortID::portJ, PinID::pin3> PinJ3;
        typedef PinDeviceX<PortID::portJ, PinID::pin4> PinJ4;
        typedef PinDeviceX<PortID::portJ, PinID::pin5> PinJ5;
        typedef PinDeviceX<PortID::portJ, PinID::pin6> PinJ6;
        typedef PinDeviceX<PortID::portJ, PinID::pin7> PinJ7;
        typedef PinDeviceX<PortID::portJ, PinID::pin8> PinJ8;
        typedef PinDeviceX<PortID::portJ, PinID::pin9> PinJ9;
        typedef PinDeviceX<PortID::portJ, PinID::pin10> PinJ10;
        typedef PinDeviceX<PortID::portJ, PinID::pin11> PinJ11;
        typedef PinDeviceX<PortID::portJ, PinID::pin12> PinJ12;
        typedef PinDeviceX<PortID::portJ, PinID::pin13> PinJ13;
        typedef PinDeviceX<PortID::portJ, PinID::pin14> PinJ14;
        typedef PinDeviceX<PortID::portJ, PinID::pin15> PinJ15;
#endif
#ifdef HTL_GPIOK_EXIST
        typedef PinDeviceX<PortID::portK, PinID::pin0> PinK0;
        typedef PinDeviceX<PortID::portK, PinID::pin1> PinK1;
        typedef PinDeviceX<PortID::portK, PinID::pin2> PinK2;
        typedef PinDeviceX<PortID::portK, PinID::pin3> PinK3;
        typedef PinDeviceX<PortID::portK, PinID::pin4> PinK4;
        typedef PinDeviceX<PortID::portK, PinID::pin5> PinK5;
        typedef PinDeviceX<PortID::portK, PinID::pin6> PinK6;
        typedef PinDeviceX<PortID::portK, PinID::pin7> PinK7;
        typedef PinDeviceX<PortID::portK, PinID::pin8> PinK8;
        typedef PinDeviceX<PortID::portK, PinID::pin9> PinK9;
        typedef PinDeviceX<PortID::portK, PinID::pin10> PinK10;
        typedef PinDeviceX<PortID::portK, PinID::pin11> PinK11;
        typedef PinDeviceX<PortID::portK, PinID::pin12> PinK12;
        typedef PinDeviceX<PortID::portK, PinID::pin13> PinK13;
        typedef PinDeviceX<PortID::portK, PinID::pin14> PinK14;
        typedef PinDeviceX<PortID::portK, PinID::pin15> PinK15;
#endif

        namespace internal {

			template <PortID portId_>
			class PortActivator final {
				private:
					using PortTraits = internal::PortTraits<portId_>;

                private:
					static constexpr auto _addr = PortTraits::activateAddr;
					static constexpr auto _pos = PortTraits::activatePos;

                private:
					static PinMask _mask;

				public:
					static void activate(PinMask mask) {
					    auto m = (uint16_t) _mask;
						if (!m) {
							bits::set(*reinterpret_cast<uint32_t*>(_addr), (uint32_t)(1 << _pos));
							__DSB();
						}
						bits::set(m, (uint16_t) mask);
						_mask = PinMask(m);
					}

#if HTL_GPIO_OPTION_DEACTIVATE == 1
					static void deactivate(PinMask mask) {
                        auto m = (uint16_t) _mask;
                        bits::clear(m, (uint16_t) mask);
						if (!m) {
							bits::clear(*reinterpret_cast<uint32_t*>(_addr), (uint32_t)(1 << _pos));
							__DSB();
						}
                        _mask = PinMask(m);
					}
#endif
			};

			template <PortID portId_>
			PinMask PortActivator<portId_>::_mask {0};

#if !defined(EOS_PLATFORM_STM32G0) && !defined(EOS_PLATFORM_STM32F7)
#ifdef HTL_GPIOA_EXIST
			template<>
			struct PortTraits<PortID::portA> {
				static constexpr uint32_t gpioAddr = GPIOA_BASE;
#if defined(EOS_PLATFORM_STM32F0)
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, AHBENR);
				static constexpr uint32_t activatePos = RCC_AHBENR_GPIOAEN_Pos;
#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
				static constexpr uint32_t activatePos = RCC_AHB1ENR_GPIOAEN_Pos;
#endif
			};
#endif
#ifdef HTL_GPIOB_EXIST
			template  <>
			struct PortTraits<PortID::portB> {
				static constexpr uint32_t gpioAddr = GPIOB_BASE;
#if defined(EOS_PLATFORM_STM32F0)
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, AHBENR);
				static constexpr uint32_t activatePos = RCC_AHBENR_GPIOBEN_Pos;
#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
				static constexpr uint32_t activatePos = RCC_AHB1ENR_GPIOBEN_Pos;
#endif
			};
#endif
#ifdef HTL_GPIOC_EXIST
			template  <>
			struct PortTraits<PortID::portC> {
				static constexpr uint32_t gpioAddr = GPIOC_BASE;
#if defined(EOS_PLATFORM_STM32F0)
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, AHBENR);
				static constexpr uint32_t activatePos = RCC_AHBENR_GPIOCEN_Pos;
#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
				static constexpr uint32_t activatePos = RCC_AHB1ENR_GPIOCEN_Pos;
#endif
			};
#endif
#ifdef HTL_GPIOD_EXIST
			template  <>
			struct PortTraits<PortID::portD> {
				static constexpr uint32_t gpioAddr = GPIOD_BASE;
#if defined(EOS_PLATFORM_STM32F0)
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, AHBENR);
				static constexpr uint32_t activatePos = RCC_AHBENR_GPIODEN_Pos;
#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
				static constexpr uint32_t activatePos = RCC_AHB1ENR_GPIODEN_Pos;
#endif
			};
#endif
#ifdef HTL_GPIOE_EXIST
			template  <>
			struct PortTraits<PortID::portE> {
				static constexpr uint32_t gpioAddr = GPIOE_BASE;
#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
				static constexpr uint32_t activatePos = RCC_AHB1ENR_GPIOEEN_Pos;
#endif
			};
#endif
#ifdef HTL_GPIOF_EXIST
			template  <>
			struct PortTraits<PortID::portF> {
				static constexpr uint32_t gpioAddr = GPIOF_BASE;
#if defined(EOS_PLATFORM_STM32F0)
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, AHBENR);
				static constexpr uint32_t activatePos = RCC_AHBENR_GPIOFEN_Pos;
#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
				static constexpr uint32_t activatePos = RCC_AHB1ENR_GPIOFEN_Pos;
#endif
			};
#endif
#ifdef HTL_GPIOG_EXIST
			template  <>
			struct PortTraits<PortID::portG> {
				static constexpr uint32_t gpioAddr = GPIOG_BASE;
#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
				static constexpr uint32_t activatePos = RCC_AHB1ENR_GPIOGEN_Pos;
#endif
			};
#endif
#ifdef HTL_GPIOH_EXIST
			template  <>
			struct PortTraits<PortID::portH> {
				static constexpr uint32_t gpioAddr = GPIOH_BASE;
#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
				static constexpr uint32_t activatePos = RCC_AHB1ENR_GPIOHEN_Pos;
#endif
			};
#endif
#ifdef HTL_GPIOI_EXIST
			template  <>
			struct PortTraits<PortID::portI> {
				static constexpr uint32_t gpioAddr = GPIOI_BASE;
#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
				static constexpr uint32_t activatePos = RCC_AHB1ENR_GPIOIEN_Pos;
#endif
			};
#endif
#ifdef HTL_GPIOJ_EXIST
			template  <>
			struct PortTraits<PortID::portJ> {
				static constexpr uint32_t gpioAddr = GPIOJ_BASE;
#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
				static constexpr uint32_t activatePos = RCC_AHB1ENR_GPIOJEN_Pos;
#endif
			};
#endif
#ifdef HTL_GPIOK_EXIST
			template  <>
			struct PortTraits<PortID::portK> {
				static constexpr uint32_t gpioAddr = GPIOK_BASE;
#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
				static constexpr uint32_t activatePos = RCC_AHB1ENR_GPIOKEN_Pos;
#endif
			};
#endif
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

#if defined(EOS_PLATFORM_STM32G030)
	#include "htl/STM32/G0/htlGPIO_Traits.h"

#elif defined(EOS_PLATFORM_STM32G031)
	#include "htl/STM32/G0/htlGPIO_Traits.h"

#elif defined(EOS_PLATFORM_STM32G071)
	#include "htl/STM32/G0/htlGPIO_Traits.h"

#elif defined(EOS_PLATFORM_STM32G0B1)
	#include "htl/STM32/G0/htlGPIO_Traits.h"

#elif defined(EOS_PLATFORM_STM32F030)

#elif defined(EOS_PLATFORM_STM32F429)
	#include "htl/STM32/F4/htlGPIO_Traits.h"

#elif defined(EOS_PLATFORM_STM32F746)
	#include "htl/STM32/F7/htlGPIO_Traits.h"

#else
    #error "Unknown platform"
#endif



#endif // __STM32_htlGPIO__
