#pragma once


#include "eos.h"
#include "eosResults.h"
#include "RTOS/rtosTask.h"


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
            rtos::Task *_task;
            volatile bool _finished;
            unsigned _txCount;
            unsigned _rxCount;

		protected:
            SerialDriver();

            void notifyTxCompleted(uint32_t length, bool irq);
            void notifyRxCompleted(uint32_t length, bool irq);
            State getState() const { return _state; }

			virtual bool onInitialize() = 0;
			virtual bool onDeinitialize() = 0;
			virtual bool onTransmit(const uint8_t *buffer, uint32_t length) = 0;
			virtual bool onReceive(uint8_t *buffer, uint32_t bufferSize) = 0;
			virtual bool onAbort() = 0;

		public:
			virtual ~SerialDriver() = default;

			void initialize();
			void deinitialize();

			Result transmit(const uint8_t *buffer, uint32_t length);
            Result receive(uint8_t *buffer, uint32_t bufferSize);
            ResultU32 wait(unsigned waitTime);
            Result abort();

			inline bool isReady() const { return _state == State::ready; }
            inline bool isBusy() const { return _state != State::ready; }
	};
}
