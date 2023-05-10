#pragma once
#ifndef __eosAsyncSerialDriver_UART__
#define __eosAsyncSerialDriver_UART__


#include "Controllers/Serial/eosAsyncSerialDriver.h"
#include "HTL/htlUART.h"


namespace eos {

	class AsyncSerialDriver_UART final: public AsyncSerialDriver {
		private:
			using TxCompletedCallback = htl::uart::TxCompletedCallback<AsyncSerialDriver_UART>;
			using RxCompletedCallback = htl::uart::RxCompletedCallback<AsyncSerialDriver_UART>;
		private:
			htl::uart::UARTDeviceHandler _uart;
			TxCompletedCallback _txCompletedCallback;
			RxCompletedCallback _rxCompletedCallback;
		private:
			void initializeImpl() override;
			void deinitializeImpl() override;
			bool transmitImpl(const uint8_t *data, int dataLength) override;
			bool receiveImpl(uint8_t *data, int dataSize) override;
			void txCompletedHandler(const uint8_t *buffer, uint16_t count);
			void rxCompletedHandler(const uint8_t *buffer, uint16_t count);

		public:
			AsyncSerialDriver_UART(htl::uart::UARTDeviceHandler hUART);
	};
}


#endif // eosAsyncSerialDriver_UART__
