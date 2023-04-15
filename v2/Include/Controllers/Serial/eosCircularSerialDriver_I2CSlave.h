#pragma once
#ifndef __eosCircularSerialDriver_I2CSlave__
#define __eosCircularSerialDriver_I2CSlave__


#include "Controllers/Serial/eosCircularSerialDriver.h"
#include "HTL/htlI2C.h"


namespace eos {

	class CircularSerialDriver_I2CSlave final : public CircularSerialDriver {
		private:
			htl::i2c::I2CSlaveDeviceHandler _hI2C;
			uint8_t _buffer[1];

		private:
			void interruptHandler(htl::i2c::I2CInterruptNotify notify);
			static void interruptFunction(htl::i2c::I2CInterruptNotify notify, htl::i2c::I2CInterruptParam param);

		protected:
			void initializeImpl() override;
			void deinitializeImpl() override;
			uint16_t transmitImpl(const uint8_t *data, uint16_t dataLength) override;
			uint16_t receiveImpl(uint8_t *data, uint16_t dataSize) override;

		public:
			CircularSerialDriver_I2CSlave(uint8_t *txBuffer, uint16_t txBufferSize,
				uint8_t *rxBuffer, uint8_t rxBufferSize, htl::i2c::I2CSlaveDeviceHandler hI2C);

			void initialize();
			void deinitialize();
	};
}


#endif // __eosCircularSerialDriver_I2CSlave__
