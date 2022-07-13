#ifndef __PIC32_htlUART__
#define __PIC32_htlUART__


// EOS includes
//
#include "eos.h"
#include "HAL/PIC32/halUART.h"
#include "HTL/PIC32/htlGPIO.h"


namespace eos {

	enum class UARTChannel {
        #ifdef _UART1
            channel1 = HAL_UART_CHANNEL_1,
        #endif
        #ifdef _UART2
            channel2 = HAL_UART_CHANNEL_2,
        #endif
        #ifdef _UART3
            channel3 = HAL_UART_CHANNEL_3,
        #endif
        #ifdef _UART4
            channel4 = HAL_UART_CHANNEL_4,
        #endif
        #ifdef _UART5
            channel5 = HAL_UART_CHANNEL_5,
        #endif
        #ifdef _UART6
            channel6 = HAL_UART_CHANNEL_6,
        #endif
        #ifdef _UART7
            channel7 = HAL_UART_CHANNEL_7,
        #endif
        #ifdef _UART8
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
            UART_x(const UART_X &) = delete;
            UART_x(const UART_X &&) = delete;
            ~UART_x() = delete;

		public:
			inline static void init(const halUARTSettings& settings) {
				_handler = halUARTInitialize(&_data, &settings);
			}

			inline static void deInit() {
				halUARTDeinitialize(_handler);
			}

			template <typename gpio_>
			inline static void setTXPin() {
				if constexpr (channel_ == UARTChannel::channel1)
					gpio_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						gpio_::GPIOAlt::uart1_TX);
			}

			template <typename gpio_>
			inline static void setRXPin(GPIOPinAdapter<port_, pin_> pinAdapter) {
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


    #ifdef _UART1
        using UART_1 = UARTAdapter<UARTChannel::channel1>;
    #endif
    #ifdef _UART2
        using UART_2 = UARTAdapter<UARTChannel::channel2>;
    #endif
    #ifdef _UART3
        using UART_3 = UARTAdapter<UARTChannel::channel3>;
    #endif
    #ifdef _UART4
        using UART_4 = UARTAdapter<UARTChannel::channel4>;
    #endif
    #ifdef _UART5
        using UART_5 = UARTAdapter<UARTChannel::channel5>;
    #endif
    #ifdef _UART6
        using UART_6 = UARTAdapter<UARTChannel::channel6>;
    #endif
    #ifdef _UART7
        using UART_7 = UARTAdapter<UARTChannel::channel7>;
    #endif
    #ifdef _UART8
        using UART_8 = UARTAdapter<UARTChannel::channel8>;
    #endif

}


#endif // __PIC32_halUARTTpl__

