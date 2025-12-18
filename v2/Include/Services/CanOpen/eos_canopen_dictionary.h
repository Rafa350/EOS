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

#define EV_RW_BOOL(index, subIndex) \
	{index, subIndex, CoType::boolean, CoAccess::rwEvent, 0}
#define EV_RW_U8(index, subIndex) \
	{index, subIndex, CoType::unsigned8, CoAccess::rwEvent, 0}
#define EV_RW_U16(index, subIndex) \
	{index, subIndex, CoType::unsigned16, CoAccess::rwEvent, 0}
#define EV_RW_U32(index, subIndex) \
	{index, subIndex, CoType::unsigned32, CoAccess::rwEvent, 0}

#define EV_RO_BOOL(index, subIndex) \
	{index, subIndex, CoType::boolean, CoAccess::roEvent, 0}
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
		boolean,
		bytes
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
			enum class NotificationID {
				valueChanged
			};
			struct NotificationEventArgs {
				NotificationID id;
				union {
					struct {
						uint16_t index;
						uint8_t subIndex;
						unsigned oldValue;
					} valueChanged;
				};
			};
			using NotificationEventRaiser = eos::EventRaiser<CanOpenDictionary, NotificationEventArgs>;
			using INotificationEvent = NotificationEventRaiser::IEvent;
			template <typename Instance_> using NotificationEvent = NotificationEventRaiser::Event<Instance_>;

			enum class DataMode {
				read,
				write
			};
			enum class DataType  {
				u8,
				u16,
				u32,
				b
			};
			struct DataEventArgs {
				DataMode dataMode;
				DataType dataType;
				uint16_t index;
				uint8_t subIndex;
				union {
					uint8_t u8;
					uint16_t u16;
					uint32_t u32;
					bool b;
				};
			};
			using DataEventRaiser = eos::EventRaiser<CanOpenDictionary, DataEventArgs>;
			using IDataEvent = DataEventRaiser::IEvent;
			template <typename Instance_> using DataEvent = DataEventRaiser::Event<Instance_>;

		private:
			const CoDictionaryEntry * const _entries;
			unsigned const _numEntries;
			NotificationEventRaiser _erNotification;
			DataEventRaiser _erData;

		private:
			void raiseValueChangedNotificationEvent(unsigned entryId, unsigned oldValue);
			void raiseWriteDataEvent(uint16_t index, uint8_t subIndex, uint8_t value);
			void raiseWriteDataEvent(uint16_t index, uint8_t subIndex, uint16_t value);
     		void raiseWriteDataEvent(uint16_t index, uint8_t subIndex, uint32_t value);
			void raiseWriteDataEvent(uint16_t index, uint8_t subIndex, bool value);
			void raiseReadDataEvent(uint16_t index, uint8_t subIndex, uint8_t &value);
			void raiseReadDataEvent(uint16_t index, uint8_t subIndex, uint16_t &value);
     		void raiseReadDataEvent(uint16_t index, uint8_t subIndex, uint32_t &value);
			void raiseReadDataEvent(uint16_t index, uint8_t subIndex, bool &value);


		public:
			CanOpenDictionary(const CoDictionaryEntry *entries, unsigned numEntries);

			unsigned find(uint16_t index, uint8_t subIndex) const;
			unsigned find(const void *ptr) const;

			unsigned getDataLength(unsigned entryId) const;
			uint16_t getIndex(unsigned entryId) const;
			uint8_t getSubIndex(unsigned entryId) const;

			bool canWrite(unsigned entryId) const;
			bool writeU8(unsigned entryId, uint8_t value);
			bool writeU16(unsigned entryId, uint16_t value);
			bool writeU32(unsigned entryId, uint32_t value);
			bool writeBool(unsigned entryId, bool value);

			bool canRead(unsigned entryId) const;
			bool readU8(unsigned entryId, uint8_t &value);
			bool readU16(unsigned entryId, uint16_t &value);
			bool readU32(unsigned entryId, uint32_t &value);
			bool readBool(unsigned entryId, bool &value);

			void setNotificationEvent(INotificationEvent &event, bool enabled = true);
            void enableNotifyEvent();
            void disableNotifyEvent();

            void setDataEvent(IDataEvent &event, bool enabled = true);
            void enableDataEvent();
            void disableDataEvent();
	};
}


#endif // __eos_canopen_dictionary__
