#pragma once
#ifndef __eosSerialDriver_I2C__
#define __eosSerialDriver_I2C__


#include "Controllers/Serial/eosSerialDriver.h"
#include "HTL/htlSPI.h"


namespace eos {

	class SerialDriver_I2C: public SerialDriver {
		private:
			htl::I2CHandler _hI2C;

		public:
			SerialDriver_I2C(htl::I2CHandler hI2C);
			~SerialDriver_I2C();

			void initialize();
			void deinitialize();

			bool send(const uint8_t *data, unsigned dataLength, unsigned &dataCount, unsigned timeout);
			bool receive(uint8_t *data, unsigned dataSize, unsigned &dataCount, unsigned timeout);
	};
}


#endif // eosSerialDriver_I2C__
