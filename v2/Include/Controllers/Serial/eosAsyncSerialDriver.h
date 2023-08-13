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
    		using ITxCompletedEvent = ICallbackP1<const TxCompletedEventArgs&>;
    		using IRxCompletedEvent = ICallbackP1<const RxCompletedEventArgs&>;
    		using IAbortedEvent = ICallbackP1<const AbortedEventArgs&>;
    		template <typename _instance> using TxCompletedEvent = CallbackP1<_instance, const TxCompletedEventArgs&>;
    		template <typename _instance> using RxCompletedEvent = CallbackP1<_instance, const RxCompletedEventArgs&>;
    		template <typename _instance> using AbortedEvent = CallbackP1<_instance, const AbortedEventArgs&>;

		private:
			State _state;
            const ITxCompletedEvent *_txCompletedEvent;
            const IRxCompletedEvent *_rxCompletedEvent;
            const IAbortedEvent *_abortedEvent;

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

			void enableTxCompletedEvent(const ITxCompletedEvent &event);
			void disableTxCompletedEvent() { _txCompletedEvent = nullptr; }
			void enableRxCompletedEvent(const IRxCompletedEvent &event);
			void disableRxCompletedEvent() { _rxCompletedEvent = nullptr; }
			void enableAbortedEvent(const IAbortedEvent &event);
			void disableAbortedEvent() { _abortedEvent = nullptr; }

			bool transmit(const uint8_t *data, int dataLength);
			bool receive(uint8_t *data, int dataSize);
	};
}


#endif // eosAsyncSerialDriver__
