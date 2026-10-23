export module Eos.Services.CanOpen.Dictionary;

import Eos.Events;
import Eos.System.Core.CriticalSection;
import Eos.Types;


export namespace eos {

	enum class CoAccess: UInt8 {
		roVariable,
		rwVariable,
		roEvent,
		rwEvent,
		constant
	};

	enum class CoType: UInt8 {
		unsigned8,
		unsigned16,
		unsigned32,
		boolean,
		unknown
	};

	struct CoDictionaryEntry {
		UInt16 index;
		UInt8 subIndex;
		CoType type;
		CoAccess access;
		UInt32 data;
	};

	class CanOpenDictionary final {
		public:
			union DataValue {
				UInt8 u8;
				UInt16 u16;
				UInt32 u32;
				bool b;
			};

			enum class AccessMode {
				read,
				write
			};
			struct AccessEventArgs {
				AccessMode access;
				UInt16 index;
				UInt8 subIndex;
				DataValue value;
			};
			using AccessEventRaiser = EventRaiser<CanOpenDictionary, AccessEventArgs>;
			using IAccessEvent = AccessEventRaiser::IEvent;
			template <typename Instance_> using AccessEvent = AccessEventRaiser::Event<Instance_>;

			struct ChangedEventArgs {
				UInt16 index;
				UInt8 subIndex;
				DataValue oldValue;
				DataValue newValue;
			};
			using ChangedEventRaiser = EventRaiser<CanOpenDictionary, ChangedEventArgs>;
			using IChangedEvent = ChangedEventRaiser::IEvent;
			template <typename Instance_> using ChangedEvent = ChangedEventRaiser::Event<Instance_>;

		private:
			const CoDictionaryEntry * const _entries;
			UInt32 const _numEntries;
			AccessEventRaiser _accessEventRaiser;
			ChangedEventRaiser _changedEventRaiser;

		private:
			void onChangedU8(UInt16 index, UInt8 subIndex, UInt8 oldValue, UInt8 newValue);
			void onChangedU16(UInt16 index, UInt8 subIndex, UInt16 oldValue, UInt16 newValue);
			void onChangedU32(UInt16 index, UInt8 subIndex, UInt32 oldValue, UInt32 newValue);

			void raiseWriteU8AccessEvent(UInt16 index, UInt8 subIndex, UInt8 value);
			void raiseWriteU16AccessEvent(UInt16 index, UInt8 subIndex, UInt16 value);
     		void raiseWriteU32AccessEvent(UInt16 index, UInt8 subIndex, UInt32 value);

     		void raiseReadU8AccessEvent(UInt16 index, UInt8 subIndex, UInt8 &value);
			void raiseReadU16AccessEvent(UInt16 index, UInt8 subIndex, UInt16 &value);
     		void raiseReadU32AccessEvent(UInt16 index, UInt8 subIndex, UInt32 &value);

		public:
			CanOpenDictionary(const CoDictionaryEntry *entries, UInt32 numEntries);

			UInt32 find(UInt16 index, UInt8 subIndex) const;
			UInt32 find(const void *ptr) const;

			CoType getType(UInt32 entryId) const;

			bool canWrite(UInt32 entryId) const;
			bool writeU8(UInt32 entryId, UInt8 value);
			bool writeU8(UInt16 index, UInt8 subIndex, UInt8 value);
			bool writeU16(UInt32 entryId, UInt16 value);
			bool writeU16(UInt16 index, UInt8 subIndex, UInt16 value);
			bool writeU32(UInt32 entryId, UInt32 value);
			bool writeU32(UInt16 index, UInt8 subIndex, UInt32 value);

			bool canRead(UInt32 entryId) const;
			bool readU8(UInt32 entryId, UInt8 &value);
			bool readU8(UInt16 index, UInt8 subIndex, UInt8 &value);
			bool readU16(UInt32 entryId, UInt16 &value);
			bool readU16(UInt16 index, UInt8 subIndex, UInt16 &value);
			bool readU32(UInt32 entryId, UInt32 &value);
			bool readU32(UInt16 index, UInt8 subIndex, UInt32 &value);

            inline void enableAccessEvent(IAccessEvent &event) {
            	_accessEventRaiser.enable(event);
            }
            inline void enableChangedEvent(IChangedEvent &event) {
            	_changedEventRaiser.enable(event);
            }
	};
}


using namespace eos;


/// ----------------------------------------------------------------------
/// @brief    Constructor.
/// @param    entries: Les entrades del diccionari.
/// @param    numEntries: El nombre d'entrades en el diccionary.
///
CanOpenDictionary::CanOpenDictionary(
	const CoDictionaryEntry *entries,
	UInt32 numEntries):

	_entries {entries},
	_numEntries {numEntries} {

}


/// ----------------------------------------------------------------------
/// @brief    Busca una entrada en el diccionari.
/// @param    index: L'index de l'entrada.
/// @param    subIndex: El subindex de l'entrada.
/// @return   El identificador de la entrada, -1 si no la troba.
///
UInt32 CanOpenDictionary::find(
	UInt16 index,
	UInt8 subIndex) const {

	for (UInt32 entryId = 0; entryId < _numEntries; entryId++) {

		auto entry = &_entries[entryId];

		if ((entry->index == index) &&
			(entry->subIndex == subIndex))
			return entryId;
	}

	return (UInt32) -1;
}


/// ----------------------------------------------------------------------
/// @brief    Busca una entrada en el diccionari.
/// @param    ptr: L'adressa de la variable
/// @return   El identificador de la entrada, -1 si no la troba.
/// \remarks  Nomes troba las que son amb acces a una variable real
///
UInt32 CanOpenDictionary::find(
	const void *ptr) const {

	for (UInt32 entryId = 0; entryId < _numEntries; entryId++) {

		auto entry = &_entries[entryId];

		if ((entry->data == (UInt32)ptr) &&
			((entry->access == CoAccess::roVariable) || (entry->access == CoAccess::rwVariable)))
			return entryId;
	}

	return (UInt32) -1;
}


/// ----------------------------------------------------------------------
/// \brieg    Obte el tipus de l'entrada.
/// @param    entryId: El identificador de la entrada.
/// @return   El tipus de la entrada.
///
CoType CanOpenDictionary::getType(
	UInt32 entryId) const {

	if (entryId < _numEntries)
		return _entries[entryId].type;
	else
		return CoType::unknown;
}


/// ----------------------------------------------------------------------
/// @brief    Genera un event 'Changed'
/// @param    index: L'index.
/// @param    subIndex: El dubindex.
/// @param    oldValue: El valor abans del canvi.
/// @param    newValue: El nou valor.
///
void CanOpenDictionary::onChangedU8(
	UInt16 index,
	UInt8 subIndex,
	UInt8 oldValue,
	UInt8 newValue) {

	if (_changedEventRaiser) {

		ChangedEventArgs args = {
			.index {index},
			.subIndex {subIndex},
			.oldValue {
				.u8 {oldValue}
			},
			.newValue {
				.u8 {newValue}
			}
		};

		_changedEventRaiser(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// @brief    Genera un event 'Access'
/// @param    index: L'index
/// @param    subIndex: El subindex
/// @param    value: El valor lleigit.
///
void CanOpenDictionary::raiseReadU8AccessEvent(
	UInt16 index,
	UInt8 subIndex,
	UInt8 &value) {

	if (_accessEventRaiser) {

		AccessEventArgs args = {
			.access {AccessMode::read},
			.index {index},
			.subIndex {subIndex},
			.value {
				.u8 {value}
			}
		};

		_accessEventRaiser(this, &args);

	   value = args.value.u8;
	}
}


/// ----------------------------------------------------------------------
/// @brief    Genera un event 'Access'
/// @param    index: L'index
/// @param    subIndex: El subindex
/// @param    value: El valor lleigit.
///
void CanOpenDictionary::raiseReadU16AccessEvent(
	UInt16 index,
	UInt8 subIndex,
	UInt16 &value) {

	if (_accessEventRaiser) {

		AccessEventArgs args = {
			.access {AccessMode::read},
			.index {index},
			.subIndex {subIndex},
			.value {
				.u16 {value}
			}
		};

		_accessEventRaiser(this, &args);

		value = args.value.u16;
	}
}


/// ----------------------------------------------------------------------
/// @brief    Genera un event 'Access'
/// @param    index: L'index
/// @param    subIndex: El subindex
/// @param    value: El valor lleigit.
///
void CanOpenDictionary::raiseReadU32AccessEvent(
	UInt16 index,
	UInt8 subIndex,
	UInt32 &value) {

	if (_accessEventRaiser) {

		AccessEventArgs args = {
			.access {AccessMode::read},
			.index {index},
			.subIndex {subIndex},
			.value {
				.u32 {value}
			}
		};

		_accessEventRaiser(this, &args);

		value = args.value.u32;
	}
}


/// ----------------------------------------------------------------------
/// @brief    Genera un event 'Access'
/// @param    index: L'index
/// @param    subIndex: El subindex
/// @param    value: El valor a escriure.
///
void CanOpenDictionary::raiseWriteU8AccessEvent(
	UInt16 index,
	UInt8 subIndex,
	UInt8 value) {

	if (_accessEventRaiser) {

		AccessEventArgs args = {
			.access {AccessMode::write},
			.index {index},
			.subIndex {subIndex},
			.value {
				.u8 {value}
			}
		};

		_accessEventRaiser(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// @brief    Genera un event 'Access'
/// @param    index: L'index
/// @param    subIndex: El subindex
/// @param    value: El valor a escriure.
///
void CanOpenDictionary::raiseWriteU16AccessEvent(
	UInt16 index,
	UInt8 subIndex,
	UInt16 value) {

	if (_accessEventRaiser) {

		AccessEventArgs args;
		args.access = AccessMode::write;
		args.index = index;
		args.subIndex = subIndex;
		args.value.u16 = value;

		_accessEventRaiser(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// @brief    Genera un event 'Access'
/// @param    index: L'index
/// @param    subIndex: El subindex
/// @param    value: El valor a escriure.
///
void CanOpenDictionary::raiseWriteU32AccessEvent(
	UInt16 index,
	UInt8 subIndex,
	UInt32 value) {

	if (_accessEventRaiser) {

		AccessEventArgs args = {
			.access {AccessMode::write},
			.index {index},
			.subIndex {subIndex},
			.value {
				.u32 {value}
			}
		};

		_accessEventRaiser(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// @brief    Comprova si es pot escriure en una entrada.
/// @param    entryId: L'identificador de l'entrada.
/// @return   True si es pot escriure, false en cas contrari.
///
bool CanOpenDictionary::canWrite(
	UInt32 entryId) const {

	bool result = false;

	if (entryId < _numEntries) {
		auto entry = &_entries[entryId];

		switch (entry->access) {
			case CoAccess::rwEvent:
				result = true;
				break;

			case CoAccess::rwVariable:
				result = entry->data != 0;
				break;

			default:
				break;
		}
	}

	return result;
}


/// ----------------------------------------------------------------------
/// @brief    Comprova si es pot lleigir una entrada.
/// @param    entryId: L'identificador de l'entrada.
/// @return   True si es pot lleigit, false en cas contrari.
///
bool CanOpenDictionary::canRead(
	UInt32 entryId) const {

	bool result = false;

	if (entryId < _numEntries) {
		auto entry = &_entries[entryId];
		switch (entry->access) {
			case CoAccess::rwVariable:
			case CoAccess::roVariable:
				result = entry->data != 0;
				break;

			default:
				result = true;
				break;
		}
	}

	return result;
}


/// ----------------------------------------------------------------------
/// @brief    Escriu un valor UInt8, en l'entrada especificada.
/// @param    entryId: El identificador de l'entrada.
/// @param    value: El valor a escriure.
/// @return   True si tot es correcte, false en cas contrari.
///
bool CanOpenDictionary::writeU8(
	UInt32 entryId,
	UInt8 value) {

	bool ok = false;

	if (entryId < _numEntries) {
		auto entry = &_entries[entryId];
		if (entry->type == CoType::unsigned8) {

			UInt8 oldValue;

			if ((entry->access == CoAccess::rwVariable) && (entry->data != 0)) {

				CriticalSection::enter();
				oldValue = *((UInt8*)entry->data);
				*((UInt8*)entry->data) = value;
				CriticalSection::exit();

				ok = true;
			}
			else if (entry->access == CoAccess::rwEvent) {

				oldValue = ~value;
				raiseWriteU8AccessEvent(entry->index, entry->subIndex, value);

				ok = true;
			}

			if (ok && (oldValue != value))
				onChangedU8(entry->index, entry->subIndex, oldValue, value);
		}
	}

	return ok;
}


/// ----------------------------------------------------------------------
/// @brief    Escriu un valor UInt8, en l'entrada especificada.
/// @param    index: L'index de l'entrada.
/// @param    subIndex: El subindex de l'entrada.
/// @param    value: El valor a escriure.
/// @return   True si tot es correcte, false en cas contrari.
///
bool CanOpenDictionary::writeU8(
	UInt16 index,
	UInt8 subIndex,
	UInt8 value) {

	return writeU8(find(index, subIndex), value);
}


/// ----------------------------------------------------------------------
/// @brief    Escriu un valor UInt16, en l'entrada especificada.
/// @param    El identificador de l'entrada.
/// @param    El valor a escriure.
/// @return   True si tot es correcte, false en cas contrari.
///
bool CanOpenDictionary::writeU16(
	UInt32 entryId,
	UInt16 value) {

	bool ok = false;

	if (entryId < _numEntries) {
		auto entry = &_entries[entryId];
		if (entry->type == CoType::unsigned16) {

			UInt16 oldValue;

			if ((entry->access == CoAccess::rwVariable) && (entry->data != 0)) {

				CriticalSection::enter();
				oldValue = *((UInt16*)entry->data);
				*((UInt16*)entry->data) = value;
				CriticalSection::exit();

				ok = true;
			}
			else if (entry->access == CoAccess::rwEvent) {

				oldValue = ~value;
				raiseWriteU16AccessEvent(entry->index, entry->subIndex, value);

				ok = true;
			}

			if (ok && (oldValue != value))
				onChangedU16(entry->index, entry->subIndex, oldValue, value);
		}
	}

	return ok;
}


/// ----------------------------------------------------------------------
/// @brief    Escriu un valor UInt16, en l'entrada especificada.
/// @param    index: L'index de l'entrada.
/// @param    subIndex: El subindex de l'entrada.
/// @param    value: El valor a escriure.
/// @return   True si tot es correcte, false en cas contrari.
///
bool CanOpenDictionary::writeU16(
	UInt16 index,
	UInt8 subIndex,
	UInt16 value) {

	return writeU16(find(index, subIndex), value);
}


/// ----------------------------------------------------------------------
/// @brief    Escriu un valor UInt32, en l'entrada especificada.
/// @param    El identificador de l'entrada.
/// @param    El valor a escriure.
/// @return   True si tot es correcte, false en cas contrari.
///
bool CanOpenDictionary::writeU32(
	UInt32 entryId,
	UInt32 value) {

	bool ok = false;

	if (entryId < _numEntries) {
		auto entry = &_entries[entryId];
		if (entry->type == CoType::unsigned32) {

			UInt32 oldValue;

			if ((entry->access == CoAccess::rwVariable) && (entry->data != 0)) {

				CriticalSection::enter();
				oldValue = *((UInt32*)entry->data);
				*((UInt32*)entry->data) = value;
				CriticalSection::exit();

				ok = true;
			}
			else if (entry->access == CoAccess::rwEvent) {

				oldValue = ~value;
				raiseWriteU32AccessEvent(entry->index, entry->subIndex, value);

				ok = true;
			}

			if (ok && (oldValue != value))
				onChangedU32(entry->index, entry->subIndex, oldValue, value);
		}
	}

	return ok;
}


/// ----------------------------------------------------------------------
/// @brief    Escriu un valor UInt32, en l'entrada especificada.
/// @param    index: L'index de l'entrada.
/// @param    subIndex: El subindex de l'entrada.
/// @param    value: El valor a escriure.
/// @return   True si tot es correcte, false en cas contrari.
///
bool CanOpenDictionary::writeU32(
	UInt16 index,
	UInt8 subIndex,
	UInt32 value) {

	return writeU32(find(index, subIndex), value);
}


/// ----------------------------------------------------------------------
/// @brief    LLegeix un valor UInt8
/// @param    entryId: L'identificador de l'entrada.
/// @param    value: El valor retornat.
/// @return   True si tot es correcte, false en cas contrari.
///
bool CanOpenDictionary::readU8(
	UInt32 entryId,
	UInt8 &value) {

	bool ok = false;

	if (entryId < _numEntries) {
		auto entry = &_entries[entryId];
		if (entry->type == CoType::unsigned8) {

			switch (entry->access) {
				case CoAccess::constant:
					value = entry->data;
					ok = true;
					break;

				case CoAccess::roVariable:
				case CoAccess::rwVariable:
					if (entry->data != 0) {
						value = *((UInt8*)entry->data);
						ok = true;
					}
					break;

				case CoAccess::roEvent:
				case CoAccess::rwEvent:
					raiseReadU8AccessEvent(entry->index, entry->subIndex, value);
					ok = true;
					break;
			}
		}
	}

	return ok;
}


/// ----------------------------------------------------------------------
/// @brief    LLegeix un valor UInt8
/// @param    index: L'index de l'entrada.
/// @param    subIndex: El subindex de l'entrada.
/// @param    value: El valor retornat.
/// @return   True si tot es correcte, false en cas contrari.
///
bool CanOpenDictionary::readU8(
	UInt16 index,
	UInt8 subIndex,
	UInt8 &value) {

	return readU8(find(index, subIndex), value);
}


/// ----------------------------------------------------------------------
/// @brief    LLegeix un valor UInt16
/// @param    entryId: El identificador de l'entrada.
/// @param    value: El valor retornat.
/// @return   True si tot es correcte, false en cas contrari.
///
bool CanOpenDictionary::readU16(
	UInt32 entryId,
	UInt16 &value) {

	bool ok = false;

	if (entryId < _numEntries) {
		auto entry = &_entries[entryId];
		if (entry->type == CoType::unsigned16) {
			if (entry->access == CoAccess::constant)
				value = entry->data;
			else
				value = *((UInt16*)entry->data);

			ok = true;
		}
	}

	return ok;
}


/// ----------------------------------------------------------------------
/// @brief    LLegeix un valor UInt16
/// @param    index: L'index de l'entrada.
/// @param    subIndex: El subindex de l'entrada.
/// @param    value: El valor retornat.
/// @return   True si tot es correcte, false en cas contrari.
///
bool CanOpenDictionary::readU16(
	UInt16 index,
	UInt8 subIndex,
	UInt16 &value) {

	return readU16(find(index, subIndex), value);
}


/// ----------------------------------------------------------------------
/// @brief    LLegeix un valor UInt32
/// @param    entryId: El identificador de l'entrada.
/// @param    value: El valor retornat.
/// @return   True si tot es correcte, false en cas contrari.
///
bool CanOpenDictionary::readU32(
	UInt32 entryId,
	UInt32 &value) {

	bool ok = false;

	if (entryId < _numEntries) {
		auto entry = &_entries[entryId];

		if (entry->type == CoType::unsigned32) {
			if (entry->access == CoAccess::constant)
				value = entry->data;
			else
				value = *((UInt32*)entry->data);

			ok = true;
		}
	}

	return ok;
}


/// ----------------------------------------------------------------------
/// @brief    LLegeix un valor UInt32
/// @param    index: L'index de l'entrada.
/// @param    subIndex: El subindex de l'entrada.
/// @param    value: El valor retornat.
/// @return   True si tot es correcte, false en cas contrari.
///
bool CanOpenDictionary::readU32(
	UInt16 index,
	UInt8 subIndex,
	UInt32 &value) {

	return readU32(find(index, subIndex), value);
}
