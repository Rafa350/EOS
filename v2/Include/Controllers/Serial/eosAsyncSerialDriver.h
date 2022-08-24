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
				unsigned count;
			};
			struct RxCompletedEventArgs {
				AsyncSerialDriver *driver;
				unsigned count;
			};
			struct AbortedEventArgs {
				AsyncSerialDriver *driver;
			};
    		using ITxCompletedCallback = ICallbackP1<const TxCompletedEventArgs&>;
    		using IRxCompletedCallback = ICallbackP1<const RxCompletedEventArgs&>;
    		using IAbortedCallback = ICallbackP1<const AbortedEventArgs&>;

		private:
			State _state;
            ITxCompletedCallback *_txCompletedCallback;
            IRxCompletedCallback *_rxCompletedCallback;
            IAbortedCallback *_abortedCallback;

		protected:
            void notifyTxStart();
            void notifyRxStart();
            void notifyTxCompleted(unsigned count);
            void notifyRxCompleted(unsigned count);
            void notifyAborted();

		public:
            /// \brief Constructor.
            ///
			AsyncSerialDriver();

			/// \brief Destructor
			///
			virtual ~AsyncSerialDriver();

			virtual void initialize();
			virtual void deinitialize();

			State getState() const;
			inline bool isBusy() const { return getState() != State::ready; }
			inline bool isReady() const { return getState() == State::ready; }

			void enableTxCompletedCallback(ITxCompletedCallback &callback);
			void disableTxCompletedCallback() { _txCompletedCallback = nullptr; }
			void enableRxCompletedCallback(IRxCompletedCallback &callback);
			void disableRxCompletedCallback() { _rxCompletedCallback = nullptr; }
			void enableAbortedCallback(IAbortedCallback &callback);
			void disableAbortedCallback() { _abortedCallback = nullptr; }

			virtual bool transmit(const uint8_t *data, unsigned dataLength) = 0;
			virtual bool receive(uint8_t *data, unsigned dataSize) = 0;
	};
}


#endif // eosAsyncSerialDriver__
