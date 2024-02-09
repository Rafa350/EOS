#pragma once
#ifndef __eosAsyncSerialDriver_UART__
#define __eosAsyncSerialDriver_UART__


#include "Controllers/Serial/eosAsyncSerialDriver.h"
#include "HTL/htlUART.h"


namespace eos {

	class AsyncSerialDriver_UART: public AsyncSerialDriver {
	    public:
            using DevUART = htl::uart::UARTDevice;

	    private:
	        using UARTNotifyEvent = htl::uart::NotifyEvent<AsyncSerialDriver_UART>;
	        using UARTNotifyEventArgs = htl::uart::NotifyEventArgs;

		protected:
			DevUART * const _devUART;

		private:
			UARTNotifyEvent _uartNotifyEvent;

		private:
			void initializeImpl() override;
			void deinitializeImpl() override;

			void uartNotifyEventHandler(const DevUART *sender, const UARTNotifyEventArgs &args);

		protected:
            bool transmitImpl(const uint8_t *data, int dataLength) override;
            bool receiveImpl(uint8_t *data, int dataSize) override;

		public:
			AsyncSerialDriver_UART(DevUART *devUART);
	};
}


#endif // __eosAsyncSerialDriver_UART__
