#pragma once
#ifndef __eosAsyncSerialDriver_UART__
#define __eosAsyncSerialDriver_UART__


#include "Controllers/Serial/eosAsyncSerialDriver.h"
#include "HTL/htlUART.h"


namespace eos {

	class AsyncSerialDriver_UART: public AsyncSerialDriver {
		private:
			htl::uart::UARTDeviceHandler _uart;
			const uint8_t *_txData;
			int _txLength;
			int _txCount;
			uint8_t *_rxData;
			int _rxSize;
			int _rxCount;

			void initializeImpl() override;
			void deinitializeImpl() override;
			bool transmitImpl(const uint8_t *data, int dataLength) override;
			bool receiveImpl(uint8_t *data, int dataSize) override;

			void interruptHandler();
			static void interruptFunction(htl::uart::UARTInterruptParam param);

		public:
			AsyncSerialDriver_UART(htl::uart::UARTDeviceHandler hUART);
	};
}


#endif // eosAsyncSerialDriver_UART__
