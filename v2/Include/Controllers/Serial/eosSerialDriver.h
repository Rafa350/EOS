#pragma once
#ifndef __eosSerialDriver__
#define __eosSerialDriver__


#include "eos.h"
#include "Controllers/Serial/eosSerialDriverBase.h"


namespace eos {

	/// \brief Driver per comunicacionsa serie.
	///
	class SerialDriver: public SerialDriverBase {
	    public:
            enum class State {
                reset,
                ready,
                tranmiting,
                receiving
            };
	    private:
            State _state;

		protected:
			virtual void initializeImpl();
			virtual void deinitializeImpl();
			virtual bool transmitImpl(const uint8_t *buffer, unsigned length) = 0;
			virtual bool receiveImpl(uint8_t *buffer, unsigned bufferSize) = 0;
			virtual bool abortImpl();

			/// \brief Constructor.
            ///
			SerialDriver();

		public:
			bool transmit(const uint8_t *buffer, unsigned length);
			bool receive(uint8_t *buffer, unsigned bufferSize);
			bool abort();

            bool isReady() const { return _state == State::ready; }
            bool isBusy() const { return _state != State::ready; }
	};
}


#endif // __eosSerialDriver__
