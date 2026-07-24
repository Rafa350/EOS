#pragma once

#include "eos.h"
#include "eosTime.h"
#include "Controllers/Serial/eosSerialDriver.h"
#include "System/IO/eosStream.h"


namespace eos {

	class SerialStream: public Stream {

		private:
			SerialDriver *_drvSerial;
			Time _txTimeout = Times::infinite;
			Time _rxTimeout = Times::infinite;

		public:
			SerialStream();
			SerialStream(SerialDriver *drvSerial);

			Result initialize(SerialDriver *drvSerial);
			Result deinitialize();

			inline void setWriteTimeout(Time timeout) {
				_txTimeout = timeout;
			}
			inline void setReadTimeout(Time timeout) {
				_rxTimeout = timeout;
			}

			ResultU32 write(const uint8_t *buffer, uint32_t length) override;
			ResultU32 read(uint8_t *buffer, uint32_t bufferSize) override;
	};
}
