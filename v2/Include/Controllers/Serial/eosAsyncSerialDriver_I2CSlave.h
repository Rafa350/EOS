#pragma once
#ifndef __eosAsyncSerialDriver_I2C__
#define __eosAsyncSerialDriver_I2C__


#include "Controllers/Serial/eosAsyncSerialDriver.h"
#include "HTL/htlI2C.h"


namespace eos {

	class AsyncSerialDriver_I2CSlave final: public AsyncSerialDriver {
		public:
			using AddressMatchCallback = htl::i2c::AddressMatchCallback<AsyncSerialDriver_I2CSlave>;
			using RxDataCallback = htl::i2c::RxDataCallback<AsyncSerialDriver_I2CSlave>;
			using RxCompletedCallback = htl::i2c::RxCompletedCallback<AsyncSerialDriver_I2CSlave>;

		private:
			htl::i2c::I2CSlaveDeviceHandler _i2c;
			const uint8_t *_txData;
			int _txLength;
			int _txCount;
			AddressMatchCallback _addressMatchCallback;
			RxDataCallback _rxDataCallback;
			RxCompletedCallback _rxCompletedCallback;

		private:
			void addressMatchHandler(uint16_t addr);
			void rxDataHandler(const uint8_t *buffer, uint16_t count);
			void rxCompletedHandler(const uint8_t *buffer, uint16_t count);

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
