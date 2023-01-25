#pragma once
#ifndef __eosSerialDriver_UART__
#define __eosSerialDriver_UART__


#include "HTL/htlUART.h"


namespace eos {

	class SerialDriver_UART {
		private:
			htl::UARTHandler _hUart;

		public:
			SerialDriver_UART(htl::UARTHandler hUart);
			~SerialDriver_UART();

			void initialize();
			void deinitialize();

			bool send(const uint8_t *data, unsigned dataLength, unsigned &dataCount, unsigned timeout);
			bool receive(uint8_t *data, unsigned dataSize, unsigned &dataCount, unsigned timeout);
	};
}


#endif // eosSerialDriver_UART__
