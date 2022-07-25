#pragma once
#ifndef __STM32_htlUART__
#define __STM32_htlUART__


// EOS includes
//
#include "eos.h"
#include "HTL/STM32/htlGPIO.h"


namespace htl {

	enum class UARTChannel {
        #ifdef USART1
            channel1,
        #endif
        #ifdef USART2
            channel2,
        #endif
        #ifdef USART3
            channel3,
        #endif
        #ifdef UART4
            channel4,
        #endif
        #ifdef UART5
            channel5,
        #endif
        #ifdef USART6
            channel6,
        #endif
        #ifdef UART7
            channel7,
        #endif
        #ifdef UART8
            channel8,
        #endif
	};

	enum class UARTParity {
		none,
		even,
		odd
	};

	enum class UARTWord {
		word7,
		word8
	};

	enum class UARTStop {
		stop0_5,
		stop1,
		stop1_5,
		stop2
	};

	enum class UARTBaudMode {
		b1200,
		b2400,
		b4800,
		b9600,
		b19200,
		b38400,
		b57600,
		b115200,
		div,
		rate,
		automatic
	};

	enum class UARTClockMode {
		pclk,
		sysclk,
		hsi,
		lse
	};

	enum class UARTOverSampling {
		os8,
		os16
	};

	enum class UARTEvent {
		cts,
		brk,
		txEmpty,
		txComplete,
		rxFull,
		idle,
		parity,
		framming,
		overrun,
		noise,
		error
	};

	using UARTInterruptParam = void*;
	using UARTInterruptFunction = void (*)(UARTEvent, UARTInterruptParam);

	void UART_init();
	void UART_setProtocol(USART_TypeDef*, UARTWord, UARTParity, UARTStop);
	void UART_setTimming(USART_TypeDef*, UARTBaudMode, UARTClockMode, unsigned rate, UARTOverSampling);
	void UART_enableInterrupt(USART_TypeDef*, UARTEvent);
	bool UART_disableInterrupt(USART_TypeDef*, UARTEvent);

	template <UARTChannel>
	struct UARTTrait {
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

				if constexpr (channel_ == UARTChannel::channel1)
					RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
				if constexpr (channel_ == UARTChannel::channel2)
					RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
				if constexpr (channel_ == UARTChannel::channel3)
					RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
				if constexpr (channel_ == UARTChannel::channel4)
					RCC->APB1ENR |= RCC_APB1ENR_UART4EN;
				if constexpr (channel_ == UARTChannel::channel5)
					RCC->APB1ENR |= RCC_APB1ENR_UART5EN;
				if constexpr (channel_ == UARTChannel::channel6)
					RCC->APB2ENR |= RCC_APB2ENR_USART6EN;
				if constexpr (channel_ == UARTChannel::channel7)
					RCC->APB1ENR |= RCC_APB1ENR_UART7EN;
				if constexpr (channel_ == UARTChannel::channel8)
					RCC->APB1ENR |= RCC_APB1ENR_UART8EN;

				__DSB();

			}

			static void disableClock() {

				if constexpr (channel_ == UARTChannel::channel1)
					RCC->APB2ENR &= ~RCC_APB2ENR_USART1EN;
				if constexpr (channel_ == UARTChannel::channel2)
					RCC->APB1ENR &= ~RCC_APB1ENR_USART2EN;
				if constexpr (channel_ == UARTChannel::channel3)
					RCC->APB1ENR &= ~RCC_APB1ENR_USART3EN;
				if constexpr (channel_ == UARTChannel::channel4)
					RCC->APB1ENR &= ~RCC_APB1ENR_UART4EN;
				if constexpr (channel_ == UARTChannel::channel5)
					RCC->APB1ENR &= ~RCC_APB1ENR_UART5EN;
				if constexpr (channel_ == UARTChannel::channel6)
					RCC->APB2ENR &= ~RCC_APB2ENR_USART6EN;
				if constexpr (channel_ == UARTChannel::channel7)
					RCC->APB1ENR &= ~RCC_APB1ENR_UART7EN;
				if constexpr (channel_ == UARTChannel::channel8)
					RCC->APB1ENR &= ~RCC_APB1ENR_UART8EN;
			}

		public:
			/// \bried Inicialitza el modul.
			///
			static void init() {

				enableClock();
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
				UARTClockMode clockMode,
				unsigned rate = 0,
				UARTOverSampling overSampling = UARTOverSampling::os16) {

				USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);
				UART_setTimming(regs, baudMode, clockMode, rate, overSampling);
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
                #ifdef USART1
                    if constexpr (channel_ == UARTChannel::channel1)
                        gpio_::initAlt(
                            GPIODriver::pushPull,
                            GPIOSpeed::fast,
                            gpio_::GPIOAlt::uart1_TX);
                #endif                        
				#ifdef USART6
					if constexpr (channel_ == UARTChannel::channel6)
						gpio_::initAlt(
							GPIODriver::pushPull,
							GPIOSpeed::fast,
							gpio_::GPIOAlt::uart6_TX);
				#endif
			}

			template <typename gpio_>
			static void initRXPin() {
                #ifdef USART1
                    if constexpr (channel_ == UARTChannel::channel1)
                        gpio_::initAlt(
                            GPIODriver::pushPull,
                            GPIOSpeed::fast,
                            gpio_::GPIOAlt::uart1_RX);
                #endif                        
				#ifdef USART6
					if constexpr (channel_ == UARTChannel::channel6)
						gpio_::initAlt(
							GPIODriver::pushPull,
							GPIOSpeed::fast,
							gpio_::GPIOAlt::uart6_RX);
				#endif
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

			static void enableInterrupt(
				UARTEvent event) {

				USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);
				UART_enableInterrupt(regs, event);
			}

			static bool disableInterrupt(
				UARTEvent event) {

				USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);
				return UART_disableInterrupt(regs, event);
			}

			static bool getInterruptFlag(
				UARTEvent event) {

				USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);
				switch (event) {
					case UARTEvent::rxFull:
						return (regs->ISR & ~USART_ISR_RXNE) != 0;

					case UARTEvent::txEmpty:
						return (regs->ISR & ~USART_ISR_TXE) != 0;

					case UARTEvent::txComplete:
						return (regs->ISR & ~USART_ISR_TC) != 0;

					case UARTEvent::parity:
						return (regs->ISR & ~USART_ISR_PE) != 0;

					case UARTEvent::overrun:
						return (regs->ISR & ~USART_ISR_ORE) != 0;

					case UARTEvent::framming:
						return (regs->ISR & USART_ISR_FE) != 0;

					case UARTEvent::noise:
						return (regs->ISR & USART_ISR_NE) != 0;

					default:
						return false;
				}
			}

			static void clearInterruptFlag(
				UARTEvent event) {

				USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);
				switch (event) {
					case UARTEvent::rxFull:
						regs->ISR &= ~USART_ISR_RXNE;
						break;

					case UARTEvent::txEmpty:
						regs->ISR &= ~USART_ISR_TXE;
						break;

					case UARTEvent::txComplete:
						regs->ISR &= ~USART_ISR_TC;
						break;

					case UARTEvent::parity:
						regs->ISR &= ~USART_ISR_PE;
						break;

					case UARTEvent::overrun:
						regs->ISR &= ~USART_ISR_ORE;
						break;

					case UARTEvent::framming:
						regs->ISR &= USART_ISR_FE;
						break;

					case UARTEvent::noise:
						regs->ISR &= USART_ISR_NE;
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
        using UART_1 = UART_x<UARTChannel::channel1>;
    #endif
    #ifdef USART2
        using UART_2 = UART_x<UARTChannel::channel2>;
    #endif
    #ifdef USART3
        using UART_3 = UART_x<UARTChannel::channel3>;
    #endif
    #ifdef UART4
        using UART_4 = UART_x<UARTChannel::channel4>;
    #endif
    #ifdef UART5
        using UART_5 = UART_x<UARTChannel::channel5>;
    #endif
    #ifdef USART6
        using UART_6 = UART_x<UARTChannel::channel6>;
    #endif
    #ifdef UART7
        using UART_7 = UART_x<UARTChannel::channel7>;
    #endif
    #ifdef UART8
        using UART_8 = UART_x<UARTChannel::channel8>;
    #endif

	#ifdef USART1
		template <>
		struct UARTTrait<UARTChannel::channel1> {
			static const uint32_t addr = USART1_BASE;
		};
	#endif
	#ifdef USART2
		template <>
		struct UARTTrait<UARTChannel::channel2> {
			static const uint32_t addr = USART2_BASE;
		};
	#endif
	#ifdef USART3
		template <>
		struct UARTTrait<UARTChannel::channel3> {
			static const uint32_t addr = USART3_BASE;
		};
	#endif
	#ifdef UART4
		template <>
		struct UARTTrait<UARTChannel::channel4> {
			static const uint32_t addr = UART4_BASE;
		};
	#endif
	#ifdef UART5
		template <>
		struct UARTTrait<UARTChannel::channel5> {
			static const uint32_t addr = UART5_BASE;
		};
	#endif
	#ifdef USART6
		template <>
		struct UARTTrait<UARTChannel::channel6> {
			static const uint32_t addr = USART6_BASE;
		};
	#endif
	#ifdef UART7
		template <>
		struct UARTTrait<UARTChannel::channel7> {
			static const uint32_t addr = UART7_BASE;
		};
	#endif
	#ifdef UART8
		template <>
		struct UARTTrait<UARTChannel::channel8> {
			static const uint32_t addr = UART8_BASE;
		};
	#endif

}


#endif // __STM32_htlUART__

