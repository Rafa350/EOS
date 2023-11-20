#pragma once


#include "Controllers/Serial/eosAsyncSerialDriver.h"
#include "HTL/htlI2C.h"


namespace eos {

	class AsyncSerialDriver_I2CSlave final: public AsyncSerialDriver {
		public:
	        using DevI2C = htl::i2c::I2CSlaveDevice;

		private:
			using I2CNotifyEvent = htl::i2c::SlaveNotifyEvent<AsyncSerialDriver_I2CSlave>;
			using I2CNotifyEventArgs = htl::i2c::NotifyEventArgs;

		private:
			DevI2C *_devI2C;
			I2CNotifyEvent _i2cNotifyEvent;
			const uint8_t *_txData;
			int _txLength;
			int _txCount;

		private:
			void initializeImpl() override;
			void deinitializeImpl() override;

			bool transmitImpl(const uint8_t *data, int dataLength) override;
			bool receiveImpl(uint8_t *data, int dataSize) override;

            void i2cNotifyEventHandler(DevI2C *sender, I2CNotifyEventArgs &args);

		public:
			AsyncSerialDriver_I2CSlave(DevI2C *devI2C);
	};
}
