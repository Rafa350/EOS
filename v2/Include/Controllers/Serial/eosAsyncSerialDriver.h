#pragma once


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

    		template <typename instance_> using TxCompletedEvent = CallbackP1<instance_, const TxCompletedEventArgs&>;
    		template <typename instance_> using RxCompletedEvent = CallbackP1<instance_, const RxCompletedEventArgs&>;
    		template <typename instance_> using AbortedEvent = CallbackP1<instance_, const AbortedEventArgs&>;

		private:
			State _state;

            const ITxCompletedEvent *_txCompletedEvent;
            const IRxCompletedEvent *_rxCompletedEvent;
            const IAbortedEvent *_abortedEvent;
            bool _txCompletedEventEnabled;
            bool _rxCompletedEventEnabled;
            bool _abortedEventEnabled;

		protected:
            void notifyTxStart();
            void notifyRxStart();
            void notifyTxCompleted(int count);
            void notifyRxCompleted(int count);
            void notifyAborted();

			virtual void initializeImpl();
			virtual void deinitializeImpl();
			virtual bool transmitImpl(const uint8_t *buffer, unsigned bufferSize) = 0;
			virtual bool receiveImpl(uint8_t *buffer, unsigned bufferSize) = 0;

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

			void setTxCompletedEvent(const ITxCompletedEvent &event, bool enabled = true);
			void enableTxCompletedEvent() { _txCompletedEventEnabled = _txCompletedEvent != nullptr; }
			void disableTxCompletedEvent() { _txCompletedEventEnabled = false; }

			void setRxCompletedEvent(const IRxCompletedEvent &event, bool enabled = true);
            void enableRxCompletedEvent() { _rxCompletedEventEnabled = _rxCompletedEvent != nullptr; }
			void disableRxCompletedEvent() { _rxCompletedEventEnabled = false; }

			void setAbortedEvent(const IAbortedEvent &event, bool enabled = true);
            void enableAbortedEvent() { _abortedEventEnabled = _abortedEvent != nullptr; }
			void disableAbortedEvent() { _abortedEventEnabled = false; }

			bool transmit(const uint8_t *buffer, unsigned bufferSize);
			bool receive(uint8_t *buffer, unsigned bufferSize);
	};
}
