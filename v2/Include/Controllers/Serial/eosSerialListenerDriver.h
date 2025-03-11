#pragma once
#ifndef __eosSerialListenerDriver__
#define __eosSerialListenerDriver__


#include "eos.h"
#include "System/eosEvents.h"
#include "System/eosResults.h"
#include "System/Collections/eosCircularBuffer.h"
#include "System/Core/eosSemaphore.h"


namespace eos {

	/// \brief Driver per comunicacions serie.
	///
	class SerialListenerDriver {
		public:
            enum class State {
                reset,
                ready,
            };

            enum class NotifyID {
            	null,
				txBufferEmpty,
				rxBufferNotEmpty
            };
            struct NotifyEventArgs {
            	unsigned count;
            };
            using ER = NotifyEventRaiser<NotifyID, NotifyEventArgs>;
            using INotifyEvent = ER::IEvent;
            template <typename Instance_> using NotifyEvent = ER::Event<Instance_>;

        private:
            using Buffer = CircularBuffer<uint8_t>;

		private:
            State _state;         // Estat del driver

            Buffer _txBuffer;     // Buffer de transmissio
            Buffer _rxBuffer;     // Buffer de recepcio.

            ER _notifyEventRaiser;
            Semaphore _semRxBufferNotEmpty;
            //Semaphore _semTxBufferEmpty;

		private:
            void raiseTxBufferEmpty();
            void raiseRxBufferNotEmpty();

		protected:
            SerialListenerDriver(uint8_t *txBuffer, unsigned txBufferSize, uint8_t *rxBuffer, unsigned rxBufferSize);

			virtual void onInitialize() = 0;
			virtual void onDeinitialize() = 0;

			unsigned rxBufferWrite(const uint8_t *pData, unsigned size, bool irq);
			unsigned txBufferRead(uint8_t *pData, unsigned size, bool irq);

		public:
			void initialize();
			void deinitialize();

			ResultU32 transmit(const uint8_t *buffer, unsigned length);
			ResultU32 receive(uint8_t *buffer, unsigned bufferSize, unsigned timeout);

			inline void setNotifyEvent(INotifyEvent &event, bool enable = true) {
				_notifyEventRaiser.set(event, enable);
			}
			inline void enableNotifyEvent() {
				_notifyEventRaiser.enable();
			}
			inline void disableNotifyEvent() {
				_notifyEventRaiser.disable();
			}

			inline State getState() const { return _state; }
			inline bool isReady() const { return _state == State::ready; }
            inline bool isBusy() const { return _state != State::ready; }
	};
}


#endif // __eosSerialListenerDriver__
