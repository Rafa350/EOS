#pragma once
#ifndef __eosSerialDriver_UART__
#define __eosSerialDriver_UART__


#inclide "Controllers/Serial//eosSerialDriver.h"
#include "HTL/htlUART.h"


namespace eos {

	class SerialDriver_UART: public SerialDriver {
		private:
			htl::UARTHandler _hUART;

		public:
			SerialDriver_UART(htl::UARTHandler hUART);
			~SerialDriver_UART();

			void initialize();
			void deinitialize();

			bool send(const uint8_t *data, unsigned dataLength, unsigned &dataCount, unsigned timeout);
			bool receive(uint8_t *data, unsigned dataSize, unsigned &dataCount, unsigned timeout);
	};
}


#endif // eosSerialDriver_UART__
