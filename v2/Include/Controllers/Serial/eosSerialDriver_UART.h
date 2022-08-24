#pragma once
#ifndef __eosSerialDriver__
#define __eosSerialDriver__


#include "HTL/htlUART.h"


namespace eos {

	class SerialDriver {
		private:
			htl::UARTAdapter &_uart;

		public:
			SerialDriver(htl::UARTAdapter &uart);
			~SerialDriver();

			void initialize();
			void deinitialize();

			bool send(const uint8_t *data, unsigned dataLength, unsigned &dataCount, unsigned timeout);
			bool receive(uint8_t *data, unsigned dataSize, unsigned &dataCount, unsigned timeout);
	};
}


#endif // eosSerialDriver__
