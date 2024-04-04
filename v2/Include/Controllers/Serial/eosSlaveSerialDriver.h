#pragma once
#ifndef __eosSlaveSerialDriver__
#define __eosSlaveSerialDriver__


#include "eos.h"
#include "Controllers/Serial/eosSerialDriverBase.h"


namespace eos {

	/// \brief Driver per comunicacionsa serie.
	///
	class SlaveSerialDriver: public SerialDriverBase {
        private:
            enum class State {
                reset,
                ready,
                listening,
                transmiting,
                receiving
            };
            
        protected:
            State _state;
            
        protected:
			SlaveSerialDriver();
            void initializeImpl() override;
            void deinitializeImpl() override;
            virtual void listenImpl(const uint8_t *txBuffer, unsigned txBufferSize, uint8_t *rxBuffer, unsigned rxBufferSize) = 0;

		public:
			bool listen(const uint8_t *txBuffer, unsigned txBufferSize, uint8_t *rxBuffer, unsigned rxBufferSize);
			bool abort();
            
            bool isReady() const { return _state == State::ready; }
            bool isBusy() const { return _state != State::ready; }
	};
}


#endif // __eosSerialDriver__
