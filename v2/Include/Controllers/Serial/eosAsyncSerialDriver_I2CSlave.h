#pragma once
#ifndef __eosAsyncSerialDriver_I2CSLAVE__
#define __eosAsyncSerialDriver_I2CSLAVE__


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
			DevI2C * const _devI2C;
			uint8_t * const _buffer;
			unsigned const _bufferSize;
			I2CNotifyEvent _i2cNotifyEvent;
			uint8_t *_rxBuffer;
			unsigned _rxBufferSize;
			unsigned _rxCount;
			const uint8_t *_txBuffer;
			unsigned _txBufferSize;
			unsigned _txCount;

		private:
			void initializeImpl() override;
			void deinitializeImpl() override;

			bool startTxImpl(const uint8_t *buffer, unsigned length) override;
			bool startRxImpl(uint8_t *buffer, unsigned bufferSize) override;
			bool abortImpl() override;

            void i2cNotifyEventHandler(I2CNotifyEventArgs &args);

		public:
			AsyncSerialDriver_I2CSlave(DevI2C *devI2C, uint8_t *buffer, unsigned bufferSize);
	};
}


#endif // __eosAsyncSerialDriver_I2CSLAVE__
