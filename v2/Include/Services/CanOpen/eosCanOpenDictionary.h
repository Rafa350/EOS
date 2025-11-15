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

	class CanOpenDictionary final {
		private:
			const CoDictionaryEntry * const _entries;
			unsigned const _numEntries;

		public:
			CanOpenDictionary(const CoDictionaryEntry *entries, unsigned numEntries);

			unsigned find(uint16_t index, uint8_t subIndex) const;

			unsigned getDataLength(unsigned entryId) const;

			bool canWrite(unsigned entryId) const;
			bool write(unsigned entryId, unsigned value) const;
			bool writeU8(unsigned entryId, uint8_t value) const;
			bool writeU16(unsigned entryId, uint16_t value) const;
			bool writeU32(unsigned entryId, uint32_t value) const;

			bool canRead(unsigned entryId) const;
			bool readU8(unsigned entryId, uint8_t &value) const;
			bool readU16(unsigned entryId, uint16_t &value) const;
			bool readU32(unsigned entryId, uint32_t &value) const;
	};
}


#endif // __eosCanOpenDictionary__
