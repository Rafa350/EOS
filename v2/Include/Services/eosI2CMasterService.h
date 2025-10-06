#pragma once
#ifndef __eosI2CMasterService__
#define __eosI2CMasterService__


// EOS includes
//
#include "eos.h"
#include "HTL/htlI2C.h"
#include "Services/eosService.h"
#include "System/eosCallbacks.h"
#include "System/Core/eosQueue.h"
#include "System/Core/eosSemaphore.h"


namespace eos {

	class I2CMasterService final: public Service {
		public:
			struct TransactionEventArgs {
				uint8_t *txData;
				unsigned txDataLength;
				uint8_t *rxData;
				unsigned rxDataLength;
			};
            using ITransactionEvent = ICallbackP2<const I2CMasterService*, const TransactionEventArgs&>;
            template <typename Instance_> using TransactionEvent = CallbackP2<Instance_, const I2CMasterService*, const TransactionEventArgs&>;

		private:
			struct Transaction {
				htl::i2c::I2CAddr addr;
				const uint8_t *txBuffer;
				unsigned txLength;
				uint8_t *rxBuffer;
				unsigned rxBufferSize;
				unsigned rxLength;
				const ITransactionEvent *event;
			};
			using TransactionQueue = Queue<Transaction>;

		private:
			htl::i2c::I2CMasterDevice *_devI2C;
			htl::i2c::MasterNotifyEvent<I2CMasterService> _devI2CNotifyEvent;
			TransactionQueue _transactionQueue;
			Semaphore _txFinished;
			unsigned _txFinishedLength;
			Semaphore _rxFinished;
			unsigned _rxFinishedLength;

		private:
			static constexpr unsigned _transactionQueueSize = 10;

		public:
    		static constexpr uint32_t minStackSize = 256;

		private:
    		void devI2CNotifyEventHandler(htl::i2c::I2CMasterDevice * const sender, htl::i2c::NotifyEventArgs * const args);

		protected:
			void onExecute() override;

		public:
			I2CMasterService(htl::i2c::I2CMasterDevice *devI2C);

			bool startTransaction(htl::i2c::I2CAddr addr, const uint8_t *txBuffer, unsigned txLength, ITransactionEvent &event, unsigned blockTime = -1);
            bool startTransaction(htl::i2c::I2CAddr addr, const uint8_t *txBuffer, unsigned txLength, uint8_t *rxBuffer, unsigned rxBufferSize, ITransactionEvent &event, unsigned blockTime = -1);
	};

}


#endif // __eosI2CMasterService__
