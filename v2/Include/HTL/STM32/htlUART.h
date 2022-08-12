#pragma once
#ifndef __STM32_htlUART__
#define __STM32_htlUART__


// EOS includes
//
#include "HTL/htl.h"
#include "HTL/STM32/htlGPIO.h"


namespace htl {

	enum class UARTChannel {
        #ifdef USART1
            _1,
        #endif
        #ifdef USART2
            _2,
        #endif
        #ifdef USART3
            _3,
        #endif
        #ifdef UART4
            _4,
        #endif
        #ifdef UART5
            _5,
        #endif
        #ifdef USART6
            _6,
        #endif
        #ifdef UART7
            _7,
        #endif
        #ifdef UART8
            _8,
        #endif
	};

	enum class UARTParity {
		none,
		even,
		odd
	};

	enum class UARTWord {
		_7,
		_8
	};

	enum class UARTStop {
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

	enum class UARTEvent {
		cts,
		brk,
		endOfBlock,
		txEmpty,
		txComplete,
		rxNotEmpty,
		rxTimeout,
		idle,
		parity,
		framming,
		overrun,
		noise
	};

	enum class UARTPin {
		TX,
		RX
	};

	using UARTInterruptParam = void*;
	using UARTInterruptFunction = void (*)(UARTEvent, UARTInterruptParam);

	void UART_init();
	void UART_setProtocol(USART_TypeDef*, UARTWord, UARTParity, UARTStop);
	void UART_setTimming(USART_TypeDef*, UARTBaudMode, UARTClockSource, unsigned, UARTOverSampling);
	void UART_enableInterrupt(USART_TypeDef*, UARTEvent);
	bool UART_disableInterrupt(USART_TypeDef*, UARTEvent);

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

			static void enableClock() {

				if constexpr (channel_ == UARTChannel::_1)
					RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
				if constexpr (channel_ == UARTChannel::_2)
					RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
				if constexpr (channel_ == UARTChannel::_3)
					RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
				if constexpr (channel_ == UARTChannel::_4)
					RCC->APB1ENR |= RCC_APB1ENR_UART4EN;
				if constexpr (channel_ == UARTChannel::_5)
					RCC->APB1ENR |= RCC_APB1ENR_UART5EN;
				if constexpr (channel_ == UARTChannel::_6)
					RCC->APB2ENR |= RCC_APB2ENR_USART6EN;
				if constexpr (channel_ == UARTChannel::_7)
					RCC->APB1ENR |= RCC_APB1ENR_UART7EN;
				if constexpr (channel_ == UARTChannel::_8)
					RCC->APB1ENR |= RCC_APB1ENR_UART8EN;

				__DSB();

			}

			static void disableClock() {

				if constexpr (channel_ == UARTChannel::_1)
					RCC->APB2ENR &= ~RCC_APB2ENR_USART1EN;
				if constexpr (channel_ == UARTChannel::_2)
					RCC->APB1ENR &= ~RCC_APB1ENR_USART2EN;
				if constexpr (channel_ == UARTChannel::_3)
					RCC->APB1ENR &= ~RCC_APB1ENR_USART3EN;
				if constexpr (channel_ == UARTChannel::_4)
					RCC->APB1ENR &= ~RCC_APB1ENR_UART4EN;
				if constexpr (channel_ == UARTChannel::_5)
					RCC->APB1ENR &= ~RCC_APB1ENR_UART5EN;
				if constexpr (channel_ == UARTChannel::_6)
					RCC->APB2ENR &= ~RCC_APB2ENR_USART6EN;
				if constexpr (channel_ == UARTChannel::_7)
					RCC->APB1ENR &= ~RCC_APB1ENR_UART7EN;
				if constexpr (channel_ == UARTChannel::_8)
					RCC->APB1ENR &= ~RCC_APB1ENR_UART8EN;
			}

		public:
			/// \bried Inicialitza el modul.
			///
			static void init() {

				enableClock();

				USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);
				regs->CR1 &= ~USART_CR1_UE;
			    regs->CR3 &= ~(USART_CR3_SCEN | USART_CR3_HDSEL | USART_CR3_IREN);
			}

			/// \bried Desinicialitza el modul.
			///
			static void deInit() {

				disable();
				disableClock();
			}

			/// \brief Habilita el modul per comunicar
			///
			static void enable() {

				USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);
				regs->CR1 |= USART_CR1_UE;
			}

			/// \brief Deshabilita el modul per comunicar
			///
			static void disable() {

				USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);
				regs->CR1 &= ~USART_CR1_UE;
			}

			/// \brief Configuracio del timing.
			/// \param baudMode: Opcions de baud.
			/// \param clockMode: Opcions del clock.
			/// \param baud: El valor de velocitat.
			/// \param overSampling: Valor del sobre mostrejat
			///
			static void setTimming(
				UARTBaudMode baudMode,
				UARTClockSource clockSource,
				unsigned rate = 0,
				UARTOverSampling overSampling = UARTOverSampling::_16) {

				USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);
				UART_setTimming(regs, baudMode, clockSource, rate, overSampling);
			}

			static void setProtocol(
				UARTWord word,
				UARTParity parity,
				UARTStop stop) {

				UART_setProtocol(
					reinterpret_cast<USART_TypeDef*>(_addr),
					word,
					parity,
					stop);
			}

			template <typename gpio_>
			static void initTXPin() {
				gpio_::initAlt(
					GPIODriver::pushPull,
					GPIOSpeed::fast,
					UARTPinTrait<channel_, gpio_, UARTPin::TX>::alt);
			}

			template <typename gpio_>
			static void initRXPin() {
				gpio_::initAlt(
					GPIODriver::pushPull,
					GPIOSpeed::fast,
					UARTPinTrait<channel_, gpio_, UARTPin::RX>::alt);
			}

			static void send(
				uint8_t data) {

				USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);
				regs->TDR = data;
			}

			static uint8_t receive() {

				USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);
				return regs->RDR;
			}

			static constexpr void enableInterrupt(
				UARTEvent event) {

				USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);
				UART_enableInterrupt(regs, event);
			}

			static constexpr bool disableInterrupt(
				UARTEvent event) {

				USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);
				return UART_disableInterrupt(regs, event);
			}

			static constexpr bool getInterruptFlag(
				UARTEvent event) {

				USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);
				switch (event) {
					case UARTEvent::framming:
						return (regs->ISR & USART_ISR_FE) != 0;

					case UARTEvent::noise:
						return (regs->ISR & USART_ISR_NE) != 0;

					case UARTEvent::overrun:
						return (regs->ISR & ~USART_ISR_ORE) != 0;

					case UARTEvent::parity:
						return (regs->ISR & ~USART_ISR_PE) != 0;

					case UARTEvent::txComplete:
						return (regs->ISR & ~USART_ISR_TC) != 0;

					case UARTEvent::txEmpty:
						return (regs->ISR & ~USART_ISR_TXE) != 0;

					case UARTEvent::rxNotEmpty:
						return (regs->ISR & ~USART_ISR_RXNE) != 0;

					default:
						return false;
				}
			}

			static constexpr void clearInterruptFlag(
				UARTEvent event) {

				USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);
				switch (event) {
					case UARTEvent::framming:
						regs->ISR &= USART_ISR_FE;
						break;

					case UARTEvent::noise:
						regs->ISR &= USART_ISR_NE;
						break;

					case UARTEvent::overrun:
						regs->ISR &= ~USART_ISR_ORE;
						break;

					case UARTEvent::parity:
						regs->ISR &= ~USART_ISR_PE;
						break;

					case UARTEvent::txComplete:
						regs->ISR &= ~USART_ISR_TC;
						break;

					case UARTEvent::txEmpty:
						regs->ISR &= ~USART_ISR_TXE;
						break;

					case UARTEvent::rxNotEmpty:
						regs->ISR &= ~USART_ISR_RXNE;
						break;
				}
			}

			/// \brief Borre tots els flags d'interrupcio.
			///
			inline static void clearInterruptFlags() {

				USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);
				regs->ISR &= ~(USART_ISR_RXNE | USART_ISR_TXE | USART_ISR_TC |
					USART_ISR_PE | USART_ISR_ORE | USART_ISR_FE | USART_ISR_NE);
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
			static void interruptHandler(
				UARTEvent event) {

				if (_isrFunction != nullptr)
                    _isrFunction(event, _isrParam);
            }
	};
    
    template <UARTChannel channel_> UARTInterruptFunction UART_x<channel_>::_isrFunction = nullptr;
    template <UARTChannel channel_> UARTInterruptParam UART_x<channel_>::_isrParam = nullptr;


    #ifdef USART1
        using UART_1 = UART_x<UARTChannel::_1>;
    #endif
    #ifdef USART2
        using UART_2 = UART_x<UARTChannel::_2>;
    #endif
    #ifdef USART3
        using UART_3 = UART_x<UARTChannel::_3>;
    #endif
    #ifdef UART4
        using UART_4 = UART_x<UARTChannel::_4>;
    #endif
    #ifdef UART5
        using UART_5 = UART_x<UARTChannel::_5>;
    #endif
    #ifdef USART6
        using UART_6 = UART_x<UARTChannel::_6>;
    #endif
    #ifdef UART7
        using UART_7 = UART_x<UARTChannel::_7>;
    #endif
    #ifdef UART8
        using UART_8 = UART_x<UARTChannel::_8>;
    #endif

	#ifdef USART1
		template <>
		struct UARTTrait<UARTChannel::_1> {
			static constexpr uint32_t addr = USART1_BASE;
		};
	#endif

	#ifdef USART2
		template <>
		struct UARTTrait<UARTChannel::_2> {
			static constexpr uint32_t addr = USART2_BASE;
		};
	#endif

	#ifdef USART3
		template <>
		struct UARTTrait<UARTChannel::_3> {
			static constexpr uint32_t addr = USART3_BASE;
		};
	#endif

	#ifdef UART4
		template <>
		struct UARTTrait<UARTChannel::_4> {
			static constexpr uint32_t addr = UART4_BASE;
		};
	#endif

	#ifdef UART5
		template <>
		struct UARTTrait<UARTChannel::_5> {
			static constexpr uint32_t addr = UART5_BASE;
		};
	#endif

	#ifdef USART6
		template <>
		struct UARTTrait<UARTChannel::_6> {
			static constexpr uint32_t addr = USART6_BASE;
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

	#ifdef UART7
		template <>
		struct UARTTrait<UARTChannel::_7> {
			static constexpr uint32_t addr = UART7_BASE;
		};
	#endif

	#ifdef UART8
		template <>
		struct UARTTrait<UARTChannel::_8> {
			static constexpr uint32_t addr = UART8_BASE;
		};
	#endif

}


#endif // __STM32_htlUART__

