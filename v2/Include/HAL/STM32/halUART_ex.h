#ifndef __STM32_halUARTTpl__
#define __STM32_halUARTTpl__


// EOS includes
//
#include "HAL/hal.h"
#include "HAL/STM32/halUART.h"
#include "HAL/STM32/halGPIO_ex.h"


namespace eos {

	enum class UARTChannel {
#ifdef HAL_UART_CHANNEL_1
		channel1 = HAL_UART_CHANNEL_1,
#endif
#ifdef HAL_UART_CHANNEL_2
		channel2 = HAL_UART_CHANNEL_2,
#endif
#ifdef HAL_UART_CHANNEL_3
		channel3 = HAL_UART_CHANNEL_3,
#endif
#ifdef HAL_UART_CHANNEL_4
		channel4 = HAL_UART_CHANNEL_4,
#endif
#ifdef HAL_UART_CHANNEL_5
		channel5 = HAL_UART_CHANNEL_5,
#endif
#ifdef HAL_UART_CHANNEL_6
		channel6 = HAL_UART_CHANNEL_6,
#endif
#ifdef HAL_UART_CHANNEL_7
		channel7 = HAL_UART_CHANNEL_7,
#endif
#ifdef HAL_UART_CHANNEL_8
		channel8 = HAL_UART_CHANNEL_8,
#endif
	};

	template <UARTChannel channel_>
	class UARTModule {
		private:
			halUARTData _data;
			halUARTHandler _handler;

		public:
			constexpr static const UARTChannel channel = channel_;

		private:
			UARTModule() = default;
			UARTModule(const UARTModule &) = delete;
			UARTModule(const UARTModule &&) = delete;
			UARTModule & operator = (const UARTModule &) = delete;
			UARTModule & operator = (const UARTModule &&) = delete;

		public:
			inline static auto & instance() {
				static UARTModule module;
				return module;
			}

			inline void initialize(const halUARTSettings &settings) {
				_handler = halUARTInitialize(&_data, &settings);
			}

			inline void deinitialize() {
				halUARTDeinitialize(_handler);
			}

			template <typename pinAdapter_>
			inline static void initTXPin() {
				if constexpr (channel_ == UARTChannel::channel1)
					pinAdapter_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						pinAdapter_::GPIOAlt::uart1_TX);
			}

			template <typename pinAdapter_>
			inline static void initRXPin() {
				if constexpr (channel_ == UARTChannel::channel1)
					pinAdapter_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						pinAdapter_::GPIOAlt::uart1_RX);
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
#ifdef HAL_UART_CHANNEL_1
	typedef UARTModule<UARTChannel::channel1> UART_1;
#endif
#ifdef HAL_UART_CHANNEL_2
	typedef UARTModule<UARTChannel::channel2> UART_2;
#endif
#ifdef HAL_UART_CHANNEL_3
	typedef UARTModule<UARTChannel::channel3> UART_3;
#endif
#ifdef HAL_UART_CHANNEL_4
	typedef UARTModule<UARTChannel::channel4> UART_4;
#endif
#ifdef HAL_UART_CHANNEL_5
	typedef UARTModule<UARTChannel::channel5> UART_5;
#endif
#ifdef HAL_UART_CHANNEL_6
	typedef UARTModule<UARTChannel::channel6> UART_6;
#endif
#ifdef HAL_UART_CHANNEL_7
	typedef UARTModule<UARTChannel::channel7> UART_7;
#endif
#ifdef HAL_UART_CHANNEL_8
	typedef UARTModule<UARTChannel::channel8> UART_8;
#endif

}


#endif // __STM32_halUARTTpl__

