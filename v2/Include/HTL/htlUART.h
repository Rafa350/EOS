#pragma once
#ifndef __htlUART__
#define	__htlUART__


// EOS includes
//
#include "HTL/htl.h"


#if defined(EOS_PLATFORM_PIC32MX) || defined(EOS_PLATFORM_PIC32MZ)
	#include "HTL/PIC32/htlUART.h"

#elif defined(EOS_PLATFORM_STM32F0) || defined(EOS_PLATFORM_STM32F1) || \
	defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
	#include "HTL/STM32/htlUART.h"

#elif defined(EOS_PLATFORM_MSP432)
    #include "HTL/MSP432/htlUART.h"

#endif


namespace htl {

	class IUART {
		protected:
			virtual ~IUART() = default;

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

	typedef IUART *UARTHandler;

	template <typename uart_>
	class UART final: public IUART {
		private:
			UART() = default;
			UART(const UART &) = delete;
			UART(const UART &&) = delete;

			UART & operator = (const UART &) = delete;
			UART & operator = (const UART &&) = delete;

		public:
			static UARTHandler instance() {
				static UART uart;
				return &uart;
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
	UARTHandler getUART() {
		return UART<uart_>::instance();
	}

}


#endif // __htlUART__

