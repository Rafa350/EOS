#pragma once
#ifndef __eos_canopen_dictionary__
#define __eos_canopen_dictionary__


#include "eos.h"
#include "System/eosEvents.h"


namespace eos {

	enum class CoAccess: uint8_t {
		readWrite,
		readOnly,
		writeOnly,
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

		private:
			const CoDictionaryEntry * const _entries;
			unsigned const _numEntries;
			NotificationEventRaiser _erNotification;

		private:
			void raiseValueChangedNotification(unsigned entryId, unsigned oldValue);

		public:
			CanOpenDictionary(const CoDictionaryEntry *entries, unsigned numEntries);

			unsigned find(uint16_t index, uint8_t subIndex) const;
			unsigned find(const void *ptr) const;

			unsigned getDataLength(unsigned entryId) const;
			uint16_t getIndex(unsigned entryId) const;
			uint8_t getSubIndex(unsigned entryId) const;

			bool canWrite(unsigned entryId);
			bool write(unsigned entryId, unsigned value);
			bool writeU8(unsigned entryId, uint8_t value);
			bool writeU16(unsigned entryId, uint16_t value);
			bool writeU32(unsigned entryId, uint32_t value);
			bool writeBool(unsigned entryId, bool value);

			bool canRead(unsigned entryId) const;
			bool read(unsigned entryId, unsigned &value) const;
			bool readU8(unsigned entryId, uint8_t &value) const;
			bool readU16(unsigned entryId, uint16_t &value) const;
			bool readU32(unsigned entryId, uint32_t &value) const;
			bool readBool(unsigned entryId, bool &value) const;

			void setNotificationEvent(INotificationEvent &event, bool enabled = true);
            void enableNotifyEvent();
            void disableNotifyEvent();
	};
}


#endif // __eos_canopen_dictionary__
