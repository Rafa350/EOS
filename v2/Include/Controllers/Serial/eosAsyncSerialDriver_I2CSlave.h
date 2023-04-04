#pragma once
#ifndef __eosAsyncSerialDriver_I2C__
#define __eosAsyncSerialDriver_I2C__


#include "Controllers/Serial/eosAsyncSerialDriver.h"
#include "HTL/htlI2C.h"


namespace eos {

	class AsyncSerialDriver_I2CSlave final: public AsyncSerialDriver {
		private:
			htl::I2CHandler _hI2C;
			const uint8_t *_txData;
			int _txLength;
			int _txCount;
			uint8_t *_rxData;
			int _rxSize;
			int _rxCount;

		private:
			void rxInterruptHandler();
			void txInterruptHandler();
			static void rxInterruptFunction(htl::I2CInterruptParam param);
			static void txInterruptFunction(htl::I2CInterruptParam param);

		protected:
			void initializeImpl() override;
			void deinitializeImpl() override;
			bool transmitImpl(const uint8_t *data, int dataLength) override;
			bool receiveImpl(uint8_t *data, int dataSize) override;

		public:
			AsyncSerialDriver_I2CSlave(htl::I2CHandler hI2C);
	};
}


#endif // __eosAsyncSerialDriver_I2C__
