#pragma once
#ifndef __eosAsyncSerialDriver_UART__
#define __eosAsyncSerialDriver_UART__


#include "Controllers/Serial/eosAsyncSerialDriver.h"
#include "HTL/htlUART.h"


namespace eos {

	class AsyncSerialDriver_UART: public AsyncSerialDriver {
		private:
			htl::UARTAdapter &_uart;
			const uint8_t *_txData;
			unsigned _txLength;
			unsigned _txCount;
			uint8_t *_rxData;
			unsigned _rxSize;
			unsigned _rxCount;

			void interruptHandler(htl::UARTEvent event);
			static void interruptHandler(htl::UARTEvent event, htl::UARTInterruptParam param);

		public:
			AsyncSerialDriver_UART(htl::UARTAdapter &uart);

			void initialize() override;
			void deinitialize() override;

			bool transmit(const uint8_t *data, unsigned dataLength) override;
			bool receive(uint8_t *data, unsigned dataSize) override;
	};
}


#endif // eosAsyncSerialDriver_UART__
