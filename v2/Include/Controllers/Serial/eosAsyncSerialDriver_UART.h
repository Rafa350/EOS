#pragma once
#ifndef __eosAsyncSerialDriver_UART__
#define __eosAsyncSerialDriver_UART__


#include "Controllers/Serial/eosAsyncSerialDriver.h"
#include "HTL/htlUART.h"


namespace eos {

	class AsyncSerialDriver_UART final: public AsyncSerialDriver {
		private:
			using TxCompletedEvent = htl::uart::TxCompletedCallback<AsyncSerialDriver_UART>;
			using RxCompletedEvent = htl::uart::RxCompletedCallback<AsyncSerialDriver_UART>;
		private:
			htl::uart::UARTDeviceHandler _uart;
			TxCompletedEvent _txCompletedEvent;
			RxCompletedEvent _rxCompletedEvent;
		private:
			void initializeImpl() override;
			void deinitializeImpl() override;
			bool transmitImpl(const uint8_t *data, int dataLength) override;
			bool receiveImpl(uint8_t *data, int dataSize) override;
			void txCompletedEventHandler(const uint8_t *buffer, uint16_t count);
			void rxCompletedEventHandler(const uint8_t *buffer, uint16_t count);

		public:
			AsyncSerialDriver_UART(htl::uart::UARTDeviceHandler hUART);
	};
}


#endif // eosAsyncSerialDriver_UART__
