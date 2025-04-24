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

        private:
            State _state;
            Semaphore _txFinished;
            Semaphore _rxFinished;
            unsigned _txCount;
            unsigned _rxCount;

		protected:
            SerialDriver();

            void notifyTxCompleted(unsigned length, bool irq);
            void notifyRxCompleted(unsigned length, bool irq);
            State getState() const { return _state; }

			virtual bool onInitialize() = 0;
			virtual bool onDeinitialize() = 0;
			virtual bool onTransmit(const uint8_t *buffer, unsigned length) = 0;
			virtual bool onReceive(uint8_t *buffer, unsigned bufferSize) = 0;
			virtual bool onAbort() = 0;

		public:
			virtual ~SerialDriver() = default;

			void initialize();
			void deinitialize();

			Result transmit(const uint8_t *buffer, unsigned length);
            Result receive(uint8_t *buffer, unsigned bufferSize);
            ResultU32 wait(unsigned timeout);
            Result abort();

			inline bool isReady() const { return _state == State::ready; }
            inline bool isBusy() const { return _state != State::ready; }
	};
}


#endif // __eosSerialDriver__
