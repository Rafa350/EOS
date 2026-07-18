#pragma once
#ifndef __eosEEPROM__
#define __eosEEPROM__


#include "eos.h"


namespace eos {

	class EEPROMDriver {
		public:
			virtual ~EEPROMDriver() = default;

			virtual void read(uint32_t addr, uint8_t *data, uint32_t dataLength) = 0;
			virtual void write(uint32_t addr, const uint8_t *data, uint32_t dataLength) = 0;
	};
}



#endif // __eosEEPROM__
