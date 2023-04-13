#pragma once
#ifndef __eosCircularSerialDriver__
#define __eosCircularSerialDriver__


#include "eos.h"
#include "Controllers/Serial/eosCircularBuffer.h"
#include "System/eosCallbacks.h"


namespace eos {

	class CircularSerialDriver {
		public:
			struct TxBufferEmptyEventArgs {
				uint16_t availableSpace;
			};
			struct RxBufferNotEmptyEventArgs {
				uint16_t availableData;
			};
			using ITxBufferEmptyCallback = ICallbackP1<const TxBufferEmptyEventArgs&>;
			using IRxBufferNotEmptyCallback = ICallbackP1<const RxBufferNotEmptyEventArgs&>;

		private:
			const ITxBufferEmptyCallback *_txBufferEmptyCallback;
			const IRxBufferNotEmptyCallback *_rxBufferNotEmptyCallback;
			CircularBuffer _txBuffer;
			CircularBuffer _rxBuffer;

		protected:
			void notifyTxBufferEmpty();
			void notifyRxBufferNotEmpty();

			inline void txPush(uint8_t data) { _txBuffer.push(data); }
			inline uint8_t txPop() { return _txBuffer.pop(); }
			uint16_t txAvailableSpace() const;
			inline uint16_t txAvailableData() const { return _txBuffer.getSize(); }

			inline void rxPush(uint8_t data) { _rxBuffer.push(data); }
			inline uint8_t rxPop() { return _rxBuffer.pop(); }
			uint16_t rxAvailableSpace() const;
			inline uint16_t rxAvailableData() const { return _rxBuffer.getSize(); }

			virtual void initializeImpl() = 0;
			virtual void deinitializeImpl() = 0;

			virtual uint16_t transmitImpl(const uint8_t *data, uint16_t dataLength) = 0;
			virtual uint16_t receiveImpl(uint8_t *data, uint16_t dataLength) = 0;

		public:
			CircularSerialDriver(uint8_t *txBuffer, uint16_t txBufferSize, uint8_t *rxBuffer, uint16_t rxBufferSize);

			void enableTxBufferEmptyCallback(const ITxBufferEmptyCallback &callback);
			void disableTxBufferEmptyCallback() { _txBufferEmptyCallback = nullptr; }
			void enableRxBufferNotEmptyCallback(const IRxBufferNotEmptyCallback &callback);
			void disableRxBufferNotEmptyCallback() { _rxBufferNotEmptyCallback = nullptr; }

			void initialize();
			void deinitialize();

			uint16_t transmit(const uint8_t *data, uint16_t dataLength);
			uint16_t receive(uint8_t *data, uint16_t dataSize);
			inline uint16_t receivePending() const { return rxAvailableData(); }
			inline uint16_t transmitPending() const { return txAvailableData(); }
	};
}


#endif // __eosCircularSerialDriver__

