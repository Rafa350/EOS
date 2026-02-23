#pragma once
#ifndef __eos_canopen_dictionary__
#define __eos_canopen_dictionary__


#include "eos.h"
#include "System/eosEvents.h"


#define VAR_RW_BOOL(index, subIndex, data) \
	{index, subIndex, CoType::boolean, CoAccess::rwVariable, (uint32_t)(& data)}
#define VAR_RW_U8(index, subIndex, data) \
	{index, subIndex, CoType::unsigned8, CoAccess::rwVariable, (uint32_t)(& data)}
#define VAR_RW_U16(index, subIndex, data) \
	{index, subIndex, CoType::unsigned16, CoAccess::rwVariable, (uint32_t)(& data)}
#define VAR_RW_U32(index, subIndex, data) \
	{index, subIndex, CoType::unsigned32, CoAccess::rwVariable, (uint32_t)(& data)}

#define VAR_RO_BOOL(index, subIndex, data) \
	{index, subIndex, CoType::boolean, CoAccess::roVariable, (uint32_t)(& data)}
#define VAR_RO_U8(index, subIndex, data) \
	{index, subIndex, CoType::unsigned8, CoAccess::roVariable, (uint32_t)(& data)}
#define VAR_RO_U16(index, subIndex, data) \
	{index, subIndex, CoType::unsigned16, CoAccess::roVariable, (uint32_t)(& data)}
#define VAR_RO_U32(index, subIndex, data) \
	{index, subIndex, CoType::unsigned32, CoAccess::roVariable, (uint32_t)(& data)}

#define CONST_BOOL(index, subIndex, data) \
	{index, subIndex, CoType::boolean, CoAccess::constant, data}
#define CONST_U8(index, subIndex, data) \
	{index, subIndex, CoType::unsigned8, CoAccess::constant, data}
#define CONST_U16(index, subIndex, data) \
	{index, subIndex, CoType::unsigned16, CoAccess::constant, data}
#define CONST_U32(index, subIndex, data) \
	{index, subIndex, CoType::unsigned32, CoAccess::constant, data}

#define EV_RW_U8(index, subIndex) \
	{index, subIndex, CoType::unsigned8, CoAccess::rwEvent, 0}
#define EV_RW_U16(index, subIndex) \
	{index, subIndex, CoType::unsigned16, CoAccess::rwEvent, 0}
#define EV_RW_U32(index, subIndex) \
	{index, subIndex, CoType::unsigned32, CoAccess::rwEvent, 0}

#define EV_RO_U8(index, subIndex) \
	{index, subIndex, CoType::unsigned8, CoAccess::roEvent, 0}
#define EV_RO_U16(index, subIndex) \
	{index, subIndex, CoType::unsigned16, CoAccess::roEvent, 0}
#define EV_RO_U32(index, subIndex) \
	{index, subIndex, CoType::unsigned32, CoAccess::roEvent, 0}

#define ARRAY(index, elements) \
		{index, 0, CoType::unsigned8, CoAccess::constant, elements}


namespace eos {

	enum class CoAccess: uint8_t {
		roVariable,
		rwVariable,
		roEvent,
		rwEvent,
		constant
	};

	enum class CoType: uint8_t {
		unsigned8,
		unsigned16,
		unsigned32,
		unknown
	};

	struct CoDictionaryEntry {
		uint16_t index;
		uint8_t subIndex;
		CoType type;
		CoAccess access;
		uint32_t data;
	};

	class CanOpenDictionary final {
		public:
			union DataValue {
				uint8_t u8;
				uint16_t u16;
				uint32_t u32;
				bool b;
			};

			enum class AccessMode {
				read,
				write
			};
			struct AccessEventArgs {
				AccessMode access;
				uint16_t index;
				uint8_t subIndex;
				DataValue value;
			};
			using AccessEventRaiser = eos::EventRaiser<CanOpenDictionary, AccessEventArgs>;
			using IAccessEvent = AccessEventRaiser::IEvent;
			template <typename Instance_> using AccessEvent = AccessEventRaiser::Event<Instance_>;

			struct ChangedEventArgs {
				uint16_t index;
				uint8_t subIndex;
				DataValue oldValue;
				DataValue newValue;
			};
			using ChangedEventRaiser = eos::EventRaiser<CanOpenDictionary, ChangedEventArgs>;
			using IChangedEvent = ChangedEventRaiser::IEvent;
			template <typename Instance_> using ChangedEvent = ChangedEventRaiser::Event<Instance_>;

		private:
			const CoDictionaryEntry * const _entries;
			unsigned const _numEntries;
			AccessEventRaiser _erAccess;
			ChangedEventRaiser _erChanged;

		private:
			void raiseChangedU8Event(uint16_t index, uint8_t subIndex, uint8_t oldValue, uint8_t newValue);
			void raiseChangedU16Event(uint16_t index, uint8_t subIndex, uint16_t oldValue, uint16_t newValue);
			void raiseChangedU32Event(uint16_t index, uint8_t subIndex, uint32_t oldValue, uint32_t newValue);
			void raiseWriteU8AccessEvent(uint16_t index, uint8_t subIndex, uint8_t value);
			void raiseWriteU16AccessEvent(uint16_t index, uint8_t subIndex, uint16_t value);
     		void raiseWriteU32AccessEvent(uint16_t index, uint8_t subIndex, uint32_t value);
			void raiseReadU8AccessEvent(uint16_t index, uint8_t subIndex, uint8_t &value);
			void raiseReadU16AccessEvent(uint16_t index, uint8_t subIndex, uint16_t &value);
     		void raiseReadU32AccessEvent(uint16_t index, uint8_t subIndex, uint32_t &value);

		public:
			CanOpenDictionary(const CoDictionaryEntry *entries, unsigned numEntries);

			unsigned find(uint16_t index, uint8_t subIndex) const;
			unsigned find(const void *ptr) const;

			CoType getType(unsigned entryId) const;

			bool canWrite(unsigned entryId) const;
			bool writeU8(unsigned entryId, uint8_t value);
			bool writeU8(uint16_t index, uint8_t subIndex, uint8_t value);
			bool writeU16(unsigned entryId, uint16_t value);
			bool writeU16(uint16_t index, uint8_t subIndex, uint16_t value);
			bool writeU32(unsigned entryId, uint32_t value);
			bool writeU32(uint16_t index, uint8_t subIndex, uint32_t value);

			bool canRead(unsigned entryId) const;
			bool readU8(unsigned entryId, uint8_t &value);
			bool readU8(uint16_t index, uint8_t subIndex, uint8_t &value);
			bool readU16(unsigned entryId, uint16_t &value);
			bool readU16(uint16_t index, uint8_t subIndex, uint16_t &value);
			bool readU32(unsigned entryId, uint32_t &value);
			bool readU32(uint16_t index, uint8_t subIndex, uint32_t &value);

            void setAccessEvent(IAccessEvent &event);
            void setChangedEvent(IChangedEvent &event);
	};
}


#endif // __eos_canopen_dictionary__
