#pragma once
#ifndef __eosAsyncSerialDriver_UART__
#define __eosAsyncSerialDriver_UART__


#include "Controllers/Serial/eosAsyncSerialDriver.h"
#include "HTL/htlUART.h"


namespace eos {

	class AsyncSerialDriver_UART final: public AsyncSerialDriver {
		private:
			htl::uart::UARTDeviceHandler _uart;
			htl::uart::NotifyEvent<AsyncSerialDriver_UART> _uartNotifyEvent;
		private:
			void initializeImpl() override;
			void deinitializeImpl() override;
			bool transmitImpl(const uint8_t *data, int dataLength) override;
			bool receiveImpl(uint8_t *data, int dataSize) override;
			void uartNotifyEventHandler(htl::uart::UARTDevice *sender, htl::uart::NotifyEventArgs &args);

		public:
			AsyncSerialDriver_UART(htl::uart::UARTDeviceHandler hUART);
	};
}


#endif // eosAsyncSerialDriver_UART__
