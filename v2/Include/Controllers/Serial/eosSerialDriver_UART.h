#pragma once
#ifndef __eosSerialDriver_UART__
#define __eosSerialDriver_UART__


#include "Controllers/Serial/eosSerialDriver.h"
#include "HTL/htlUART.h"


namespace eos {

	class SerialDriver_UART: public SerialDriver {
		protected:
			htl::uart::UARTDevice * const _devUART;

		private:
			htl::uart::NotifyEvent<SerialDriver_UART> _uartNotifyEvent;

		private:
			void uartNotifyEventHandler(htl::uart::UARTDevice*, htl::uart::NotifyEventArgs * const args);

		protected:
            bool onInitialize() override;
            bool onDeinitialize() override;
            bool onTransmit(const uint8_t *buffer, unsigned length) override;
            bool onReceive(uint8_t *buffer, unsigned bufferSize) override;
            bool onAbort() override;

		public:
			SerialDriver_UART(htl::uart::UARTDevice *devUART);
	};
}


#endif // __eosSerialDriver_UART__
