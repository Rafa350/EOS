#pragma once
#ifndef __eosAsyncSerialDriver_I2C__
#define __eosAsyncSerialDriver_I2C__


#include "Controllers/Serial/eosAsyncSerialDriver.h"
#include "HTL/htlI2C.h"


namespace eos {

	class AsyncSerialDriver_I2CSlave final: public AsyncSerialDriver {
		public:
			using I2CNotifyEvent = htl::i2c::SlaveNotifyEvent<AsyncSerialDriver_I2CSlave>;

		private:
			htl::i2c::I2CSlaveDevice *_devI2C;
			I2CNotifyEvent _i2cNotifyEvent;
			const uint8_t *_txData;
			int _txLength;
			int _txCount;

		private:
			void i2cNotifyEventHandler(htl::i2c::I2CSlaveDevice *sender, htl::i2c::NotifyEventArgs &args);

		protected:
			void initializeImpl() override;
			void deinitializeImpl() override;
			bool transmitImpl(const uint8_t *data, int dataLength) override;
			bool receiveImpl(uint8_t *data, int dataSize) override;

		public:
			AsyncSerialDriver_I2CSlave(htl::i2c::I2CSlaveDevice *devI2C);
	};
}


#endif // __eosAsyncSerialDriver_I2C__
