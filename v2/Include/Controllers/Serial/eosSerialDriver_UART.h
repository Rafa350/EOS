#pragma once
#ifndef __eosSerialDriver_UART__
#define __eosSerialDriver_UART__


#include "Controllers/Serial/eosSerialDriver.h"
#include "HTL/htlUART.h"


namespace eos {

	class SerialDriver_UART: public SerialDriver {
	    public:
            using DevUART = htl::uart::UARTDevice;

	    private:
            using UARTNotifyID = htl::uart::NotifyID;
	        using UARTNotifyEvent = htl::uart::NotifyEvent<SerialDriver_UART>;
	        using UARTNotifyEventArgs = htl::uart::NotifyEventArgs;

		protected:
			DevUART * const _devUART;

		private:
			UARTNotifyEvent _uartNotifyEvent;

		private:
			void uartNotifyEventHandler(UARTNotifyID, UARTNotifyEventArgs * const args);

		protected:
            void onInitialize() override;
            void onDeinitialize() override;
            void onTransmit(const uint8_t *buffer, unsigned length) override;
            void onReceive(uint8_t *buffer, unsigned bufferSize) override;

		public:
			SerialDriver_UART(DevUART *devUART);
	};
}


#endif // __eosSerialDriver_UART__
