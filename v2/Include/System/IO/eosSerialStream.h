#pragma once

#include "eos.h"
#include "Controllers/Serial/eosSerialDriver.h"
#include "System/Core/eosSemaphore.h"
#include "System/IO/eosStream.h"


namespace eos {

	class SerialStream: public Stream {

		private:
    		using TxCompletedEvent = eos::SerialDriver::TxCompletedEvent<SerialStream>;
    		using RxCompletedEvent = eos::SerialDriver::RxCompletedEvent<SerialStream>;

		private:
			eos::SerialDriver *_drvSerial;

			TxCompletedEvent _txCompletedEvent;
			eos::Semaphore _txCompleted;
			unsigned _txTimeout = unsigned(-1);

			RxCompletedEvent _rxCompletedEvent;
			eos::Semaphore _rxCompleted;
			unsigned _rxDataCount;
			unsigned _rxTimeout = unsigned(-1);

		private:
			void txCompletedEventHandler(const eos::SerialDriver::TxCompletedEventArgs &args);
            void rxCompletedEventHandler(const eos::SerialDriver::RxCompletedEventArgs &args);

		public:
			SerialStream();
			SerialStream(SerialDriver *drvSerial);

			Result initialize(SerialDriver *drvSerial);
			Result deinitialize();

			inline void setWriteTimeout(unsigned timeout) {
				_txTimeout = timeout;
			}
			inline void setReadTimeout(unsigned timeout) {
				_rxTimeout = timeout;
			}

			Result write(const uint8_t *data, unsigned length, unsigned *count = nullptr) override;
			Result read(uint8_t *data, unsigned size, unsigned *count = nullptr) override;
	};
}
