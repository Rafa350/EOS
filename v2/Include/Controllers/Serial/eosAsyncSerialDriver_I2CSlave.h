#pragma once
#ifndef __eosAsyncSerialDriver_I2C__
#define __eosAsyncSerialDriver_I2C__


#include "Controllers/Serial/eosAsyncSerialDriver.h"
#include "HTL/htlI2C.h"


namespace eos {

	class AsyncSerialDriver_I2CSlave final: public AsyncSerialDriver {
		private:
			htl::i2c::I2CSlaveDeviceHandler _i2c;
			const uint8_t *_txData;
			int _txLength;
			int _txCount;
			uint8_t *_rxData;
			int _rxSize;
			int _rxCount;

		private:
			static void rxInterruptFunction(htl::i2c::I2CInterruptContext *context);
			static void txInterruptFunction(htl::i2c::I2CInterruptContext *context);

		protected:
			void initializeImpl() override;
			void deinitializeImpl() override;
			bool transmitImpl(const uint8_t *data, int dataLength) override;
			bool receiveImpl(uint8_t *data, int dataSize) override;

		public:
			AsyncSerialDriver_I2CSlave(htl::i2c::I2CSlaveDeviceHandler i2c);
	};
}


#endif // __eosAsyncSerialDriver_I2C__
