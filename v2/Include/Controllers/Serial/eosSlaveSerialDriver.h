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

          struct TxStartEventArgs {
              SlaveSerialDriver * const driver;
              uint8_t *buffer;
              unsigned length;
          };

          struct TxCompletedEventArgs {
              SlaveSerialDriver * const driver;
              unsigned length;
          };

          struct RxStartEventArgs {
              SlaveSerialDriver * const driver;
              uint8_t *buffer;
              unsigned bufferSize;
          };

          struct RxCompletedEventArgs {
              SlaveSerialDriver * const driver;
              unsigned length;
          };

          using ITxStartEvent = ICallbackP1<const TxStartEventArgs&>;
          using ITxCompletedEvent = ICallbackP1<const TxCompletedEventArgs&>;
          using IRxStartEvent = ICallbackP1<const RxStartEventArgs&>;
          using IRxCompletedEvent = ICallbackP1<const RxCompletedEventArgs&>;

          template <typename instance_> using TxStartEvent = CallbackP1<instance_, const TxStartEventArgs&>;
          template <typename instance_> using TxCompletedEvent = CallbackP1<instance_, const TxCompletedEventArgs&>;
          template <typename instance_> using RxStartEvent = CallbackP1<instance_, const RxStartEventArgs&>;
          template <typename instance_> using RxCompletedEvent = CallbackP1<instance_, const RxCompletedEventArgs&>;

	    private:
	        State _state;
	        const ITxStartEvent *_txStartEvent;
            const ITxCompletedEvent *_txCompletedEvent;
            const IRxStartEvent *_rxStartEvent;
            const IRxCompletedEvent *_rxCompletedEvent;
            bool _txStartEventEnabled;
            bool _txCompletedEventEnabled;
            bool _rxStartEventEnabled;
            bool _rxCompletedEventEnabled;

	    private:
            void raiseListenStart();
            void raiseTxCompleted(unsigned length);
            void raiseRxCompleted(unsigned length);

        protected:
			SlaveSerialDriver();

			void notifyTxStart(uint8_t * &buffer, unsigned &length);
			void notifyTxCompleted(unsigned length);
			void notifyRxStart(uint8_t * &buffer, unsigned &bufferSize);
            void notifyRxCompleted(unsigned length);

			virtual void onInitialize() = 0;
			virtual void onDeinitialize() = 0;
            virtual void onListen(const uint8_t *txBuffer, unsigned txBufferSize, uint8_t *rxBuffer, unsigned rxBufferSize) = 0;

		public:
            virtual ~SlaveSerialDriver() = default;

            void initialize();
            void deinitialize();

			bool listen(const uint8_t *txBuffer, unsigned txBufferSize, uint8_t *rxBuffer, unsigned rxBufferSize);

            void setTxStartEvent(const ITxStartEvent &event, bool enabled = true);
            inline void enableTxStartEvent() { _txStartEventEnabled = _txCompletedEvent != nullptr; }
            inline void disableTxStartEvent() { _txStartEventEnabled = false; }

            void setTxCompletedEvent(const ITxCompletedEvent &event, bool enabled = true);
            inline void enableTxCompletedEvent() { _txCompletedEventEnabled = _txCompletedEvent != nullptr; }
            inline void disableTxCompletedEvent() { _txCompletedEventEnabled = false; }

            void setRxStartEvent(const IRxStartEvent &event, bool enabled = true);
            inline void enableRxStartEvent() { _rxStartEventEnabled = _rxCompletedEvent != nullptr; }
            inline void disableRxStartEvent() { _rxStartEventEnabled = false; }

            void setRxCompletedEvent(const IRxCompletedEvent &event, bool enabled = true);
            inline void enableRxCompletedEvent() { _rxCompletedEventEnabled = _rxCompletedEvent != nullptr; }
            inline void disableRxCompletedEvent() { _rxCompletedEventEnabled = false; }

            inline bool isReady() const { return _state == State::ready; }
			inline bool isBusy() const { return _state != State::ready; }
	};
}


#endif // __eosSlaveSerialDriver__
