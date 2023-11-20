#pragma once


#include "Controllers/Serial/eosAsyncSerialDriver.h"
#include "HTL/htlUART.h"


namespace eos {

	class AsyncSerialDriver_UART final: public AsyncSerialDriver {
	    public:
            using DevUART = htl::uart::UARTDevice;

	    private:
	        using UARTNotifyEvent = htl::uart::NotifyEvent<AsyncSerialDriver_UART>;
	        using UARTNotifyEventArgs = htl::uart::NotifyEventArgs;

		private:
			DevUART *_devUART;
			UARTNotifyEvent _uartNotifyEvent;

		private:
			void initializeImpl() override;
			void deinitializeImpl() override;

			bool transmitImpl(const uint8_t *data, int dataLength) override;
			bool receiveImpl(uint8_t *data, int dataSize) override;

			void uartNotifyEventHandler(const DevUART *sender, const UARTNotifyEventArgs &args);

		public:
			AsyncSerialDriver_UART(DevUART *devUART);
	};
}
