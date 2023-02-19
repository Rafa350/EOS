#pragma once
#ifndef __eosAsyncSerialDriver_I2C__
#define __eosAsyncSerialDriver_I2C__


#include "Controllers/Serial/eosAsyncSerialDriver.h"
#include "HTL/htlI2C.h"


namespace eos {

	class AsyncSerialDriver_I2C: public AsyncSerialDriver {
		private:
			struct Flags {
				int rxMode:1;
			};
		private:
			htl::I2CHandler _hI2C;
			Flags _flags;
			const uint8_t *_txData;
			int _txLength;
			int _txCount;
			uint8_t *_rxData;
			int _rxSize;
			int _rxCount;

		protected:
			void initializeImpl() override;
			void deinitializeImpl() override;
			bool transmitImpl(const uint8_t *data, int dataLength) override;
			bool receiveImpl(uint8_t *data, int dataSize) override;

			void interruptHandler();
			static void interruptFunction(htl::I2CInterruptParam param);

		public:
			AsyncSerialDriver_I2C(htl::I2CHandler hI2C);
	};
}


#endif // __eosAsyncSerialDriver_I2C__
