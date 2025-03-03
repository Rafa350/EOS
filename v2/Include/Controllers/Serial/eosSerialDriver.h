#pragma once
#ifndef __eosSerialDriver__
#define __eosSerialDriver__


#include "eos.h"
#include "System/eosCallbacks.h"
#include "System/eosResults.h"
#include "System/Core/eosSemaphore.h"


namespace eos {

	/// \brief Driver per comunicacions serie.
	///
	class SerialDriver {
		public:
            enum class State {
                reset,
                ready,
                transmiting,
                receiving
            };

			struct TxCompletedEventArgs {
				SerialDriver * const driver;
				unsigned length;
			};

			struct RxCompletedEventArgs {
				SerialDriver * const driver;
				unsigned length;
			};

    		using ITxCompletedEvent = ICallbackP1<const TxCompletedEventArgs&>;
    		using IRxCompletedEvent = ICallbackP1<const RxCompletedEventArgs&>;

    		template <typename instance_> using TxCompletedEvent = CallbackP1<instance_, const TxCompletedEventArgs&>;
    		template <typename instance_> using RxCompletedEvent = CallbackP1<instance_, const RxCompletedEventArgs&>;

        private:
            State _state;
            Semaphore _txFinished;
            Semaphore _rxFinished;
            unsigned _txCount;
            unsigned _rxCount;
            const ITxCompletedEvent *_txCompletedEvent;
            const IRxCompletedEvent *_rxCompletedEvent;
            bool _txCompletedEventEnabled;
            bool _rxCompletedEventEnabled;

        private:
            void raiseTxCompleted(unsigned length);
            void raiseRxCompleted(unsigned length);

		protected:
            SerialDriver();

            void notifyTxCompleted(unsigned length, bool irq);
            void notifyRxCompleted(unsigned length, bool irq);
            State getState() const { return _state; }

			virtual void onInitialize() = 0;
			virtual void onDeinitialize() = 0;
			virtual void onTransmit(const uint8_t *buffer, unsigned length) = 0;
			virtual void onReceive(uint8_t *buffer, unsigned bufferSize) = 0;
			virtual void onAbort() = 0;

		public:
			virtual ~SerialDriver() = default;

			void initialize();
			void deinitialize();

			Result transmit(const uint8_t *buffer, unsigned length);
            Result receive(uint8_t *buffer, unsigned bufferSize);
            ResultU32 wait(unsigned timeout);
            Result abort();

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


#endif // __eosSerialDriver__
