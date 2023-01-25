#pragma once
#ifndef __eosSerialDriver_SPI__
#define __eosSerialDriver_SPI__


#include "HTL/htlSPI.h"


namespace eos {

	class SerialDriver_SPI {
		private:
			htl::SPIHandler _hSPI;

		public:
			SerialDriver_SPI(htl::SPIHandler hSPI);
			~SerialDriver_SPI();

			void initialize();
			void deinitialize();

			bool send(const uint8_t *data, unsigned dataLength, unsigned &dataCount, unsigned timeout);
			bool receive(uint8_t *data, unsigned dataSize, unsigned &dataCount, unsigned timeout);
	};
}


#endif // eosSerialDriver_SPI__
