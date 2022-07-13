#ifndef __STM32_htlUART__
#define __STM32_htlUART__


// EOS includes
//
#include "eos.h"
#include "HAL/STM32/halUART.h"
#include "HTL/STM32/htlGPIO.h"


namespace eos {

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

	template <UARTChannel channel_>
	class UART_x {
		private:
			static halUARTData _data;
			static halUARTHandler _handler;

		public:
			constexpr static const UARTChannel channel = channel_;

		private:
			UART_x() = delete;
			UART_x(const UART_x &) = delete;
			UART_x(const UART_x &&) = delete;
			UART_x & operator = (const UART_x &) = delete;
			UART_x & operator = (const UART_x &&) = delete;

		public:
			inline static void init(const halUARTSettings &settings) {
				_handler = halUARTInitialize(&_data, &settings);
			}

			inline static void deInit() {
				halUARTDeinitialize(_handler);
			}

			template <typename gpio_>
			inline static void initTXPin() {
				if constexpr (channel_ == UARTChannel::channel1)
					gpio_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						gpio_::GPIOAlt::uart1_TX);
			}

			template <typename gpio_>
			inline static void initRXPin() {
				if constexpr (channel_ == UARTChannel::channel1)
					gpio_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						gpio_::GPIOAlt::uart1_RX);
			}

			inline static void send(uint8_t data) const {
				halUARTSend(_handler, data);
			}

			inline static halUARTHandler getHandler() const {
				return _handler;
			}
	};
    
    template <typename UARTChannel> halUARTData UART_x::_data;
    template <typename UARTChannel> halUARTHandler UART_x::_handler;


    #ifdef HAL_UART_CHANNEL_1
        using UART_1 = UART_x<UARTChannel::channel1>;
    #endif
    #ifdef HAL_UART_CHANNEL_2
        using UART_2 = UART_x<UARTChannel::channel2>;
    #endif
    #ifdef HAL_UART_CHANNEL_3
        using UART_3 = UART_x<UARTChannel::channel3>;
    #endif
    #ifdef HAL_UART_CHANNEL_4
        using UART_4 = UART_x<UARTChannel::channel4>;
    #endif
    #ifdef HAL_UART_CHANNEL_5
        using UART_5 = UART_x<UARTChannel::channel5>;
    #endif
    #ifdef HAL_UART_CHANNEL_6
        using UART_6 = UART_x<UARTChannel::channel6>;
    #endif
    #ifdef HAL_UART_CHANNEL_7
        using UART_7 = UART_x<UARTChannel::channel7>;
    #endif
    #ifdef HAL_UART_CHANNEL_8
        using UART_8 = UART_x<UARTChannel::channel8>;
    #endif

}


#endif // __STM32_htlUART__

