#pragma once
#ifndef __eosSerialDriverBase__
#define __eosSerialDriverBase__


#include "eos.h"
#include "System/eosCallbacks.h"


namespace eos {

	/// \brief Driver per comunicacions serie. 
	///
	class SerialDriverBase {
		public:
			struct TxCompletedEventArgs {
				SerialDriverBase * const driver;
				unsigned length;
			};
			struct RxCompletedEventArgs {
				SerialDriverBase * const driver;
				unsigned length;
			};
			struct AbortedEventArgs {
				SerialDriverBase * const driver;
			};

    		using ITxCompletedEvent = ICallbackP1<const TxCompletedEventArgs&>;
    		using IRxCompletedEvent = ICallbackP1<const RxCompletedEventArgs&>;
    		using IAbortedEvent = ICallbackP1<const AbortedEventArgs&>;

    		template <typename instance_> using TxCompletedEvent = CallbackP1<instance_, const TxCompletedEventArgs&>;
    		template <typename instance_> using RxCompletedEvent = CallbackP1<instance_, const RxCompletedEventArgs&>;
    		template <typename instance_> using AbortedEvent = CallbackP1<instance_, const AbortedEventArgs&>;

		private:
            const ITxCompletedEvent *_txCompletedEvent;
            const IRxCompletedEvent *_rxCompletedEvent;
            const IAbortedEvent *_abortedEvent;
            bool _txCompletedEventEnabled;
            bool _rxCompletedEventEnabled;
            bool _abortedEventEnabled;

		protected:
            void notifyTxCompleted(unsigned length);
            void notifyRxCompleted(unsigned length);
            void notifyAborted();

			virtual void initializeImpl() = 0;
			virtual void deinitializeImpl() = 0;

			/// \brief Constructor.
            ///
			SerialDriverBase();

		public:
			/// \brief Destructor
			///
			virtual ~SerialDriverBase() = default;

			void initialize();
			void deinitialize();

			void setTxCompletedEvent(const ITxCompletedEvent &event, bool enabled = true);
			void enableTxCompletedEvent() { _txCompletedEventEnabled = _txCompletedEvent != nullptr; }
			void disableTxCompletedEvent() { _txCompletedEventEnabled = false; }

			void setRxCompletedEvent(const IRxCompletedEvent &event, bool enabled = true);
            void enableRxCompletedEvent() { _rxCompletedEventEnabled = _rxCompletedEvent != nullptr; }
			void disableRxCompletedEvent() { _rxCompletedEventEnabled = false; }

			void setAbortedEvent(const IAbortedEvent &event, bool enabled = true);
            void enableAbortedEvent() { _abortedEventEnabled = _abortedEvent != nullptr; }
			void disableAbortedEvent() { _abortedEventEnabled = false; }
	};
}


#endif // __eosSerialDriverBase__
