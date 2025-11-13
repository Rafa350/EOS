#pragma once
#ifndef __eosCanOpenDictionary__
#define __eosCanOpenDictionary__


#include "eos.h"


namespace eos {

	enum class CoAccess: uint8_t {
		rw,
		ro,
		wo
	};

	enum class CoType: uint8_t {
		u8,
		u16,
		u32,
		b,
		pu8,
		pu16,
		pu32,
		pb,
	};

	struct CoDictionaryEntry {
		uint16_t index;
		uint8_t subIndex;
		CoType type;
		CoAccess access;
		uint32_t data;
	};


	constexpr uint32_t makeCobId(uint8_t function, uint8_t nodeId) {
		return ((function & 0xF) << 7) | (nodeId & 0x7F);
	}
}


#endif // __eosCanOpenDictionary__
