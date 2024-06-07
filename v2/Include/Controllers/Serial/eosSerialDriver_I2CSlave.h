#pragma once
#ifndef __eosSerialDriver_I2CSlave__
#define __eosSerialDriver_I2CSlave__


#include "Controllers/Serial/eosSerialDriver.h"
#include "HTL/htlI2C.h"


namespace eos {

	class SerialDriver_I2CSlave final: public SerialDriver {
		public:
	        using DevI2C = htl::i2c::I2CSlaveDevice;

		private:
			using I2CNotifyEvent = htl::i2c::SlaveNotifyEvent<SerialDriver_I2CSlave>;
			using I2CNotifyEventArgs = htl::i2c::NotifyEventArgs;

		private:
			DevI2C * const _devI2C;
			I2CNotifyEvent _i2cNotifyEvent;
			uint8_t *_rxBuffer;
			unsigned _rxBufferSize;
			const uint8_t *_txBuffer;
			unsigned _txLength;

		private:
			void onInitialize() override;
			void onDeinitialize() override;
            void onTransmit(const uint8_t *buffer, unsigned length) override;
            void onReceive(uint8_t *buffer, unsigned bufferSize) override;

            void i2cNotifyEventHandler(I2CNotifyEventArgs &args);

		public:
			SerialDriver_I2CSlave(DevI2C *devI2C);
	};
}


#endif // __eosSlaveSerialDriver_I2CSLAVE__
