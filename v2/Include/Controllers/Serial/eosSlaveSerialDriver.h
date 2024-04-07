#pragma once
#ifndef __eosSlaveSerialDriver__
#define __eosSlaveSerialDriver__


#include "eos.h"
#include "System/eosCallbacks.h"


namespace eos {

	/// \brief Driver per comunicacionsa serie.
	///
	class SlaveSerialDriver {
	    public:
	      enum class State {
	          reset,
	          ready,
	          listening,
	          transmiting,
	          receiving
	      };

	      struct TxCompletedEventArgs {
              SlaveSerialDriver * const driver;
              unsigned length;
          };

          struct RxCompletedEventArgs {
              SlaveSerialDriver * const driver;
              unsigned length;
          };

          using ITxCompletedEvent = ICallbackP1<const TxCompletedEventArgs&>;
          using IRxCompletedEvent = ICallbackP1<const RxCompletedEventArgs&>;

          template <typename instance_> using TxCompletedEvent = CallbackP1<instance_, const TxCompletedEventArgs&>;
          template <typename instance_> using RxCompletedEvent = CallbackP1<instance_, const RxCompletedEventArgs&>;

	    private:
	        State _state;
            const ITxCompletedEvent *_txCompletedEvent;
            const IRxCompletedEvent *_rxCompletedEvent;
            bool _txCompletedEventEnabled;
            bool _rxCompletedEventEnabled;

	    private:
            void raiseListenStart();
            void raiseTxCompleted(unsigned length);
            void raiseRxCompleted(unsigned length);

        protected:
			SlaveSerialDriver();

			void notifyTxCompleted(unsigned length);
            void notifyRxCompleted(unsigned length);

			virtual void onInitialize() = 0;
			virtual void onDeinitialize() = 0;
            virtual void onListen(const uint8_t *txBuffer, unsigned txBufferSize, uint8_t *rxBuffer, unsigned rxBufferSize) = 0;

		public:
            virtual ~SlaveSerialDriver() = default;

            void initialize();
            void deinitialize();

			bool listen(const uint8_t *txBuffer, unsigned txBufferSize, uint8_t *rxBuffer, unsigned rxBufferSize);

            void setTxCompletedEvent(const ITxCompletedEvent &event, bool enabled = true);
            void enableTxCompletedEvent() { _txCompletedEventEnabled = _txCompletedEvent != nullptr; }
            void disableTxCompletedEvent() { _txCompletedEventEnabled = false; }

            void setRxCompletedEvent(const IRxCompletedEvent &event, bool enabled = true);
            void enableRxCompletedEvent() { _rxCompletedEventEnabled = _rxCompletedEvent != nullptr; }
            void disableRxCompletedEvent() { _rxCompletedEventEnabled = false; }

			inline bool isReady() const { return _state == State::ready; }
			inline bool isBusy() const { return _state != State::ready; }
	};
}


#endif // __eosSlaveSerialDriver__
