#pragma once
#ifndef __eosCircularSerialDriver_I2CSlave__
#define __eosCircularSerialDriver_I2CSlave__


#include "Controllers/Serial/eosCircularSerialDriver.h"
#include "HTL/htlI2C.h"


namespace eos {

	class CircularSerialDriver_I2CSlave final : public CircularSerialDriver {
		public:
			using I2CNotifyEvent = htl::i2c::SlaveNotifyEvent<CircularSerialDriver_I2CSlave>;

		private:
			htl::i2c::I2CSlaveDevice *_dev;
			uint8_t _buffer[10];
			I2CNotifyEvent _i2cNotifyEvent;

		private:
			void i2cNotifyEventHandler(htl::i2c::I2CSlaveDevice *sender, htl::i2c::NotifyEventArgs &args);

		protected:
			void initializeImpl() override;
			void deinitializeImpl() override;
			uint16_t transmitImpl(const uint8_t *data, uint16_t dataLength) override;
			uint16_t receiveImpl(uint8_t *data, uint16_t dataSize) override;

		public:
			CircularSerialDriver_I2CSlave(uint8_t *txBuffer, uint16_t txBufferSize,
				uint8_t *rxBuffer, uint8_t rxBufferSize, htl::i2c::I2CSlaveDevice *dev);

			void initialize();
			void deinitialize();
	};
}


#endif // __eosCircularSerialDriver_I2CSlave__
