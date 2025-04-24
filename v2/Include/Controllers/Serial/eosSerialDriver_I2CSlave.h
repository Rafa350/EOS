#pragma once
#ifndef __eosSerialDriver_I2CSlave__
#define __eosSerialDriver_I2CSlave__


#include "Controllers/Serial/eosSerialDriver.h"
#include "HTL/htlI2C.h"


namespace eos {

	class SerialDriver_I2CSlave: public SerialDriver {
	    public:
            using DevI2C = htl::i2c::I2CSlaveDevice;

	    private:
            using I2CNotifyID = htl::i2c::NotifyID;
	        using I2CNotifyEvent = htl::i2c::SlaveNotifyEvent<SerialDriver_I2CSlave>;
	        using I2CNotifyEventArgs = htl::i2c::NotifyEventArgs;

		protected:
			DevI2C * const _devI2C;

		private:
			I2CNotifyEvent _i2cNotifyEvent;
			uint8_t *_buffer;
			unsigned _bufferSize;

		private:
			void i2cNotifyEventHandler(I2CNotifyID id, I2CNotifyEventArgs * const args);

		protected:
            bool onInitialize() override;
            bool onDeinitialize() override;
            bool onTransmit(const uint8_t *buffer, unsigned length) override;
            bool onReceive(uint8_t *buffer, unsigned bufferSize) override;
            bool onAbort() override;

		public:
			SerialDriver_I2CSlave(DevI2C *devI2C);
	};
}


#endif // __eosSerialDriver_I2CSlave__
