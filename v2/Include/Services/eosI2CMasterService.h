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

			};
            using ITransactionEvent = ICallbackP2<const I2CMasterService*, const TransactionEventArgs&>;
            template <typename Instance_> using TransactionEvent = CallbackP2<Instance_, const I2CMasterService*, const TransactionEventArgs&>;
            using DevI2C = htl::i2c::I2CMasterDevice;
            using NotifyEvent = htl::i2c::MasterNotifyEvent<I2CMasterService>;

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
			DevI2C *_devI2C;
			TransactionQueue _transactionQueue;
			Semaphore _finishedTransaction;
			NotifyEvent _notifyEvent;

		private:
			static constexpr unsigned _transactionQueueSize = 10;

		public:
    		static constexpr uint32_t minStackSize = 256;

		private:
    		void notifyEventHandler(htl::i2c::NotifyEventArgs &args);

		protected:
			bool onTask() override;

		public:
			I2CMasterService(DevI2C *devI2C);

			bool startTransaction(htl::i2c::I2CAddr addr, const uint8_t *txBuffer, unsigned txLength, ITransactionEvent &event, unsigned blockTime = -1);
            bool startTransaction(htl::i2c::I2CAddr addr, const uint8_t *txBuffer, unsigned txLength, uint8_t *rxBuffer, unsigned rxBufferSize, ITransactionEvent &event, unsigned blockTime = -1);
	};

}


#endif // __eosI2CMasterService__
