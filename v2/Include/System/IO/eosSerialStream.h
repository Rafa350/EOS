#pragma once

#include "eos.h"
#include "Controllers/Serial/eosSerialDriver.h"
#include "System/IO/eosStream.h"


namespace eos {

	class SerialStream: public Stream {

		private:
			SerialDriver *_drvSerial;
			unsigned _txTimeout = unsigned(-1);
			unsigned _rxTimeout = unsigned(-1);

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

			ResultU32 write(const uint8_t *data, unsigned length) override;
			ResultU32 read(uint8_t *data, unsigned size) override;
	};
}
