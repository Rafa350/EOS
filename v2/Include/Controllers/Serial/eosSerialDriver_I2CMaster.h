#pragma once
#ifndef __eosSerialDriver_I2CMaster__
#define __eosSerialDriver_I2CMaster__


#include "Controllers/Serial/eosSerialDriver.h"
#include "HTL/htlI2C.h"


namespace eos {

	class SerialDriver_I2CMaster: public SerialDriver {
		protected:
			htl::i2c::I2CMasterDevice * const _devI2C;

		private:
			htl::i2c::MasterNotifyEvent<SerialDriver_I2CMaster> _i2cNotifyEvent;

		private:
			void i2cNotifyEventHandler(htl::i2c::I2CMasterDevice *sender, htl::i2c::NotifyEventArgs * const args);

		protected:
            bool onInitialize() override;
            bool onDeinitialize() override;
            bool onTransmit(const uint8_t *buffer, unsigned length) override;
            bool onReceive(uint8_t *buffer, unsigned bufferSize) override;
            bool onAbort() override;

		public:
			SerialDriver_I2CMaster(htl::i2c::I2CMasterDevice *devI2C);
	};
}


#endif // __eosSerialDriver_I2CMaster__
