#pragma once
#ifndef __eosAsyncSerialDriver__
#define __eosAsyncSerialDriver__


#include "eos.h"
#include "System/eosCallbacks.h"


namespace eos {

	/// \brief Driver per comunicacionsa serie.
	///
	class AsyncSerialDriver {
		public:
			enum class State {
				reset,
				ready,
				transmiting,
				receiving
			};
			struct TxCompletedEventArgs {
				AsyncSerialDriver *driver;
				int count;
			};
			struct RxCompletedEventArgs {
				AsyncSerialDriver *driver;
				int count;
			};
			struct AbortedEventArgs {
				AsyncSerialDriver *driver;
			};
    		using ITxCompletedCallback = ICallbackP1<const TxCompletedEventArgs&>;
    		using IRxCompletedCallback = ICallbackP1<const RxCompletedEventArgs&>;
    		using IAbortedCallback = ICallbackP1<const AbortedEventArgs&>;

		private:
			State _state;
            const ITxCompletedCallback *_txCompletedCallback;
            const IRxCompletedCallback *_rxCompletedCallback;
            const IAbortedCallback *_abortedCallback;

		protected:
            void notifyTxStart();
            void notifyRxStart();
            void notifyTxCompleted(int count);
            void notifyRxCompleted(int count);
            void notifyAborted();

			virtual void initializeImpl();
			virtual void deinitializeImpl();
			virtual bool transmitImpl(const uint8_t *data, int dataLength) = 0;
			virtual bool receiveImpl(uint8_t *data, int dataSize) = 0;

			/// \brief Constructor.
            ///
			AsyncSerialDriver();

		public:
			/// \brief Destructor
			///
			virtual ~AsyncSerialDriver() = default;

			void initialize();
			void deinitialize();

			State getState() const;
			inline bool isBusy() const { return getState() != State::ready; }
			inline bool isReady() const { return getState() == State::ready; }

			void enableTxCompletedCallback(const ITxCompletedCallback &callback);
			void disableTxCompletedCallback() { _txCompletedCallback = nullptr; }
			void enableRxCompletedCallback(const IRxCompletedCallback &callback);
			void disableRxCompletedCallback() { _rxCompletedCallback = nullptr; }
			void enableAbortedCallback(const IAbortedCallback &callback);
			void disableAbortedCallback() { _abortedCallback = nullptr; }

			bool transmit(const uint8_t *data, int dataLength);
			bool receive(uint8_t *data, int dataSize);
	};
}


#endif // eosAsyncSerialDriver__
