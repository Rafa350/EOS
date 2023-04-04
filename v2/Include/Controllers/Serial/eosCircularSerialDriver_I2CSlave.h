#pragma once
#ifndef __eosCircularSerialDriver_I2CSlave__
#define __eosCircularSerialDriver_I2CSlave__


#include "Controllers/Serial/eosCircularSerialDriver.h"
#include "HTL/htlI2C.h"


namespace eos {

	class CircularSerialDriver_I2CSlave final : public CircularSerialDriver {
		private:
			htl::I2CHandler _hI2C;

		private:
			void rxInterruptHandler();
			void txInterruptHandler();
			static void rxInterruptFunction(htl::I2CInterruptParam param);
			static void txInterruptFunction(htl::I2CInterruptParam param);

		protected:
			void initializeImpl() override;
			void deinitializeImpl() override;
			uint16_t transmitImpl(const uint8_t *data, uint16_t dataLength) override;

		public:
			CircularSerialDriver_I2CSlave(uint8_t *txBuffer, uint16_t txBufferSize,
				uint8_t *rxBuffer, uint8_t rxBufferSize, htl::I2CHandler hI2C);

			void initialize();
			void deinitialize();
	};
}


#endif // __eosCircularSerialDriver_I2CSlave__
