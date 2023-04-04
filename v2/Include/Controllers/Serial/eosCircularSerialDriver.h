#pragma once
#ifndef __eosCircularSerialDriver__
#define __eosCircularSerialDriver__


#include "eos.h"
#include "Controllers/Serial/eosCircularBuffer.h"
#include "System/eosCallbacks.h"


namespace eos {

	class CircularSerialDriver {
		public:
			struct TxBufferFullEventArgs {
			};
			struct RxBufferNotEmptyEventArgs {
			};
			using ITxBufferFullCallback = ICallbackP1<const TxBufferFullEventArgs&>;
			using IRxBufferNotEmptyCallback = ICallbackP1<const RxBufferNotEmptyEventArgs&>;

		private:
			const ITxBufferFullCallback *_txBufferFullCallback;
			const IRxBufferNotEmptyCallback *_rxBufferNotEmptyCallback;
			CircularBuffer _txBuffer;
			CircularBuffer _rxBuffer;

		protected:
			void notifyTxBufferFull();
			void notifyRxBufferNotEmpty();

			void txPush(uint8_t data);
			uint8_t txPop();
			uint16_t txAvailableSpace() const;
			uint16_t txAvailableData() const;
			void rxPush(uint8_t data);
			uint8_t rxPop();
			uint16_t rxAvailableSpace() const;
			uint16_t rxAvailableData() const;

			virtual void initializeImpl() = 0;
			virtual void deinitializeImpl() = 0;

			virtual uint16_t transmitImpl(const uint8_t *data, uint16_t dataLength) = 0;

		public:
			CircularSerialDriver(uint8_t *txBuffer, uint16_t txBufferSize, uint8_t *rxBuffer, uint8_t rxBufferSize);

			void enableTxBufferFullCallback(const ITxBufferFullCallback &callback);
			void disableTxBufferFullCallback() { _txBufferFullCallback = nullptr; }
			void enableRxBufferNotEmptyCallback(const IRxBufferNotEmptyCallback &callback);
			void disableRxBufferNotEmptyCallback() { _rxBufferNotEmptyCallback = nullptr; }

			void initialize();
			void deinitialize();

			uint16_t transmit(const uint8_t *data, uint16_t dataLength);
	};
}


#endif // __eosCircularSerialDriver__

