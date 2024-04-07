#pragma once
#ifndef __eosSlaveSerialDriver_I2CSlave__
#define __eosSlaveSerialDriver_I2CSlave__


#include "Controllers/Serial/eosSlaveSerialDriver.h"
#include "HTL/htlI2C.h"


namespace eos {

	class SlaveSerialDriver_I2CSlave final: public SlaveSerialDriver {
		public:
	        using DevI2C = htl::i2c::I2CSlaveDevice;

		private:
			using I2CNotifyEvent = htl::i2c::SlaveNotifyEvent<SlaveSerialDriver_I2CSlave>;
			using I2CNotifyEventArgs = htl::i2c::NotifyEventArgs;

		private:
			DevI2C * const _devI2C;
			I2CNotifyEvent _i2cNotifyEvent;
			uint8_t *_rxBuffer;
			unsigned _rxBufferSize;
			unsigned _rxCount;
			const uint8_t *_txBuffer;
			unsigned _txBufferSize;
			unsigned _txCount;

		private:
			void onInitialize() override;
			void onDeinitialize() override;
			void onListen(const uint8_t *txBuffer, unsigned txBufferSize,
			        uint8_t *rxBuffer, unsigned rxBufferSize) override;

            void i2cNotifyEventHandler(I2CNotifyEventArgs &args);

		public:
			SlaveSerialDriver_I2CSlave(DevI2C *devI2C);
	};
}


#endif // __eosSlaveSerialDriver_I2CSLAVE__
