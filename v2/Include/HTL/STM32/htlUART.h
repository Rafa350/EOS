#pragma once
#ifndef __STM32_htlUART__
#define __STM32_htlUART__


// EOS includes
//
#include "HTL/htl.h"
#include "HTL/STM32/htlGPIO.h"
#include "HTL/STM32/htlINT.h"


namespace htl {

	enum class UARTChannel {
        #ifdef USART1_BASE
            _1,
        #endif
        #ifdef USART2_BASE
            _2,
        #endif
        #ifdef USART3_BASE
            _3,
        #endif
        #ifdef UART4_BASE
            _4,
        #endif
        #ifdef UART5_BASE
            _5,
        #endif
        #ifdef USART6_BASE
            _6,
        #endif
        #ifdef UART7_BASE
            _7,
        #endif
        #ifdef UART8_BASE
            _8,
        #endif
	};

	enum class UARTFirstBit {
		lsb,
		msb
	};

	enum class UARTParity {
		none,
		even,
		odd
	};

	enum class UARTWordBits {
		_7,
		_8
	};

	enum class UARTStopBits {
		_0p5,
		_1,
		_1p5,
		_2
	};

	enum class UARTBaudMode {
		_1200,
		_2400,
		_4800,
		_9600,
		_19200,
		_38400,
		_57600,
		_115200,
		div,
		rate,
		automatic
	};

	enum class UARTHandsake {
		none,
		ctsrts
	};

	enum class UARTClockSource {
		pclk,
		sysclk,
		hsi,
		lse,
		automatic
	};

	enum class UARTOverSampling {
		_8,
		_16
	};

	enum class UARTInterrupt {
		txEmpty,
		cts,
		txComplete,
		rxNotEmpty,
		idle,
		parity,
		brk,
		endOfBlock,
		rxTimeout,
		match,
		error
	};

	enum class UARTFlag {
		txEmpty,
		cts,
		txComplete,
		rxNotEmpty,
		overrun,
		idle,
		parity,
		brk,
		endOfBlock,
		rxTimeout,
		framming,
		noise,
		match
	};

	enum class UARTPin {
		TX,
		RX,
		CTS,
		RTS,
		DE
	};

	using UARTInterruptParam = void*;
	using UARTInterruptFunction = void (*)(UARTInterruptParam);

	void UART_initialize();
	void UART_setProtocol(USART_TypeDef*, UARTWordBits, UARTParity, UARTStopBits, UARTHandsake);
	void UART_setTimming(USART_TypeDef*, UARTBaudMode, UARTClockSource, unsigned, UARTOverSampling);

	template <UARTChannel>
	struct UARTTrait {
	};

	template <UARTChannel, typename, UARTPin>
	struct UARTPinTrait {
	};

	template <UARTChannel channel_>
	class UART_x final {
		private:
			using Trait = UARTTrait<channel_>;

		public:
			static constexpr UARTChannel channel = channel_;

		private:
			static constexpr uint32_t _addr = Trait::addr;
			static UARTInterruptFunction _isrFunction;
			static UARTInterruptParam _isrParam;

		private:
			UART_x() = delete;
			UART_x(const UART_x &) = delete;
			UART_x(const UART_x &&) = delete;
			~UART_x() = delete;

			UART_x & operator = (const UART_x &) = delete;
			UART_x & operator = (const UART_x &&) = delete;

			/// \brief Habilita el rellotge el modul.
			///
			static void activate() {

				#ifdef USART1_BASE
					if constexpr (channel_ == UARTChannel::_1)
						RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
				#endif
				#ifdef USART2_BASE
					if constexpr (channel_ == UARTChannel::_2)
						RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
				#endif
				#ifdef USART3_BASE
					if constexpr (channel_ == UARTChannel::_3)
						RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
				#endif
				#ifdef UART4_BASE
					if constexpr (channel_ == UARTChannel::_4)
						RCC->APB1ENR |= RCC_APB1ENR_UART4EN;
				#endif
				#ifdef UART5_BASE
					if constexpr (channel_ == UARTChannel::_5)
						RCC->APB1ENR |= RCC_APB1ENR_UART5EN;
				#endif
				#ifdef USART6_BASE
					if constexpr (channel_ == UARTChannel::_6)
						RCC->APB2ENR |= RCC_APB2ENR_USART6EN;
				#endif
				#ifdef UART7_BASE
					if constexpr (channel_ == UARTChannel::_7)
						RCC->APB1ENR |= RCC_APB1ENR_UART7EN;
				#endif
				#ifdef UART8_BASE
					if constexpr (channel_ == UARTChannel::_8)
						RCC->APB1ENR |= RCC_APB1ENR_UART8EN;
				#endif

				__DSB();
			}

			/// \brief Desabilita el rellotge del modul
			///
			static void deactivate() {

				#ifdef USART1_BASE
					if constexpr (channel_ == UARTChannel::_1)
						RCC->APB2ENR &= ~RCC_APB2ENR_USART1EN;
				#endif
				#ifdef USART2_BASE
					if constexpr (channel_ == UARTChannel::_2)
						RCC->APB1ENR &= ~RCC_APB1ENR_USART2EN;
				#endif
				#ifdef USART3_BASE
					if constexpr (channel_ == UARTChannel::_3)
						RCC->APB1ENR &= ~RCC_APB1ENR_USART3EN;
				#endif
				#ifdef UART4_BASE
					if constexpr (channel_ == UARTChannel::_4)
						RCC->APB1ENR &= ~RCC_APB1ENR_UART4EN;
				#endif
				#ifdef UART5_BASE
					if constexpr (channel_ == UARTChannel::_5)
						RCC->APB1ENR &= ~RCC_APB1ENR_UART5EN;
				#endif
				#ifdef USART6_BASE
					if constexpr (channel_ == UARTChannel::_6)
						RCC->APB2ENR &= ~RCC_APB2ENR_USART6EN;
				#endif
				#ifdef UART7_BASE
					if constexpr (channel_ == UARTChannel::_7)
						RCC->APB1ENR &= ~RCC_APB1ENR_UART7EN;
				#endif
				#ifdef UART8_BASE
					if constexpr (channel_ == UARTChannel::_8)
						RCC->APB1ENR &= ~RCC_APB1ENR_UART8EN;
				#endif
			}

		public:
			/// \bried Inicialitza el modul.
			///
			static void initialize() {

				activate();
				disable();
			}

			/// \bried Desinicialitza el modul.
			///
			static void deinitialize() {

				disable();
				deactivate();
			}

			/// \brief Reseteja el modul
			///
			static void reset() {

				#ifdef USART1_BASE
					if constexpr (channel_ == UARTChannel::_1) {
						RCC->APB2RSTR |= RCC_APB2RSTR_USART1RST;
						RCC->APB2RSTR &= ~RCC_APB2RSTR_USART1RST;
					}
				#endif
				#ifdef USART2_BASE
					if constexpr (channel_ == UARTChannel::_2) {
						RCC->APB1RSTR |= RCC_APB1RSTR_USART2RST;
						RCC->APB1RSTR &= ~RCC_APB1RSTR_USART2RST;
					}
				#endif
				#ifdef USART3_BASE
					if constexpr (channel_ == UARTChannel::_3) {
						RCC->APB1RSTR |= RCC_APB1RSTR_USART3RST;
						RCC->APB1RSTR &= ~RCC_APB1RSTR_USART3RST;
					}
				#endif
				#ifdef UART4_BASE
					if constexpr (channel_ == UARTChannel::_4) {
						RCC->APB1RSTR |= RCC_APB1RSTR_UART4RST;
						RCC->APB1RSTR &= ~RCC_APB1RSTR_UART4RST;
					}
				#endif
				#ifdef UART5_BASE
					if constexpr (channel_ == UARTChannel::_5) {
						RCC->APB1RSTR |= RCC_APB1RSTR_UART5RST;
						RCC->APB1RSTR &= ~RCC_APB1RSTR_UART5RST;
					}
				#endif
				#ifdef USART6_BASE
					if constexpr (channel_ == UARTChannel::_6) {
						RCC->APB2RSTR |= RCC_APB2RSTR_USART6RST;
						RCC->APB2RSTR &= ~RCC_APB2RSTR_USART6RST;
					}
				#endif
				#ifdef UART7_BASE
					if constexpr (channel_ == UARTChannel::_7) {
						RCC->APB1RSTR |= RCC_APB1RSTR_UART7RST;
						RCC->APB1RSTR &= ~RCC_APB1RSTR_UART7RST;
					}
				#endif
				#ifdef UART8_BASE
					if constexpr (channel_ == UARTChannel::_8) {
						RCC->APB1RSTR |= RCC_APB1RSTR_UART8RST;
						RCC->APB1RSTR &= ~RCC_APB1RSTR_UART8RST;
					}
				#endif
			}

			/// \brief Habilita el modul.
			///
			static void enable() {

				USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);
				regs->CR1 |= USART_CR1_UE;
			}

			/// \brief Habilita la transmisio
			///
			static void enableTX() {

				USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);
				ATOMIC_SET_BIT(regs->CR1, USART_CR1_TE);
			}

			/// \brief Habilita la recepcio.
			///
			static void enableRX() {

				USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);
				ATOMIC_SET_BIT(regs->CR1, USART_CR1_RE);
			}

			/// \brief Deshabilita el modul.
			///
			static void disable() {

				USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);
				regs->CR1 &= ~(USART_CR1_UE | USART_CR1_RE | USART_CR1_TE);
			}

			/// \brief Deshabilita la transmisio.
			///
			static void disableTX() {

				USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);
				ATOMIC_CLEAR_BIT(regs->CR1, USART_CR1_TE);
			}

			/// \brief Deshabilita la recepcio.
			///
			static void disableRX() {

				USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);
				ATOMIC_CLEAR_BIT(regs->CR1, USART_CR1_RE);
			}

			/// \brief Configuracio del timing.
			/// \param baudMode: Opcions de baud.
			/// \param clocCource: Opcions del clock.
			/// \param baud: El valor de velocitat.
			/// \param overSampling: Valor del sobre mostrejat
			///
			static void setTimming(
				UARTBaudMode baudMode = UARTBaudMode::_9600,
				UARTClockSource clockSource = UARTClockSource::automatic,
				unsigned rate = 0,
				UARTOverSampling overSampling = UARTOverSampling::_16) {

				USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);
				UART_setTimming(regs, baudMode, clockSource, rate, overSampling);
			}

			/// \brief Configura el protocol de comunicacio.
			/// \param work: Numero de bits de dades.
			/// \param parity: Opcions de paritat.
			/// \param stop: Numero dels bits de parada.
			/// \param handsake: El protocol hardware.
			///
			static void setProtocol(
				UARTWordBits wordBits,
				UARTParity parity,
				UARTStopBits stopBits,
				UARTHandsake handsake = UARTHandsake::none) {

				UART_setProtocol(
					reinterpret_cast<USART_TypeDef*>(_addr),
					wordBits,
					parity,
					stopBits,
					handsake);
			}

			/// \brief Inicialitza el pin TX
			///
			template <typename gpio_>
			static void initTXPin() {

				gpio_::initAlt(
					GPIODriver::pushPull,
					GPIOSpeed::fast,
					UARTPinTrait<channel_, gpio_, UARTPin::TX>::alt);
			}

			/// \brief Inicialitza el pin RX
			///
			template <typename gpio_>
			static void initRXPin() {

				gpio_::initAlt(
					GPIODriver::pushPull,
					GPIOSpeed::fast,
					UARTPinTrait<channel_, gpio_, UARTPin::RX>::alt);
			}

			/// \brief Inicialitza el pin CTS
			///
			template <typename gpio_>
			static void initCTSPin() {

				gpio_::initAlt(
					GPIODriver::pushPull,
					GPIOSpeed::fast,
					UARTPinTrait<channel_, gpio_, UARTPin::CTS>::alt);
			}

			/// \brief Inicialitza el pin RTS
			///
			template <typename gpio_>
			static void initRTSPin() {

				gpio_::initAlt(
					GPIODriver::pushPull,
					GPIOSpeed::fast,
					UARTPinTrait<channel_, gpio_, UARTPin::RTS>::alt);
			}

			/// \brief Escriu un byte en el buffer de transmissio.
			/// \param data: El byte.
			///
			static void write(
				uint8_t data) {

				USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);
				regs->TDR = data;
			}

			/// \brief Llegeix un byte del buffer de recepcio.
			/// \return El byte.
			///
			static uint8_t read() {

				USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);
				return regs->RDR;
			}

			/// \brief Habilita les interrupcions
			/// \param interrupt: La interrupcio.
			///
			static void enableInterrupt(
				UARTInterrupt interrupt) {

				USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);
				switch (interrupt) {
					case UARTInterrupt::cts:
						ATOMIC_SET_BIT(regs->CR3, USART_CR3_CTSIE);
						break;

					case UARTInterrupt::brk:
						ATOMIC_SET_BIT(regs->CR2, USART_CR2_LBDIE);
						break;

					case UARTInterrupt::idle:
						ATOMIC_SET_BIT(regs->CR1, USART_CR1_IDLEIE);
						break;

					case UARTInterrupt::txEmpty:
						ATOMIC_SET_BIT(regs->CR1, USART_CR1_TXEIE);
						break;

					case UARTInterrupt::txComplete:
						ATOMIC_SET_BIT(regs->CR1, USART_CR1_TCIE);
						break;

					case UARTInterrupt::rxNotEmpty:
						ATOMIC_SET_BIT(regs->CR1, USART_CR1_RXNEIE);
						break;

					case UARTInterrupt::parity:
						ATOMIC_SET_BIT(regs->CR1, USART_CR1_PEIE);
						break;

					case UARTInterrupt::rxTimeout:
						ATOMIC_SET_BIT(regs->CR1, USART_CR1_RTOIE);
						break;

					case UARTInterrupt::endOfBlock:
						ATOMIC_SET_BIT(regs->CR1, USART_CR1_EOBIE);
						break;

					case UARTInterrupt::match:
						ATOMIC_SET_BIT(regs->CR1, USART_CR1_CMIE);
						break;

					case UARTInterrupt::error:
						ATOMIC_SET_BIT(regs->CR3, USART_CR3_EIE);
						break;
				}
			}

			/// \brief Deshabilita les interrupcions
			/// \param event: El event.
			///
			static bool disableInterrupt(
				UARTInterrupt interrupt) {

				USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);

				bool state = false;
				switch (interrupt) {
					case UARTInterrupt::cts:
						state = (regs->CR3 & USART_CR3_CTSIE) != 0;
						ATOMIC_CLEAR_BIT(regs->CR3, USART_CR3_CTSIE);
						break;

					case UARTInterrupt::brk:
						state = (regs->CR2 & USART_CR2_LBDIE) != 0;
						ATOMIC_CLEAR_BIT(regs->CR2, USART_CR2_LBDIE);
						break;

					case UARTInterrupt::idle:
						state = (regs->CR1 & USART_CR1_IDLEIE) != 0;
						ATOMIC_CLEAR_BIT(regs->CR1, USART_CR1_IDLEIE);
						break;

					case UARTInterrupt::txEmpty:
						state = (regs->CR1 & USART_CR1_TXEIE) != 0;
						ATOMIC_CLEAR_BIT(regs->CR1, USART_CR1_TXEIE);
						break;

					case UARTInterrupt::txComplete:
						state = (regs->CR1 & USART_CR1_TCIE) != 0;
						ATOMIC_CLEAR_BIT(regs->CR1, USART_CR1_TCIE);
						break;

					case UARTInterrupt::rxNotEmpty:
						state = regs->CR1 & USART_CR1_RXNEIE;
						ATOMIC_CLEAR_BIT(regs->CR1, USART_CR1_RXNEIE);
						break;

					case UARTInterrupt::parity:
						state = (regs->CR1 & USART_CR1_PEIE) != 0;
						ATOMIC_CLEAR_BIT(regs->CR1, USART_CR1_PEIE);
						break;

					case UARTInterrupt::rxTimeout:
						state = (regs->CR1 & USART_CR1_RTOIE) != 0;
						ATOMIC_CLEAR_BIT(regs->CR1, USART_CR1_RTOIE);
						break;

					case UARTInterrupt::endOfBlock:
						state = (regs->CR1 & USART_CR1_EOBIE) != 0;
						ATOMIC_CLEAR_BIT(regs->CR1, USART_CR1_EOBIE);
						break;

					case UARTInterrupt::match:
						state = (regs->CR1 & USART_CR1_CMIE) != 0;
						ATOMIC_CLEAR_BIT(regs->CR1, USART_CR1_CMIE);
						break;

					case UARTInterrupt::error:
						state = (regs->CR3 & USART_CR3_EIE) != 0;
						ATOMIC_CLEAR_BIT(regs->CR3, USART_CR3_EIE);
						break;
				}

				return state;
			}

			/// \brief Obte un flag.
			/// \param flag: El flag.
			///
			static bool getFlag(
				UARTFlag flag) {

				USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);
				switch (flag) {
					case UARTFlag::framming:
						return (regs->ISR & USART_ISR_FE) != 0;

					case UARTFlag::idle:
						return (regs->ISR & USART_ISR_IDLE) != 0;

					case UARTFlag::noise:
						return (regs->ISR & USART_ISR_NE) != 0;

					case UARTFlag::overrun:
						return (regs->ISR & USART_ISR_ORE) != 0;

					case UARTFlag::parity:
						return (regs->ISR & USART_ISR_PE) != 0;

					case UARTFlag::txComplete:
						return (regs->ISR & USART_ISR_TC) != 0;

					case UARTFlag::txEmpty:
						return (regs->ISR & USART_ISR_TXE) != 0;

					case UARTFlag::rxNotEmpty:
						return (regs->ISR & USART_ISR_RXNE) != 0;

					case UARTFlag::rxTimeout:
						return (regs->ISR & USART_ISR_RTOF) != 0;

					case UARTFlag::cts:
						return (regs->ISR & USART_ISR_CTSIF) != 0;

					default:
						return false;
				}
			}

			/// \brief Borra el flag.
			/// \param flag: El flag.
			///
			static void clearFlag(
				UARTFlag flag) {

				USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);
				switch (flag) {
					case UARTFlag::cts:
						regs->ICR = USART_ICR_CTSCF;
						break;

					case UARTFlag::endOfBlock:
						regs->ICR = USART_ICR_EOBCF;
						break;

					case UARTFlag::framming:
						regs->ICR = USART_ICR_FECF;
						break;

					case UARTFlag::idle:
						regs->ICR = USART_ICR_IDLECF;
						break;

					case UARTFlag::noise:
						regs->ICR = USART_ICR_NCF;
						break;

					case UARTFlag::overrun:
						regs->ICR = USART_ICR_ORECF;
						break;

					case UARTFlag::parity:
						regs->ICR = USART_ICR_PECF;
						break;

					case UARTFlag::rxTimeout:
						regs->ICR = USART_ICR_RTOCF;
						break;

					case UARTFlag::txComplete:
						regs->ICR = USART_ICR_TCCF;
						break;

					case UARTFlag::brk:
						regs->ICR = USART_ICR_LBDCF;
						break;

					case UARTFlag::match:
						regs->ICR = USART_ICR_CMCF;
						break;
				}
			}

			/// \brief Asigna la funcio d'interrupcio.
			/// \param function: La funcio.
			/// \param param: El parametre.
			///
			static void setInterruptFunction(
				UARTInterruptFunction function,
				UARTInterruptParam param) {

				_isrFunction = function;
				_isrParam = param;
			}

			/// \brief Invoca la funcio d'interrupcio.
			/// \param event: L'event.
			//
			static void interruptHandler() {

				if (_isrFunction != nullptr)
                    _isrFunction(_isrParam);
            }
	};
    
    template <UARTChannel channel_> UARTInterruptFunction UART_x<channel_>::_isrFunction = nullptr;
    template <UARTChannel channel_> UARTInterruptParam UART_x<channel_>::_isrParam = nullptr;

    #ifdef USART1_BASE
        using UART_1 = UART_x<UARTChannel::_1>;
    #endif
    #ifdef USART2_BASE
        using UART_2 = UART_x<UARTChannel::_2>;
    #endif
    #ifdef USART3_BASE
        using UART_3 = UART_x<UARTChannel::_3>;
    #endif
    #ifdef UART4_BASE
        using UART_4 = UART_x<UARTChannel::_4>;
    #endif
    #ifdef UART5_BASE
        using UART_5 = UART_x<UARTChannel::_5>;
    #endif
    #ifdef USART6_BASE
        using UART_6 = UART_x<UARTChannel::_6>;
    #endif
    #ifdef UART7_BASE
        using UART_7 = UART_x<UARTChannel::_7>;
    #endif
    #ifdef UART8_BASE
        using UART_8 = UART_x<UARTChannel::_8>;
    #endif

	#ifdef USART1_BASE
		template <>
		struct UARTTrait<UARTChannel::_1> {
			static constexpr uint32_t addr = USART1_BASE;
			static constexpr INTVector vector = INTVector::uart1;
		};

		template <>
		struct UARTPinTrait<UARTChannel::_1, GPIO_A9, UARTPin::TX> {
			static constexpr GPIOAlt alt = GPIOAlt::_8;
		};

		template <>
		struct UARTPinTrait<UARTChannel::_1, GPIO_B7, UARTPin::RX> {
			static constexpr GPIOAlt alt = GPIOAlt::_8;
		};
	#endif

	#ifdef USART2_BASE
		template <>
		struct UARTTrait<UARTChannel::_2> {
			static constexpr uint32_t addr = USART2_BASE;
			static constexpr INTVector vector = INTVector::uart2;
		};
	#endif

	#ifdef USART3_BASE
		template <>
		struct UARTTrait<UARTChannel::_3> {
			static constexpr uint32_t addr = USART3_BASE;
			static constexpr INTVector vector = INTVector::uart3;
		};
	#endif

	#ifdef UART4_BASE
		template <>
		struct UARTTrait<UARTChannel::_4> {
			static constexpr uint32_t addr = UART4_BASE;
			static constexpr INTVector vector = INTVector::uart4;
		};
	#endif

	#ifdef UART5_BASE
		template <>
		struct UARTTrait<UARTChannel::_5> {
			static constexpr uint32_t addr = UART5_BASE;
			static constexpr INTVector vector = INTVector::uart5;
		};
	#endif

	#ifdef USART6_BASE
		template <>
		struct UARTTrait<UARTChannel::_6> {
			static constexpr uint32_t addr = USART6_BASE;
			static constexpr INTVector vector = INTVector::uart6;
		};

		template <>
		struct UARTPinTrait<UARTChannel::_6, GPIO_C6, UARTPin::TX> {
			static constexpr GPIOAlt alt = GPIOAlt::_8;
		};

		template <>
		struct UARTPinTrait<UARTChannel::_6, GPIO_C7, UARTPin::RX> {
			static constexpr GPIOAlt alt = GPIOAlt::_8;
		};
	#endif

	#ifdef UART7_BASE
		template <>
		struct UARTTrait<UARTChannel::_7> {
			static constexpr uint32_t addr = UART7_BASE;
			static constexpr INTVector vector = INTVector::uart7;
		};
	#endif

	#ifdef UART8_BASE
		template <>
		struct UARTTrait<UARTChannel::_8> {
			static constexpr uint32_t addr = UART8_BASE;
			static constexpr INTVector vector = INTVector::uart8;
		};
	#endif


	class UARTWrapper {
		protected:
			UARTWrapper() = default;
			virtual ~UARTWrapper() = default;

		public:
			virtual void write(uint8_t data) const = 0;
			virtual uint8_t read() const = 0;
			virtual void enableTX() const = 0;
			virtual void enableRX() const = 0;
			virtual void disableTX() const = 0;
			virtual void disableRX() const = 0;
			virtual void setInterruptFunction(UARTInterruptFunction function, UARTInterruptParam param) const = 0;
			virtual void enableInterrupt(UARTInterrupt interrupt) const = 0;
			virtual bool disableInterrupt(UARTInterrupt interrupt) const = 0;
			virtual bool getFlag(UARTFlag flag) const = 0;
			virtual void clearFlag(UARTFlag flag) const = 0;
	};

	template <typename uart_>
	class UARTWrapper_x final: public UARTWrapper {
		private:
			UARTWrapper_x() = default;
			UARTWrapper_x(const UARTWrapper_x &) = delete;
			UARTWrapper_x(const UARTWrapper_x &&) = delete;

			UARTWrapper & operator = (const UARTWrapper_x &) = delete;
			UARTWrapper & operator = (const UARTWrapper_x &&) = delete;

		public:
			static UARTWrapper_x& instance() {
				static UARTWrapper_x adapter;
				return adapter;
			}

			void write(uint8_t data) const override {
				uart_::write(data);
			}

			uint8_t read() const override {
				return uart_::read();
			}

			void enableTX() const override {
				uart_::enableTX();
			}

			void enableRX() const override {
				uart_::enableRX();
			}

			void disableTX() const override {
				uart_::disableTX();
			}

			void disableRX() const override {
				uart_::disableRX();
			}

			void setInterruptFunction(UARTInterruptFunction function, UARTInterruptParam param) const {
				uart_::setInterruptFunction(function, param);
			}

			void enableInterrupt(UARTInterrupt interrupt) const override {
				uart_::enableInterrupt(interrupt);
			}

			bool disableInterrupt(UARTInterrupt interrupt) const override {
				return uart_::disableInterrupt(interrupt);
			}

			bool getFlag(UARTFlag flag) const override {
				return uart_::getFlag(flag);
			}

			void clearFlag(UARTFlag flag) const override {
				uart_::clearFlag(flag);
			}
	};

	template <typename uart_>
	UARTWrapper& getUARTWrapper() {
		return UARTWrapper_x<uart_>::instance();
	}
}


#endif // __STM32_htlUART__

