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
			htl::uart::UARTDevice::NotificationEvent<SerialDriver_UART> _devUART_notificationEvent;

		private:
			void devUART_notificationEventHandler(htl::uart::UARTDevice *sender, htl::uart::UARTDevice::NotificationEventArgs *args);

		protected:
            bool onInitialize() override;
            bool onDeinitialize() override;
            bool onTransmit(const uint8_t *buffer, uint32_t length) override;
            bool onReceive(uint8_t *buffer, uint32_t bufferSize) override;
            bool onAbort() override;

		public:
			SerialDriver_UART(htl::uart::UARTDevice *devUART);
	};
}


#endif // __eosSerialDriver_UART__
