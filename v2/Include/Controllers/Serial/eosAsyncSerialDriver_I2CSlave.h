#pragma once
#ifndef __eosAsyncSerialDriver_I2C__
#define __eosAsyncSerialDriver_I2C__


#include "Controllers/Serial/eosAsyncSerialDriver.h"
#include "HTL/htlI2C.h"


namespace eos {

	class AsyncSerialDriver_I2CSlave final: public AsyncSerialDriver {
		public:
			using AddressMatchEvent = htl::i2c::AddressMatchEvent<AsyncSerialDriver_I2CSlave>;
			using RxDataEvent = htl::i2c::RxDataEvent<AsyncSerialDriver_I2CSlave>;
			using RxCompletedEvent = htl::i2c::RxCompletedEvent<AsyncSerialDriver_I2CSlave>;

		private:
			htl::i2c::I2CSlaveDeviceHandler _i2c;
			const uint8_t *_txData;
			int _txLength;
			int _txCount;
			AddressMatchEvent _addressMatchEvent;
			RxDataEvent _rxDataEvent;
			RxCompletedEvent _rxCompletedEvent;

		private:
			void addressMatchEventHandler(htl::i2c::I2CSlaveDevice &sender, uint16_t addr);
			void rxDataEventHandler(htl::i2c::I2CSlaveDevice &sender, const uint8_t *buffer, uint16_t count);
			void rxCompletedEventHandler(htl::i2c::I2CSlaveDevice &sender, const uint8_t *buffer, uint16_t count);

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
