module;


#include "HTL/htl.h"


export module htl.gpio;

import htl.bits;


export namespace htl::gpio {

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

            template <PortID>
            class Activator;

            template <PortID>
            struct PortTraits;

            template <PinID>
            struct PinTraits;

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

				void set(PinMask mask) const;
				void set(PinBit bit) const;
				void clear(PinMask mask) const;
				void clear(PinBit bit) const;
				void toggle(PinMask mask) const;
				void toggle(PinBit bit) const;
				PinMask read() const;
				bool read(PinBit bit) const;
				void write(PinMask mask) const;
				void write(PinMask clearMask, PinMask setMask) const;
				void write(PinBit bit, bool state) const;
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

				void set() const;
				void clear() const;
				void toggle() const;
				void write(bool state) const;
				bool read() const;
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
                PinDeviceX();

            protected:
                void activate() const override;
                void deactivate() const override;
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
        }
	}



struct MODER {
	static constexpr uint32_t Mask      = 0b11;
	static constexpr uint32_t INPUT     = 0b00;
	static constexpr uint32_t OUTPUT    = 0b01;
	static constexpr uint32_t ALTERNATE = 0b10;
	static constexpr uint32_t ANALOGIC  = 0b11;
};

struct PUPDR {
	static constexpr uint32_t Mask = 0b11;
	static constexpr uint32_t NONE = 0b00;
	static constexpr uint32_t UP   = 0b01;
	static constexpr uint32_t DOWN = 0b10;
};

struct OTYPER {
	static constexpr uint32_t Mask = 0b1;
	static constexpr uint32_t PP   = 0b0;
	static constexpr uint32_t OD   = 0b1;
};

struct OSPEEDR {
	static constexpr uint32_t Mask   = 0b11;
	static constexpr uint32_t LOW    = 0b00;
	static constexpr uint32_t MEDIUM = 0b01;
	static constexpr uint32_t HIGH   = 0b10;
	static constexpr uint32_t FAST   = 0b11;
};

struct AFR {
	static constexpr uint32_t Mask = 0b1111;
};


static const uint32_t __speedTbl[] = {
    OSPEEDR::LOW,
    OSPEEDR::MEDIUM,
    OSPEEDR::HIGH,
    OSPEEDR::FAST};


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    gpio: Registres hardware del modul GPIO.
///
htl::gpio::PortDevice::PortDevice(
	GPIO_TypeDef *gpio):

	_gpio {gpio} {
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio com entrades.
/// \param    mask: Mascara de pins a configurar.
/// \param    mode: Tipus d'entrada.
///
void htl::gpio::PortDevice::initInput(
	PinMask mask,
	InputMode mode) const {

	activate(mask);
	internal::initInput(_gpio, mask, mode);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio com sortides.
/// \param    mask: Mascara de pins a configurar.
/// \param    mode: El tipus de sortida.
/// \param    speed: Opcions de velocitat.
///
void htl::gpio::PortDevice::initOutput(
	PinMask mask,
	OutputMode mode,
	Speed speed) const {

	activate(mask);
	internal::initOutput(_gpio, mask, mode, speed, false);
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el dispositiu.
///
void htl::gpio::PortDevice::deinitialize() const {

}


void htl::gpio::PortDevice::set(
	PinMask mask) const {

	_gpio->BSRR = mask;
}


void htl::gpio::PortDevice::set(
	PinBit bit) const {

	_gpio->BSRR = 1 << bit;
}


void htl::gpio::PortDevice::clear(
	PinMask mask) const {

	_gpio->BSRR = mask << 16;
}


void htl::gpio::PortDevice::clear(
	PinBit bit) const {

	_gpio->BSRR = 1 << (bit + 16);
}


void htl::gpio::PortDevice::toggle(
	PinMask mask) const {

	_gpio->ODR ^= mask;
}


void htl::gpio::PortDevice::toggle(
	PinBit bit) const {

	_gpio->ODR ^= 1 << bit;
}


htl::gpio::PinMask htl::gpio::PortDevice::read() const {

	return PinMask(_gpio->IDR);
}


bool htl::gpio::PortDevice::read(
	PinBit bit) const {

	return (_gpio->IDR & (1 << bit)) ? true : false;
}


void htl::gpio::PortDevice::write(
	PinMask mask) const {

	_gpio->ODR = mask;
}


void htl::gpio::PortDevice::write(
	PinMask clearMask,
	PinMask setMask) const {

    _gpio->BSRR = (clearMask << 16) | setMask;
}


void htl::gpio::PortDevice::write(
	PinBit bit,
	bool state) const {

	_gpio->BSRR = 1 << (bit + (state ? 0 : 16));
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    gpio: Registres de hardware
/// \param    bit: El bit del pin.
///
htl::gpio::PinDevice::PinDevice(
    GPIO_TypeDef *gpio,
    PinBit bit):

    _gpio {gpio},
    _mask {bit} {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio.
/// \param    info: Parametres d'inicialitzacio.
///
void htl::gpio::PinDevice::initialize(
    const InitInfo &info) const {

    activate();
    internal::initialize(_gpio, _mask, &info);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el pin en modun entrada digital.
/// \param    mode: El tipus d'entrada.
///
void htl::gpio::PinDevice::initInput(
	InputMode mode) const {

	activate();
	internal::initInput(_gpio, _mask, mode);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza un pin en modus soirtida digital.
/// \parAM    mode: El tipus de sortida.
/// \param    speed: Velocitat de conmutacio.
/// \param    state: L'estat inicial de la sortida.
///
void htl::gpio::PinDevice::initOutput(
	OutputMode mode,
	Speed speed,
	bool state) const {

    activate();
	internal::initOutput(_gpio, _mask, mode, speed, state);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza un pin en modus alternatiu.
/// \param    mode: El tipus de entrada/sortida
/// \param    speed: Velocitat de conmutacio.
/// \param    af: Funcio alternativa.
///
void htl::gpio::PinDevice::initAlternate(
	AlternateMode mode,
	Speed speed,
	AlternateFunction af) const {

	activate();
	internal::initAlternate(_gpio, _mask, mode, speed, af);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el pin com a entrada/sortida analogica.
///
void htl::gpio::PinDevice::initAnalogic() const {

    activate();
	internal::initAnalogic(_gpio, _mask);
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el pin i el deixa als valor per defecte.
///
void htl::gpio::PinDevice::deinitialize() const {

	internal::deinitialize(_gpio, _mask);
    deactivate();
}

void htl::gpio::PinDevice::set() const {

    _gpio->BSRR = _mask;
}


void htl::gpio::PinDevice::clear() const {

    _gpio->BSRR = _mask << 16;
}


void htl::gpio::PinDevice::toggle() const {

    _gpio->ODR ^= _mask;
}


void htl::gpio::PinDevice::write(bool state) const {

    _gpio->BSRR = _mask << (state ? 0 : 16);
}


bool htl::gpio::PinDevice::read() const {

	return (_gpio->IDR & _mask) != 0;
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
template <htl::gpio::PortID portID_, htl::gpio::PinID pinID_>
htl::gpio::PinDeviceX<portID_, pinID_>::PinDeviceX():
    PinDevice(reinterpret_cast<GPIO_TypeDef*>(_gpioAddr), _bit) {
}


/// ----------------------------------------------------------------------
/// \brief    Activa el dispositiu
///
template <htl::gpio::PortID portID_, htl::gpio::PinID pinID_>
void htl::gpio::PinDeviceX<portID_, pinID_>::activate() const {

    Activator::activate(_mask);
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el dispositiu
///
template <htl::gpio::PortID portID_, htl::gpio::PinID pinID_>
void htl::gpio::PinDeviceX<portID_, pinID_>::deactivate() const {

    Activator::deactivate(_mask);
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    gpio: Registres de hardware del modul GPIO.
/// \param    pinID: Identificador del pin.
///
htl::gpio::PinInterrupt::PinInterrupt(
	GPIO_TypeDef *gpio,
	PinID pinID) :

	_portNum {uint8_t((uint32_t(gpio) >> 10) & 0x000F)},
	_pinNum {uint8_t(pinID)},
	_notifyEvent {nullptr},
	_notifyEventEnabled {false} {

}


/// ----------------------------------------------------------------------
/// \brief    Habilita la interrupcio.
/// \param    edge: El flanc que genera la interrupcio.
/// \remarks  Hi han limitavcions en funcio del hardware.
///
void htl::gpio::PinInterrupt::enableInterruptPin(
	Edge edge) const {

	#if defined(EOS_PLATFORM_STM32F0) || \
	    defined(EOS_PLATFORM_STM32F4) || \
	    defined(EOS_PLATFORM_STM32F7)

	if ((RCC->APB2ENR & RCC_APB2ENR_SYSCFGEN) == 0) {
		RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
		__DSB();
	}

	uint32_t tmp = SYSCFG->EXTICR[_pinNum >> 2];
	tmp &= ~(((uint32_t)0x0F) << (4 * (_pinNum & 0x03)));
	tmp |= (_portNum << (4 * (_pinNum & 0x03)));
	SYSCFG->EXTICR[_pinNum >> 2] = tmp;

	uint32_t mask = 1 << _pinNum;

	// Configura en modus interrupcio
	//
	EXTI->IMR |= mask;
	EXTI->EMR &= ~mask;

	// Configura el registre RTSR (Rising Trigger Selection Register)
	//
	if ((edge == Edge::rising) || (edge == Edge::all))
		EXTI->RTSR |= mask;
	else
		EXTI->RTSR &= ~mask;

	// Configura el registre FTSR1 (Falling Trigger Selection Register)
	//
	if ((edge == Edge::falling) || (edge == Edge::all))
		EXTI->FTSR |= mask;
	else
		EXTI->FTSR &= ~mask;


	#elif defined(EOS_PLATFORM_STM32G0)

	/// Asigna el port GPIO a la linia EXTI
	//
	uint32_t tmp = EXTI->EXTICR[_pinNum >> 2u];
	tmp &= ~(EXTI_EXTICR1_EXTI0 << (EXTI_EXTICR1_EXTI1_Pos * (_pinNum & 0x03u)));
	tmp |= (_portNum << (EXTI_EXTICR1_EXTI1_Pos * (_pinNum & 0x03u)));
	EXTI->EXTICR[_pinNum >> 2u] = tmp;

	// Obte la mascara del pin
	//
	uint32_t mask = 1 << _pinNum;

	// Configura en modus interrupcio
	//
	EXTI->IMR1 |= mask;
	EXTI->EMR1 &= ~mask;

	// Configura el registre RTSR (Rising Trigger Selection Register)
	//
	if ((edge == Edge::rising) || (edge == Edge::all))
		EXTI->RTSR1 |= mask;
	else
		EXTI->RTSR1 &= ~mask;

	// Configura el registre FTSR1 (Falling Trigger Selection Register)
	//
	if ((edge == Edge::falling) || (edge == Edge::all))
		EXTI->FTSR1 |= mask;
	else
		EXTI->FTSR1 &= ~mask;

	#else
		#error "Unknown platform"
	#endif
}


/// ----------------------------------------------------------------------
/// \brief    Deshabilita la interrupcio del pin.
///
void htl::gpio::PinInterrupt::disableInterruptPin() const {

	#if defined(EOS_PLATFORM_STM32F0) || \
	    defined(EOS_PLATFORM_STM32F4) || \
	    defined(EOS_PLATFORM_STM32F7)

	uint32_t mask = 1 << _pinNum;
	EXTI->RTSR &= ~mask;
	EXTI->FTSR &= ~mask;

	#elif defined(EOS_PLATFORM_STM32G0)

	uint32_t mask = 1 << _pinNum;
	EXTI->RTSR1 &= ~mask;
	EXTI->FTSR1 &= ~mask;

	#else
		#error "Unknown platform"
	#endif
}


/// ----------------------------------------------------------------------
/// \brief    Asigna l'event.
/// \param    event: El event.
/// \param    enabled: Indica si esta habilitat o no.
///
void htl::gpio::PinInterrupt::setNotifyEvent(
	INotifyEvent &event,
	bool enabled) {

	_notifyEvent = &event;
	_notifyEventEnabled = enabled;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les interupcions.
///
void htl::gpio::PinInterrupt::interruptService() const {

	// Revisar per que els flags son per tots els ports

	uint32_t mask = 1 << _pinNum;

	#if defined(EOS_PLATFORM_STM32F4) || \
	    defined(EOS_PLATFORM_STM32F7)

	if (EXTI->PR & mask) {
		EXTI->PR = mask;

		auto gpio = reinterpret_cast<GPIO_TypeDef*>(GPIOA_BASE + (_portNum * 0x400));

		// Si la entrada es 1, es un flanc ascendent
		//
		if (gpio->IDR & mask)
			notifyRisingEdge();

		// En cas contrari es un flanc descendent
		//
		else
			notifyFallingEdge();
	}

	#elif defined(EOS_PLATFORM_STM32G0)

	if (EXTI->FPR1 & mask) {
		EXTI->FPR1 = mask;
		notifyFallingEdge();
	}

	if (EXTI->RPR1 & mask) {
		EXTI->RPR1 = mask;
		notifyRisingEdge();
	}

	#endif
}


/// ----------------------------------------------------------------------
/// \brief    Invoca l'event de notificacio RisingEdge
///
void htl::gpio::PinInterrupt::notifyRisingEdge() const {

	if (_notifyEventEnabled) {
		NotifyEventArgs args = {
			.id = NotifyID::risingEdge,
			.isr = true
		};
		_notifyEvent->execute(this, args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Invoca l'event de notificacio FallingEdge
///
void htl::gpio::PinInterrupt::notifyFallingEdge() const {

	if (_notifyEventEnabled) {
		NotifyEventArgs args = {
			.id = NotifyID::fallingEdge,
			.isr = true
		};
		_notifyEvent->execute(this, args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza els pins.
/// \param    gpio: Registres de hardware del GPIO.
/// \param    mack: mascara de pins
/// \param    info: Informacio per la inicialitzacio.
///
void htl::gpio::internal::initialize(
    GPIO_TypeDef * const gpio,
	PinMask mask,
    const InitInfo *info) {

    switch(info->mode) {
        case InitMode::input:
            internal::initInput(gpio, mask, info->input.mode);
            break;

        case InitMode::output:
            internal::initOutput(gpio, mask, info->output.mode,
                    info->output.speed, info->output.state);
            break;

        case InitMode::alternate:
            internal::initAlternate(gpio, mask, info->alternate.mode,
                    info->alternate.speed, info->alternate.function);
            break;

        case InitMode::analogic:
            internal::initAnalogic(gpio, mask);
            break;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza els pins com a entrades.
/// \param    gpio: Registres de hardware del GPIO.
/// \param    mask: Mascara dels pins a inicialitzar.
/// \param    node: Tipus d'entrada.
///
void htl::gpio::internal::initInput(
    GPIO_TypeDef * const gpio,
    PinMask mask,
    InputMode mode) {

    auto m = uint16_t(mask);
    for (uint8_t b = 0; b < 15; b++) {
        if ((m & (1 << b)) != 0)
            initInput(gpio, PinBit(b), mode);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza un pin com a entrade.
/// \param    gpio: Registres de hardware del GPIO.
/// \param    bit: El bit del pin a inicialitzar.
/// \param    node: Tipus d'entrada.
///
void htl::gpio::internal::initInput(
	GPIO_TypeDef * const gpio,
	PinBit bit,
	InputMode mode) {

    auto b = uint8_t(bit);

    uint32_t tmp;

    // Configura el pin com a entrada digital
    //
    tmp = gpio->MODER;
    tmp &= ~(MODER::Mask << (b * 2));
    tmp |= MODER::INPUT << (b * 2);
    gpio->MODER = tmp;

    // Configura les resistencies pull UP/DOWN
    //
    tmp = gpio->PUPDR;
    tmp &= ~(PUPDR::Mask << (b * 2));
    switch (mode) {
        case InputMode::pullUp:
            tmp |= PUPDR::UP << (b * 2);
            break;

        case InputMode::pullDown:
            tmp |= PUPDR::DOWN << (b * 2);
            break;

        default:
            break;
    }
    gpio->PUPDR = tmp;
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza els pins com sortides.
/// \param    gpio: Els registres de hardware del GPIO.
/// \param    mask: Mascara dels pins a inicialitzar.
/// \param    mode: Tipus de sortida.
/// \param    speed: Velocitat de conmutacio.
/// \param    state: L'estat inicial del pin.
///
void htl::gpio::internal::initOutput(
    GPIO_TypeDef * const gpio,
    PinMask mask,
    OutputMode mode,
    Speed speed,
    bool state) {

    auto m = uint16_t(mask);
    for (auto b = 0; b < 15; b++) {
        if ((m & (1 << b)) != 0)
            initOutput(gpio, PinBit(b), mode, speed, state);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza un pin com sortida.
/// \param    gpio: Els registres de hardware del GPIO.
/// \param    bit: El bit del pin a inicialitzar.
/// \param    mode: Tipus de sortida.
/// \param    speed: Velocitat de conmutacio.
/// \param    state: L'estat inicial del pin.
///
void htl::gpio::internal::initOutput(
	GPIO_TypeDef * const gpio,
	PinBit bit,
	OutputMode mode,
	Speed speed,
	bool state) {

    auto b = uint8_t(bit);

    uint32_t tmp;

    // Configura el pin com sortida digital
    //
    tmp = gpio->MODER;
    clearBits(tmp, MODER::Mask << (b * 2));
    setBits(tmp, MODER::OUTPUT << (b * 2));
    gpio->MODER = tmp;

    // Configura el driver de sortida
    //
    tmp = gpio->OTYPER;
    clearBits(tmp, OTYPER::Mask << b);
    if (mode == OutputMode::openDrain ||
        mode == OutputMode::openDrainPullUp)
        setBits(tmp, OTYPER::OD << b);
    gpio->OTYPER = tmp;

    // Configura la resistencia pull UP
    //
    tmp = gpio->PUPDR;
    clearBits(tmp, PUPDR::Mask << (b * 2));
    if (mode == OutputMode::openDrainPullUp)
        setBits(tmp, PUPDR::UP << (b * 2));
    gpio->PUPDR = tmp;

    // Configura la velocitat de conmutacio
    //
    tmp = gpio->OSPEEDR;
    clearBits(tmp, OSPEEDR::Mask << (b * 2));
    setBits(tmp, __speedTbl[uint8_t(speed)] << (b * 2));
    gpio->OSPEEDR = tmp;

    setBits(gpio->ODR, (state ? 1 : 0) << b);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza els pins com entrades/sortides alternatives.
/// \param    gpio: Registres de hardware del GPIO.
/// \param    mask: Mascara del pins a inicialitzar.
/// \param    mode: Tipus de entrada/sortida.
/// \param    speed: Velocitat de conmutacio.
/// \param    af: La funcio alternativa.
///
void htl::gpio::internal::initAlternate(
	GPIO_TypeDef * const gpio,
	PinMask mask,
	AlternateMode mode,
	Speed speed,
	AlternateFunction af) {

    auto m = uint16_t(mask);
	for (uint8_t b = 0; b < 15; b++) {
		if ((m & (1 << b)) != 0)
		    initAlternate(gpio, PinBit(b), mode, speed, af);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza un pin com entrada/sortida alternativa.
/// \param    gpio: Registres de hardware del GPIO.
/// \param    bit: El bit del pin a inicialitzar.
/// \param    mode: Tipus de entrada/sortida.
/// \param    speed: Velocitat de conmutacio.
/// \param    af: La funcio alternativa.
///
void htl::gpio::internal::initAlternate(
    GPIO_TypeDef * const gpio,
    PinBit bit,
    AlternateMode mode,
    Speed speed,
    AlternateFunction af) {

    auto b = uint8_t(bit);

    uint32_t tmp;

    // Configura el pin com entrada/sortida alternativa
    //
    tmp = gpio->MODER;
    clearBits(tmp, MODER::Mask << (b * 2));
    setBits(tmp, MODER::ALTERNATE << (b * 2));
    gpio->MODER = tmp;

    // Configura el driver de sortida
    //
    tmp = gpio->OTYPER;
    clearBits(tmp, OTYPER::Mask << b);
    if (mode == AlternateMode::openDrain ||
        mode == AlternateMode::openDrainPullUp)
        setBits(tmp, OTYPER::OD << b);
    gpio->OTYPER = tmp;

    // Configura la resistencia pull UP
    //
    tmp = gpio->PUPDR;
    clearBits(tmp, PUPDR::Mask << (b * 2));
    if (mode == AlternateMode::openDrainPullUp)
        setBits(tmp, PUPDR::UP << (b * 2));
    gpio->PUPDR = tmp;

    // Configura la velocitat de conmutacio
    //
    tmp = gpio->OSPEEDR;
    clearBits(tmp, OSPEEDR::Mask << (b * 2));
    setBits(tmp, __speedTbl[uint8_t(speed)] << (b * 2));
    gpio->OSPEEDR = tmp;

    // Selecciona la funcio alternativa
    //
    tmp = gpio->AFR[b >> 3];
    clearBits(tmp, AFR::Mask << ((b & 0x07) * 4)) ;
    setBits(tmp, (uint32_t(af) & AFR::Mask) << ((b & 0x07) * 4));
    gpio->AFR[b >> 3] = tmp;
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza els pins com entrades/sortides analogiques.
/// \param    gpio: Registres de hardware del GPIO.
/// \param    mask: Mascara dels pins a inicialitzar.
///
void htl::gpio::internal::initAnalogic(
	GPIO_TypeDef * const gpio,
	PinMask mask) {

    auto m = uint16_t(mask);
    for (uint8_t b = 0; b < 15; b++) {
        if ((m & (1 << b)) != 0)
            initAnalogic(gpio, PinBit(b));
    }
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza un pin com entrada/sortida analogica.
/// \param    gpio: Registres de hardware del GPIO.
/// \param    bit: El bit del pin a inicialitzar.
///
void htl::gpio::internal::initAnalogic(
    GPIO_TypeDef * const gpio,
    PinBit bit) {

}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza els pins. Els deixa en la seva configuracio
///           per defecte.
/// \param    gpio: Registres de hardware del GPIO.
/// \param    mask: Mascara dels pins a desinicialitzar.
///
void htl::gpio::internal::deinitialize(
	GPIO_TypeDef * const gpio,
	PinMask mask) {

    auto m = uint16_t(mask);
    for (uint8_t b = 0; b < 15; b++) {
        if ((m & (1 << b)) != 0)
            deinitialize(gpio, PinMask(1 << b));
    }
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza un pin. El deixa en la seva configuracio
///           per defecte.
/// \param    gpio: Registres de hardware del GPIO.
/// \param    bit: El bit del pin a desinicialitzar.
///
void htl::gpio::internal::deinitialize(
	GPIO_TypeDef * const gpio,
	PinBit bit) {
/*

    uint32_t tmp;

    tmp = gpio->MODER;
    #if defined(EOS_PLATFORM_STM32F4)
    tmp |= MODER_ANALOGIC << pn;
    #elif defined(EOS_PLATFORM_STM32G0)
    tmp &= MODER_Mask << pn;
    if ((gpio == reinterpret_cast<GPIO_TypeDef*>(GPIOA_BASE)) && ((pn == 13 || pn == 14)))
        tmp |= MODER_ALTERNATE << pn;
    else
        tmp |= MODER_ANALOGIC << pn;
    #else
    #error "Undefined platform"
    #endif
    gpio->MODER = tmp;

    tmp = gpio->OTYPER;
    tmp &= OTYPER_Mask << pn;
    tmp |= OTYPER_PP << pn;
    gpio->OTYPER = tmp;

    tmp = gpio->PUPDR;
    tmp &= PUPDR_Mask << pn;
    #if defined(EOS_PLATFORM_STM32F4)
    tmp |=  PUPDR_NONE << pn;
    #elif defined(EOS_PLATFORM_STM32G0)
    if ((gpio == reinterpret_cast<GPIO_TypeDef*>(GPIOA_BASE)) && (pn == 14))
        tmp |= PUPDR_DOWN << pn;
    else if ((gpio == reinterpret_cast<GPIO_TypeDef*>(GPIOA_BASE)) && (pn == 13))
        tmp |= PUPDR_UP << pn;
    else
        tmp |=  PUPDR_NONE << pn;
    #else
    #error "Undefined platform"
    #endif
    gpio->PUPDR = tmp;

    gpio->ODR = 0 << pn;

    gpio->AFR[pn >> 3] &= ~(AFR_Mask << ((pn & 0x07) * 4)) ;
	*/
}


namespace htl::gpio::internal {

#ifdef HTL_GPIOA_EXIST
	template<>
	struct PortTraits<PortID::portA> {
		static constexpr uint32_t gpioAddr = GPIOA_BASE;
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPENR);
		static constexpr uint32_t rccEnablePos = RCC_IOPENR_GPIOAEN_Pos;
	};
#endif

#ifdef HTL_GPIOB_EXIST
	template  <>
	struct PortTraits<PortID::portB> {
		static constexpr uint32_t gpioAddr = GPIOB_BASE;
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPENR);
		static constexpr uint32_t rccEnablePos = RCC_IOPENR_GPIOBEN_Pos;
	};
#endif

#ifdef HTL_GPIOC_EXIST
	template  <>
	struct PortTraits<PortID::portC> {
		static constexpr uint32_t gpioAddr = GPIOC_BASE;
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPENR);
		static constexpr uint32_t rccEnablePos = RCC_IOPENR_GPIOCEN_Pos;
	};
#endif

#ifdef HTL_GPIOD_EXIST
	template  <>
	struct PortTraits<PortID::portD> {
		static constexpr uint32_t gpioAddr = GPIOD_BASE;
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPENR);
		static constexpr uint32_t rccEnablePos = RCC_IOPENR_GPIODEN_Pos;
	};
#endif

#ifdef HTL_GPIOE_EXIST
	template  <>
	struct PortTraits<PortID::portE> {
		static constexpr uint32_t gpioAddr = GPIOE_BASE;
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPENR);
		static constexpr uint32_t rccEnablePos = RCC_IOPENR_GPIOEEN_Pos;
	};
#endif

#ifdef HTL_GPIOF_EXIST
	template  <>
	struct PortTraits<PortID::portF> {
		static constexpr uint32_t gpioAddr = GPIOF_BASE;
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPENR);
		static constexpr uint32_t rccEnablePos = RCC_IOPENR_GPIOFEN_Pos;
	};
#endif

#ifdef HTL_GPIOG_EXIST
	template  <>
	struct PortTraits<PortID::portG> {
		static constexpr uint32_t gpioAddr = GPIOG_BASE;
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPENR);
		static constexpr uint32_t rccEnablePos = RCC_IOPENR_GPIOGEN_Pos;
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

