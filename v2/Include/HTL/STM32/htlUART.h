#pragma once
#ifndef __STM32_htlUART__
#define __STM32_htlUART__


// EOS includes
//
#include "HTL/htl.h"
#include "HTL/STM32/htlGPIO.h"
#include "HTL/STM32/htlINT.h"


// Detecta les opcions suportades
//
#if defined(EOS_PLATFORM_STM32F0)
	#define HTL_UART_7BIT_SUPPORT 0
	#define HTL_UART_LINMODE_SUPPORT 0
	#define HTL_UART_SMARTCARD_SUPPORT 0
#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
	#define HTL_UART_7BIT_SUPPORT 1
	#define HTL_UART_LINMODE_SUPPORT 1
	#define HTL_UART_SMARTCARD_SUPPORT 1
#elif defined(EOS_PLATFORM_STM32G0)
	#define HTL_UART_7BIT_SUPPORT 0
	#define HTL_UART_LINMODE_SUPPORT 0
	#define HTL_UART_SMARTCARD_SUPPORT 0
#else
	#error "Unknown platform"
#endif


#if defined(EOS_PLATFORM_STM32G0)
	namespace htl {
		#ifdef HTL_UART1_EXIST
			inline void UART1ClockEnable() {
				RCC->APBENR2 |= RCC_APBENR2_USART1EN;
			}
			inline void UART1ClockDisable() {
				RCC->APBENR2 &= ~RCC_APBENR2_USART1EN;
			}
			inline void UART1Reset() {
				RCC->APBRSTR2 |= RCC_APBRSTR2_USART1RST;
				RCC->APBRSTR2 &= ~RCC_APBRSTR2_USART1RST;
			}
		#endif
		#ifdef HTL_UART2_EXIST
			inline void UART2ClockEnable() {
				RCC->APBENR1 |= RCC_APBENR1_USART2EN;
			}
			inline void UART2ClockDisable() {
				RCC->APBENR1 &= ~RCC_APBENR1_USART2EN;
			}
			inline void UART2Reset() {
				RCC->APBRSTR1 |= RCC_APBRSTR1_USART2RST;
				RCC->APBRSTR1 &= ~RCC_APBRSTR1_USART2RST;
			}
		#endif
	}
#elif defined(EOS_PLATFORM_STM32F0)
	namespace htl {
		#ifdef HTL_UART1_EXIST
			inline void UART1ClockEnable() {
				RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
			}
			inline void UART1ClockDisable() {
				RCC->APB2ENR &= ~RCC_APB2ENR_USART1EN;
			}
			inline void UART1Reset() {
				RCC->APB2RSTR |= RCC_APB2RSTR_USART1RST;
				RCC->APB2RSTR &= ~RCC_APB2RSTR_USART1RST;
			}
		#endif
		#ifdef HTL_UART2_EXIST
			inline void UART2ClockEnable() {
				RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
			}
			inline void UART2ClockDisable() {
				RCC->APB1ENR &= ~RCC_APB1ENR_USART2EN;
			}
			inline void UART2Reset() {
				RCC->APB1RSTR |= RCC_APB1RSTR_USART2RST;
				RCC->APB1RSTR &= ~RCC_APB1RSTR_USART2RST;
			}
		#endif
		#ifdef HTL_EXIST_USART3
			inline void UART3Reset() {
				RCC->APB1RSTR |= RCC_APB1RSTR_USART3RST;
				RCC->APB1RSTR &= ~RCC_APB1RSTR_USART3RST;
			}
		#endif
		#ifdef HTL_EXIST_USART4
			inline void UART4Reset() {
				RCC->APB1RSTR |= RCC_APB1RSTR_USART4RST;
				RCC->APB1RSTR &= ~RCC_APB1RSTR_USART4RST;
			}
		#endif
	}
#else
	#error Unsuported platform
#endif


namespace htl {

	enum class UARTChannel {
        #ifdef HTL_UART1_EXIST
            _1,
        #endif
        #ifdef HTL_UART2_EXIST
            _2,
        #endif
        #ifdef HTL_UART3_EXIST
            _3,
        #endif
        #ifdef HTL_UART4_EXIST
            _4,
        #endif
        #ifdef HTL_UART5_EXIST
            _5,
        #endif
        #ifdef HTL_UART6_EXIST
            _6,
        #endif
        #ifdef HTL_UART7_EXIST
            _7,
        #endif
        #ifdef HTL_UART8_EXIST
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
		#if HTL_UART_7BIT_SUPPORT == 1
			_7,
		#endif
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
		#if HTL_UART_LINMODE_SUPPORT == 1
			linBrk,
		#endif
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
		#if HTL_UART_LINMODE_SUPPORT == 1
			linBrk,
		#endif
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

	template <UARTChannel>
	struct UARTTrait {
	};

	template <UARTChannel, typename, UARTPin>
	struct UARTPinTrait {
	};

	class UARTBase_x {
		protected:
			static void setProtocol(USART_TypeDef*, UARTWordBits, UARTParity, UARTStopBits, UARTHandsake);
			static void setTimming(USART_TypeDef*, UARTBaudMode, UARTClockSource, uint32_t, UARTOverSampling);
	};

	template <UARTChannel channel_>
	class UART_x final: public UARTBase_x {
		private:
			using Trait = UARTTrait<channel_>;

		public:
			static constexpr UARTChannel channel = channel_;

		private:
			static constexpr uint32_t _addr = Trait::addr;
			static UARTInterruptFunction _isrFunction;
			static UARTInterruptParam _isrParam;

		private:
			UART_x() = default;
			UART_x(const UART_x &) = delete;
			UART_x(const UART_x &&) = delete;
			~UART_x() = delete;

			UART_x & operator = (const UART_x &) = delete;
			UART_x & operator = (const UART_x &&) = delete;

			/// \brief Habilita el rellotge el modul.
			///
			static void activate() {

				#ifdef HTL_UART1_EXIST
					if constexpr (channel_ == UARTChannel::_1)
						UART1ClockEnable();
				#endif
				#ifdef HTL_UART2_EXIST
					if constexpr (channel_ == UARTChannel::_2)
						UART2ClockEnable();
				#endif
				#ifdef HTL_UART3_EXIST
					if constexpr (channel_ == UARTChannel::_3)
						RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
				#endif
				#ifdef HTL_UART4_EXIST
					if constexpr (channel_ == UARTChannel::_4)
						RCC->APB1ENR |= RCC_APB1ENR_UART4EN;
				#endif
				#ifdef HTL_UART5_EXIST
					if constexpr (channel_ == UARTChannel::_5)
						RCC->APB1ENR |= RCC_APB1ENR_UART5EN;
				#endif
				#ifdef HTL_UART6_EXIST
					if constexpr (channel_ == UARTChannel::_6)
						RCC->APB2ENR |= RCC_APB2ENR_USART6EN;
				#endif
				#ifdef HTL_UART7_EXIST
					if constexpr (channel_ == UARTChannel::_7)
						RCC->APB1ENR |= RCC_APB1ENR_UART7EN;
				#endif
				#ifdef HTL_UART8_EXIST
					if constexpr (channel_ == UARTChannel::_8)
						RCC->APB1ENR |= RCC_APB1ENR_UART8EN;
				#endif

				__DSB();
			}

			/// \brief Desabilita el rellotge del modul
			///
			static void deactivate() {

				#ifdef HTL_UART1_EXIST
					if constexpr (channel_ == UARTChannel::_1)
						UART1ClockDisable();
				#endif
				#ifdef HTL_UART2_EXIST
					if constexpr (channel_ == UARTChannel::_2)
						UART2ClockDisable();
				#endif
				#ifdef HTL_UART3_EXIST
					if constexpr (channel_ == UARTChannel::_3)
						RCC->APB1ENR &= ~RCC_APB1ENR_USART3EN;
				#endif
				#ifdef HTL_UART4_EXIST
					if constexpr (channel_ == UARTChannel::_4)
						RCC->APB1ENR &= ~RCC_APB1ENR_UART4EN;
				#endif
				#ifdef HTL_UART5_EXIST
					if constexpr (channel_ == UARTChannel::_5)
						RCC->APB1ENR &= ~RCC_APB1ENR_UART5EN;
				#endif
				#ifdef HTL_UART6_EXIST
					if constexpr (channel_ == UARTChannel::_6)
						RCC->APB2ENR &= ~RCC_APB2ENR_USART6EN;
				#endif
				#ifdef HTL_UART7_EXIST
					if constexpr (channel_ == UARTChannel::_7)
						RCC->APB1ENR &= ~RCC_APB1ENR_UART7EN;
				#endif
				#ifdef HTL_UART8_EXIST
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

				#ifdef HTL_UART1_EXIST
					if constexpr (channel_ == UARTChannel::_1)
						UART1Reset();
				#endif
				#ifdef HTL_UART2_EXIST
					if constexpr (channel_ == UARTChannel::_2)
						UART2Reset();
				#endif
				#ifdef HTL_UART3_EXIST
					if constexpr (channel_ == UARTChannel::_3)
						UART3Reset();
				#endif
				#ifdef HTL_UART4_EXIST
					if constexpr (channel_ == UARTChannel::_4)
						UART4Reset();
				#endif
				#ifdef HTL_UART5_EXIST
					if constexpr (channel_ == UARTChannel::_5)
						UART5Reset();
				#endif
				#ifdef HTL_UART6_EXIST
					if constexpr (channel_ == UARTChannel::_6)
						UART6Reset();
				#endif
				#ifdef HTL_UART7_EXIST
					if constexpr (channel_ == UARTChannel::_7)
						UART7Reset();
				#endif
				#ifdef HTL_UART8_EXIST
					if constexpr (channel_ == UARTChannel::_8)
						UART8Reset();
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
				uint32_t rate = 0,
				UARTOverSampling overSampling = UARTOverSampling::_16) {

				UARTBase_x::setTimming(
					reinterpret_cast<USART_TypeDef*>(_addr),
					baudMode,
					clockSource,
					rate,
					overSampling);
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

				UARTBase_x::setProtocol(
					reinterpret_cast<USART_TypeDef*>(_addr),
					wordBits,
					parity,
					stopBits,
					handsake);
			}

			/// \brief Configura el timeout per recepcio.
			/// \param bits: Nombre de bits perduts per generar timeout
			///
			static void setRxTimeout(
				uint32_t lostBits) {

				if constexpr (Trait::supportedRxTimeout) {
					USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);
					if (lostBits > 0) {
						regs->RTOR |= (lostBits << USART_RTOR_RTO_Pos) & USART_RTOR_RTO_Msk;
						regs->CR2 |= USART_CR2_RTOEN;
					}
					else
						regs->CR2 &= ~USART_CR2_RTOEN;
				}
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

					#if HTL_UART_LINMODE_SUPPORT == 1
						case UARTInterrupt::linBrk:
							ATOMIC_SET_BIT(regs->CR2, USART_CR2_LBDIE);
							break;
					#endif

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
						if constexpr (Trait::supportedRxTimeout)
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

					#if HTL_UART_LINMODE_SUPPORT == 1
						case UARTInterrupt::linBrk:
							state = (regs->CR2 & USART_CR2_LBDIE) != 0;
							ATOMIC_CLEAR_BIT(regs->CR2, USART_CR2_LBDIE);
							break;
					#endif

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
						if constexpr (Trait::supportedRxTimeout) {
							state = (regs->CR1 & USART_CR1_RTOIE) != 0;
							ATOMIC_CLEAR_BIT(regs->CR1, USART_CR1_RTOIE);
						}
						break;

					#ifdef USART_CR1_EOBIE
						case UARTInterrupt::endOfBlock:
							state = (regs->CR1 & USART_CR1_EOBIE) != 0;
							ATOMIC_CLEAR_BIT(regs->CR1, USART_CR1_EOBIE);
							break;
					#endif

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

			/// \brief Comprova si la interrupcio esta habilidata
			// \param interrupt: La interrupcio.
			// \return True si esta habilitada, false en cas conmtrari
			//
			static bool isInterruptEnabled(
				UARTInterrupt interrupt) {

				USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);

				bool state = false;
				switch (interrupt) {
					case UARTInterrupt::cts:
						state = (regs->CR3 & USART_CR3_CTSIE) != 0;
						break;

					#if HTL_UART_LINMODE_SUPPORT == 1
						case UARTInterrupt::linBrk:
							state = (regs->CR2 & USART_CR2_LBDIE) != 0;
							break;
					#endif

					case UARTInterrupt::idle:
						state = (regs->CR1 & USART_CR1_IDLEIE) != 0;
						break;

					case UARTInterrupt::txEmpty:
						state = (regs->CR1 &USART_CR1_TXEIE) != 0;
						break;

					case UARTInterrupt::txComplete:
						state = (regs->CR1 & USART_CR1_TCIE) != 0;
						break;

					case UARTInterrupt::rxNotEmpty:
						state = (regs->CR1 & USART_CR1_RXNEIE) != 0;
						break;

					case UARTInterrupt::parity:
						state = (regs->CR1 & USART_CR1_PEIE) != 0;
						break;

					case UARTInterrupt::rxTimeout:
						if constexpr (Trait::supportedRxTimeout)
							state = (regs->CR1 & USART_CR1_RTOIE) != 0;
						break;

					case UARTInterrupt::endOfBlock:
						state = (regs->CR1 & USART_CR1_EOBIE) != 0;
						break;

					case UARTInterrupt::match:
						state = (regs->CR1, USART_CR1_CMIE) != 0;
						break;

					case UARTInterrupt::error:
						state = (regs->CR3 & USART_CR3_EIE) != 0;
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
						if constexpr (Trait::supportedRxTimeout)
							return (regs->ISR & USART_ISR_RTOF) != 0;
						else
							return false;

					case UARTFlag::cts:
						return (regs->ISR & USART_ISR_CTSIF) != 0;

					default:
						return false;
				}
			}

			static bool isTxEmpty()  {

				return  getFlag(UARTFlag::txEmpty);
			}

			static bool isTxComplete()  {

				return  getFlag(UARTFlag::txComplete);
			}

			static bool isRxNotEmpty() {

				return getFlag(UARTFlag::rxNotEmpty);
			}

			static bool isRxTimeout() {

				if constexpr (Trait::suportedRxTimeout)
					return getFlag(UARTFlag::rxTimeout);
				else
					return false;
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

					#ifdef USART_ICR_EOBCF
						case UARTFlag::endOfBlock:
							regs->ICR = USART_ICR_EOBCF;
							break;
					#endif

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
						if constexpr (Trait::supportedRxTimeout)
							regs->ICR = USART_ICR_RTOCF;
						break;

					case UARTFlag::txComplete:
						regs->ICR = USART_ICR_TCCF;
						break;

					#if HTL_UART_LINMODE_SUPPORT == 1
						case UARTFlag::linBrk:
							regs->ICR = USART_ICR_LBDCF;
							break;
					#endif

					case UARTFlag::match:
						regs->ICR = USART_ICR_CMCF;
						break;

					default:
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

    #ifdef HTL_UART1_EXIST
        using UART_1 = UART_x<UARTChannel::_1>;
    #endif
    #ifdef HTL_UART2_EXIST
        using UART_2 = UART_x<UARTChannel::_2>;
    #endif
    #ifdef HTL_UART3_EXIST
        using UART_3 = UART_x<UARTChannel::_3>;
    #endif
    #ifdef HTL_UART4_EXIST
        using UART_4 = UART_x<UARTChannel::_4>;
    #endif
    #ifdef HTL_UART5_EXIST
        using UART_5 = UART_x<UARTChannel::_5>;
    #endif
    #ifdef HTL_UART6_EXIST
        using UART_6 = UART_x<UARTChannel::_6>;
    #endif
    #ifdef HTL_UART7_EXIST
        using UART_7 = UART_x<UARTChannel::_7>;
    #endif
    #ifdef HTL_UART8_EXIST
        using UART_8 = UART_x<UARTChannel::_8>;
    #endif

	#ifdef HTL_UART1_EXIST
		template <>
		struct UARTTrait<UARTChannel::_1> {
			static constexpr uint32_t addr = USART1_BASE;
			static constexpr INTVector vector = INTVector::uart1;
			static constexpr bool supportedRxTimeout = true;
		};
	#endif

	#ifdef HTL_UART2_EXIST
		template <>
		struct UARTTrait<UARTChannel::_2> {
			static constexpr uint32_t addr = USART2_BASE;
			static constexpr INTVector vector = INTVector::uart2;
			#if defined(EOS_PLATFORM_STM32F0)
				static constexpr bool supportedRxTimeout = false;
			#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr bool supportedRxTimeout = true;
			#elif defined(EOS_PLATFORM_STM32G0)
				static constexpr bool supportedRxTimeout = false;
			#else
				#error Plataforma no soportada
			#endif
		};
	#endif

	#ifdef HTL_UART3_EXIST
		template <>
		struct UARTTrait<UARTChannel::_3> {
			static constexpr uint32_t addr = USART3_BASE;
			static constexpr INTVector vector = INTVector::uart3;
			static constexpr bool supportedRxTimeout = true;
		};
	#endif

	#ifdef HTL_UART4_EXIST
		template <>
		struct UARTTrait<UARTChannel::_4> {
			static constexpr uint32_t addr = UART4_BASE;
			static constexpr INTVector vector = INTVector::uart4;
			static constexpr bool supportedRxTimeout = true;
		};
	#endif

	#ifdef HTL_UART5_EXIST
		template <>
		struct UARTTrait<UARTChannel::_5> {
			static constexpr uint32_t addr = UART5_BASE;
			static constexpr INTVector vector = INTVector::uart5;
			static constexpr bool supportedRxTimeout = true;
		};
	#endif

	#ifdef HTL_UART6_EXIST
		template <>
		struct UARTTrait<UARTChannel::_6> {
			static constexpr uint32_t addr = USART6_BASE;
			static constexpr INTVector vector = INTVector::uart6;
			static constexpr bool supportedRxTimeout = true;
		};
	#endif

	#ifdef HTL_UART7_EXIST
		template <>
		struct UARTTrait<UARTChannel::_7> {
			static constexpr uint32_t addr = UART7_BASE;
			static constexpr INTVector vector = INTVector::uart7;
			static constexpr bool supportedRxTimeout = true;
		};
	#endif

	#ifdef HTL_UART8_EXIST
		template <>
		struct UARTTrait<UARTChannel::_8> {
			static constexpr uint32_t addr = UART8_BASE;
			static constexpr INTVector vector = INTVector::uart8;
			static constexpr bool supportedRxTimeout = true;
		};
	#endif

}


#if defined(EOS_PLATFORM_STM32G030)
    #include "htl/STM32/htlUART_AF_G030.h"
    
#elif defined(EOS_PLATFORM_STM32G031)
    #include "htl/STM32/htlUART_AF_G031.h"
    
#elif defined(EOS_PLATFORM_STM32F030)
    #include "htl/STM32/htlUART_AF_F030.h"
    
#elif defined(EOS_PLATFORM_STM32F4)
    #include "htl/STM32/htlUART_AF_F4.h"
    
#elif defined(EOS_PLATFORM_STM32F7)
    #include "htl/STM32/htlUART_AF_F7.h"
    
#else
    #error "Unknown platform"
#endif


#endif // __STM32_htlUART__

