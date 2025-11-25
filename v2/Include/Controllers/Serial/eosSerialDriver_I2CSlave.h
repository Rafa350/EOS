#pragma once
#ifndef __eosSerialDriver_I2CSlave__
#define __eosSerialDriver_I2CSlave__


#include "Controllers/Serial/eosSerialDriver.h"
#include "HTL/htlI2C.h"


namespace eos {

	class SerialDriver_I2CSlave: public SerialDriver {
		protected:
			htl::i2c::I2CSlaveDevice * const _devI2C;

		private:
			htl::i2c::SlaveNotificationEvent<SerialDriver_I2CSlave> _i2cNotificationEvent;
			uint8_t *_buffer;
			unsigned _bufferSize;

		private:
			void i2cNotificationEventHandler(htl::i2c::I2CSlaveDevice *sender, htl::i2c::NotificationEventArgs * const args);

		protected:
            bool onInitialize() override;
            bool onDeinitialize() override;
            bool onTransmit(const uint8_t *buffer, unsigned length) override;
            bool onReceive(uint8_t *buffer, unsigned bufferSize) override;
            bool onAbort() override;

		public:
			SerialDriver_I2CSlave(htl::i2c::I2CSlaveDevice *devI2C);
	};
}


#endif // __eosSerialDriver_I2CSlave__
