#pragma once
#ifndef __eosSerialDriver_I2CSlave__
#define __eosSerialDriver_I2CSlave__


#include "HTL/htl.h"
#include "HTL/htlI2C.h"


#include "Controllers/Serial/eosSerialListenerDriver.h"


namespace eos {

	class SerialListenerDriver_I2CSlave final: public SerialListenerDriver {
		public:
	        using DevI2C = htl::i2c::I2CSlaveDevice;

		private:
	        using I2CNotifyID = htl::i2c::NotifyID;
			using I2CNotifyEvent = htl::i2c::SlaveNotifyEvent<SerialListenerDriver_I2CSlave>;
			using I2CNotifyEventArgs = htl::i2c::NotifyEventArgs;

		private:
			DevI2C * const _devI2C;
			I2CNotifyEvent _devI2CNotifyEvent;
			uint8_t *_buffer;
			unsigned _bufferSize;

		private:
			void onInitialize() override;
			void onDeinitialize() override;

            void devI2CNotifyEventHandler(I2CNotifyID, I2CNotifyEventArgs * const args);

		public:
			SerialListenerDriver_I2CSlave(DevI2C *devI2C, uint8_t *txBuffer, unsigned txBufferSize, uint8_t *rxBuffer, unsigned rxBufferSize);
			~SerialListenerDriver_I2CSlave();
	};
}


#endif // __eosSlaveSerialDriver_I2CSlave__
