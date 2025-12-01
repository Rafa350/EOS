#pragma once
#ifndef __eos_canopen_tpdo_transmitter__
#define __eos_canopen_tpdo_transmitter__


#include "eos.h"
#include "System/eosResults.h"


namespace eos {

	class CanOpenDictionary;

	class CanOpenTPDOTransmitter {
		private:
			CanOpenDictionary * const _dictionary;

		public:
			CanOpenTPDOTransmitter(CanOpenDictionary * dictionary);

			eos::Result process(unsigned tpdoId, uint8_t *response);
	};
}


#endif // __eos_canopen_tpdo_transmitter
