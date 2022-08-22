#pragma once
#ifndef __eosSerialDriver_IT__
#define __eosSerialDriver_IT__


#include "HTL/htlUART.h"
#include "System/eosCallbacks.h"


namespace eos {

	class SerialDriver_IT {
		public:
			enum class State {
				reset,
				ready,
				transmiting,
				receiving
			};
			struct TxCompletedEventArgs {
				SerialDriver_IT *driver;
				unsigned count;
			};
			struct RxCompletedEventArgs {
				SerialDriver_IT *driver;
				unsigned count;
			};
			struct AbortedEventArgs {
				SerialDriver_IT *driver;
			};
    		using ITxCompletedCallback = ICallbackP1<const TxCompletedEventArgs&>;
    		using IRxCompletedCallback = ICallbackP1<const RxCompletedEventArgs&>;
    		using IAbortedCallback = ICallbackP1<const AbortedEventArgs&>;

		private:
			htl::UARTAdapter &_uart;
			State _state;
			const uint8_t *_txData;
			unsigned _txLength;
			unsigned _txCount;
			uint8_t *_rxData;
			unsigned _rxSize;
			unsigned _rxCount;
            ITxCompletedCallback *_txCompletedCallback;
            IRxCompletedCallback *_rxCompletedCallback;
            IAbortedCallback *_abortedCallback;

            void notifyTxCompleted();
            void notifyRxCompleted();
            void notifyAborted();
			void interruptHandler(htl::UARTEvent event);
			static void interruptHandler(htl::UARTEvent event, htl::UARTInterruptParam param);

		public:
			SerialDriver_IT(htl::UARTAdapter &uart);
			~SerialDriver_IT();

			void initialize();
			void deinitialize();

			State getState() const;
			inline bool isBusy() const { return getState() != State::ready; }

			void setTxCompletedCallback(ITxCompletedCallback &callback);
			void setRxCompletedCallback(IRxCompletedCallback &callback);
			void setAbortedCallback(IAbortedCallback &callback);

			bool transmit(const uint8_t *data, unsigned dataLength);
			bool receive(uint8_t *data, unsigned dataSize);
	};
}


#endif // eosSerialDriver_IT__
