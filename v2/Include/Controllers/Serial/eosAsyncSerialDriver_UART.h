#pragma once
#ifndef __eosAsyncSerialDriver_UART__
#define __eosAsyncSerialDriver_UART__


#include "Controllers/Serial/eosAsyncSerialDriver.h"
#include "HTL/htlUART.h"


namespace eos {

	class AsyncSerialDriver_UART: public AsyncSerialDriver {
		private:
			htl::UARTHandler _hUART;
			const uint8_t *_txData;
			unsigned _txLength;
			unsigned _txCount;
			uint8_t *_rxData;
			unsigned _rxSize;
			unsigned _rxCount;

			void initializeImpl() override;
			void deinitializeImpl() override;
			bool transmitImpl(const uint8_t *data, unsigned dataLength) override;
			bool receiveImpl(uint8_t *data, unsigned dataSize) override;

			void interruptHandler();
			static void interruptHandler(htl::UARTInterruptParam param);

		public:
			AsyncSerialDriver_UART(htl::UARTHandler hUART);
	};
}


#endif // eosAsyncSerialDriver_UART__
