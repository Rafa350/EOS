#pragma once
#ifndef __eosCircularSerialDriver_I2CSlave__
#define __eosCircularSerialDriver_I2CSlave__


#include "Controllers/Serial/eosCircularSerialDriver.h"
#include "HTL/htlI2C.h"


namespace eos {

	class CircularSerialDriver_I2CSlave final : public CircularSerialDriver {
		public:
			using AddressMatchCallback = htl::i2c::AddressMatchCallback<CircularSerialDriver_I2CSlave>;
			using RxDataCallback = htl::i2c::RxDataCallback<CircularSerialDriver_I2CSlave>;
			using RxCompletedCallback = htl::i2c::RxCompletedCallback<CircularSerialDriver_I2CSlave>;
			using TxDataCallback = htl::i2c::TxDataCallback<CircularSerialDriver_I2CSlave>;
			using TxCompletedCallback = htl::i2c::TxCompletedCallback<CircularSerialDriver_I2CSlave>;

		private:
			htl::i2c::I2CSlaveDeviceHandler _i2c;
			uint8_t _buffer[10];
			AddressMatchCallback _addressMatchCallback;
			RxDataCallback _rxDataCallback;
			RxCompletedCallback _rxCompletedCallback;
			TxDataCallback _txDataCallback;
			TxCompletedCallback _txCompletedCallback;

		private:
			void addressMatchHandler(uint16_t addr);
			void rxDataHandler(const uint8_t *buffer, uint16_t count);
			void rxCompletedHandler(const uint8_t *buffer, uint16_t count);
			void txDataHandler(uint8_t *buffer, uint16_t bufferSize, uint16_t &count);
			void txCompletedHandler();

		protected:
			void initializeImpl() override;
			void deinitializeImpl() override;
			uint16_t transmitImpl(const uint8_t *data, uint16_t dataLength) override;
			uint16_t receiveImpl(uint8_t *data, uint16_t dataSize) override;

		public:
			CircularSerialDriver_I2CSlave(uint8_t *txBuffer, uint16_t txBufferSize,
				uint8_t *rxBuffer, uint8_t rxBufferSize, htl::i2c::I2CSlaveDeviceHandler i2c);

			void initialize();
			void deinitialize();
	};
}


#endif // __eosCircularSerialDriver_I2CSlave__
