#ifndef __STM32_halUARTTpl__
#define __STM32_halUARTTpl__


// EOS includes
//
#include "HAL/hal.h"
#include "HAL/STM32/halUART.h"
#include "HAL/STM32/halGPIOTpl.h"


namespace eos {

	enum class UARTChannel {
		channel1 = HAL_UART_CHANNEL_1,
		channel2 = HAL_UART_CHANNEL_2,
		channel3 = HAL_UART_CHANNEL_3,
		channel4 = HAL_UART_CHANNEL_4,
		channel5 = HAL_UART_CHANNEL_5,
		channel6 = HAL_UART_CHANNEL_6,
		channel7 = HAL_UART_CHANNEL_7,
		channel8 = HAL_UART_CHANNEL_8,
	};

	template <UARTChannel channel_>
	class UARTAdapter {
		private:
			halUARTData _data;
			halUARTHandler _handler;

		public:
			constexpr static const UARTChannel channel = channel_;

		public:
			inline void initialize(const halUARTSettings& settings) {
				_handler = halUARTInitialize(&_data, &settings);
			}

			inline void deinitialize() {
				halUARTDeinitialize(_handler);
			}

			template <GPIOPort port_, GPIOPin pin_>
			inline static void setTXPin(GPIOPinAdapter<port_, pin_> pinAdapter) {
				if constexpr (channel_ == UARTChannel::channel1)
					pinAdapter.initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						GPIOPinAdapter<port_, pin_>::GPIOAlt::uart1_TX);
			}

			template <GPIOPort port_, GPIOPin pin_>
			inline static void setRXPin(GPIOPinAdapter<port_, pin_> pinAdapter) {
				if constexpr (channel_ == UARTChannel::channel1)
					pinAdapter.initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						GPIOPinAdapter<port_, pin_>::GPIOAlt::uart1_RX);
			}

			inline void send(uint8_t data) const {
				halUARTSend(_handler, data);
			}

			inline halUARTHandler getHandler() const {
				return _handler;
			}

			inline operator halUARTHandler () const {
				return _handler;
			}
	};

	class UARTAttachedAdapter {
		private:
			halUARTHandler _handler;

		public:
			UARTAttachedAdapter(halUARTHandler handler) {
				_handler = handler;
			}

			inline void send(uint8_t data) const {
				halUARTSend(_handler, data);
			}

			inline uint8_t receive() const {
				return halUARTReceive(_handler);
			}

			inline void enableInterrupts(uint32_t events) const {
				halUARTEnableInterrupts(_handler, events);
			}

			inline uint32_t disableInterrupts(uint32_t events) const {
				return halUARTDisableInterrupts(_handler, events);
			}

			inline void clearInterruptFlags(uint32_t events) const {
				halUARTClearInterruptFlags(_handler, events);
			}

			inline operator halUARTHandler () const {
				return _handler;
			}
	};

	typedef UARTAttachedAdapter UART;
	typedef UARTAdapter<UARTChannel::channel1> UART_1;
	typedef UARTAdapter<UARTChannel::channel2> UART_2;
	typedef UARTAdapter<UARTChannel::channel3> UART_3;
	typedef UARTAdapter<UARTChannel::channel4> UART_4;
	typedef UARTAdapter<UARTChannel::channel5> UART_5;
	typedef UARTAdapter<UARTChannel::channel6> UART_6;
	typedef UARTAdapter<UARTChannel::channel7> UART_7;
	typedef UARTAdapter<UARTChannel::channel8> UART_8;

}


#endif // __STM32_halUARTTpl__

