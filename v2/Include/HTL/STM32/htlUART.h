#pragma once
#ifndef __STM32_htlUART__
#define __STM32_htlUART__


// EOS includes
//
#include "eos.h"
#include "HAL/STM32/halUART.h"
#include "HTL/STM32/htlGPIO.h"


namespace htl {

	enum class UARTChannel {
        #ifdef USART1
            channel1 = HAL_UART_CHANNEL_1,
        #endif
        #ifdef USART2
            channel2 = HAL_UART_CHANNEL_2,
        #endif
        #ifdef USART3
            channel3 = HAL_UART_CHANNEL_3,
        #endif
        #ifdef UART4
            channel4 = HAL_UART_CHANNEL_4,
        #endif
        #ifdef UART5
            channel5 = HAL_UART_CHANNEL_5,
        #endif
        #ifdef USART6
            channel6 = HAL_UART_CHANNEL_6,
        #endif
        #ifdef UART7
            channel7 = HAL_UART_CHANNEL_7,
        #endif
        #ifdef UART8
            channel8 = HAL_UART_CHANNEL_8,
        #endif
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

	template <UARTChannel>
	struct UARTTrait {
	};

	template <UARTChannel channel_>
	class UART_x {
		private:
			using Trait = UARTTrait<channel_>;
			static halUARTData _data;
			static halUARTHandler _handler;

		public:
			constexpr static const UARTChannel channel = channel_;

		private:
			constexpr static const uint32_t _addr = Trait::addr;
			static UARTInterruptFunction _isrFunction;
			static UARTInterruptParam _isrParam;

		private:
			UART_x() = delete;
			UART_x(const UART_x &) = delete;
			UART_x(const UART_x &&) = delete;
			UART_x & operator = (const UART_x &) = delete;
			UART_x & operator = (const UART_x &&) = delete;

		public:
			static void init(const halUARTSettings &settings) {
				_handler = halUARTInitialize(&_data, &settings);
			}

			static void deInit() {
				halUARTDeinitialize(_handler);
			}

			template <typename gpio_>
			static void initTXPin() {
                #ifdef USART1
                    if constexpr (channel_ == UARTChannel::channel1)
                        gpio_::initAlt(
                            GPIOSpeed::fast,
                            GPIODriver::pushPull,
                            gpio_::GPIOAlt::uart1_TX);
                #endif                        
				#ifdef USART6
					if constexpr (channel_ == UARTChannel::channel6)
						gpio_::initAlt(
							GPIOSpeed::fast,
							GPIODriver::pushPull,
							gpio_::GPIOAlt::uart6_TX);
				#endif
			}

			template <typename gpio_>
			static void initRXPin() {
                #ifdef USART1
                    if constexpr (channel_ == UARTChannel::channel1)
                        gpio_::initAlt(
                            GPIOSpeed::fast,
                            GPIODriver::pushPull,
                            gpio_::GPIOAlt::uart1_RX);
                #endif                        
				#ifdef USART6
					if constexpr (channel_ == UARTChannel::channel6)
						gpio_::initAlt(
							GPIOSpeed::fast,
							GPIODriver::pushPull,
							gpio_::GPIOAlt::uart6_RX);
				#endif
			}

			static void send(
				uint8_t data) {
			}

			static void enableInterrupt(
				UARTEvent event) {

				USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);

			}

			static void disableInterrupt(
				UARTEvent event) {

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
				}
			}

			static void clearInterruptFlag(
				UARTEvent event) {

			}

			static void setInterruptFunction(
				UARTInterruptFunction function,
				UARTInterruptParam param) {

				_isrFunction = function;
				_isrParam = param;
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

    template <>
    struct UARTTrait<UARTChannel::channel1> {
    	static const uint32_t addr = USART1_BASE;
    };
    template <>
    struct UARTTrait<UARTChannel::channel2> {
    	static const uint32_t addr = USART2_BASE;
    };
    template <>
    struct UARTTrait<UARTChannel::channel3> {
    	static const uint32_t addr = USART3_BASE;
    };
    template <>
    struct UARTTrait<UARTChannel::channel4> {
    	static const uint32_t addr = UART4_BASE;
    };
    template <>
    struct UARTTrait<UARTChannel::channel5> {
    	static const uint32_t addr = UART5_BASE;
    };
    template <>
    struct UARTTrait<UARTChannel::channel6> {
    	static const uint32_t addr = USART6_BASE;
    };
    template <>
    struct UARTTrait<UARTChannel::channel7> {
    	static const uint32_t addr = UART7_BASE;
    };
    template <>
    struct UARTTrait<UARTChannel::channel8> {
    	static const uint32_t addr = UART8_BASE;
    };

}


#endif // __STM32_htlUART__

