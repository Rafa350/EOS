#include "eos.h"
#include "RTOS/rtosCriticalSection.h"
#include "Services/CanOpen/eosCanOpenDictionary.h"


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    entries: Les entrades del diccionari.
/// \param    numEntries: El nombre d'entrades en el diccionary.
///
eos::CanOpenDictionary::CanOpenDictionary(
	const CoDictionaryEntry *entries,
	uint32_t numEntries):

	_entries {entries},
	_numEntries {numEntries} {

}


/// ----------------------------------------------------------------------
/// \brief    Busca una entrada en el diccionari.
/// \param    index: L'index de l'entrada.
/// \param    subIndex: El subindex de l'entrada.
/// \return   El identificador de la entrada, -1 si no la troba.
///
uint32_t eos::CanOpenDictionary::find(
	uint16_t index,
	uint8_t subIndex) const {

	for (uint32_t entryId = 0; entryId < _numEntries; entryId++) {

		auto entry = &_entries[entryId];

		if ((entry->index == index) &&
			(entry->subIndex == subIndex))
			return entryId;
	}

	return (uint32_t) -1;
}


/// ----------------------------------------------------------------------
/// \brief    Busca una entrada en el diccionari.
/// \param    ptr: L'adressa de la variable
/// \return   El identificador de la entrada, -1 si no la troba.
/// \remarks  Nomes troba las que son amb acces a una variable real
///
uint32_t eos::CanOpenDictionary::find(
	const void *ptr) const {

	for (uint32_t entryId = 0; entryId < _numEntries; entryId++) {

		auto entry = &_entries[entryId];

		if ((entry->data == (uint32_t)ptr) &&
			((entry->access == CoAccess::roVariable) || (entry->access == CoAccess::rwVariable)))
			return entryId;
	}

	return (uint32_t) -1;
}


/// ----------------------------------------------------------------------
/// \brieg    Obte el tipus de l'entrada.
/// \param    entryId: El identificador de la entrada.
/// \return   El tipus de la entrada.
///
eos::CoType eos::CanOpenDictionary::getType(
	uint32_t entryId) const {

	if (entryId < _numEntries)
		return _entries[entryId].type;
	else
		return CoType::unknown;
}


/// ----------------------------------------------------------------------
/// \brief    Genera un event 'Changed'
/// \param    index: L'index.
/// \param    subIndex: El dubindex.
/// \param    oldValue: El valor abans del canvi.
/// \param    newValue: El nou valor.
///
void eos::CanOpenDictionary::onChangedU8(
	uint16_t index,
	uint8_t subIndex,
	uint8_t oldValue,
	uint8_t newValue) {

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
/// \brief    Genera un event 'Access'
/// \param    index: L'index
/// \param    subIndex: El subindex
/// \param    value: El valor lleigit.
///
void eos::CanOpenDictionary::raiseReadU8AccessEvent(
	uint16_t index,
	uint8_t subIndex,
	uint8_t &value) {

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
/// \brief    Genera un event 'Access'
/// \param    index: L'index
/// \param    subIndex: El subindex
/// \param    value: El valor lleigit.
///
void eos::CanOpenDictionary::raiseReadU16AccessEvent(
	uint16_t index,
	uint8_t subIndex,
	uint16_t &value) {

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
/// \brief    Genera un event 'Access'
/// \param    index: L'index
/// \param    subIndex: El subindex
/// \param    value: El valor lleigit.
///
void eos::CanOpenDictionary::raiseReadU32AccessEvent(
	uint16_t index,
	uint8_t subIndex,
	uint32_t &value) {

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
/// \brief    Genera un event 'Access'
/// \param    index: L'index
/// \param    subIndex: El subindex
/// \param    value: El valor a escriure.
///
void eos::CanOpenDictionary::raiseWriteU8AccessEvent(
	uint16_t index,
	uint8_t subIndex,
	uint8_t value) {

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
/// \brief    Genera un event 'Access'
/// \param    index: L'index
/// \param    subIndex: El subindex
/// \param    value: El valor a escriure.
///
void eos::CanOpenDictionary::raiseWriteU16AccessEvent(
	uint16_t index,
	uint8_t subIndex,
	uint16_t value) {

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
/// \brief    Genera un event 'Access'
/// \param    index: L'index
/// \param    subIndex: El subindex
/// \param    value: El valor a escriure.
///
void eos::CanOpenDictionary::raiseWriteU32AccessEvent(
	uint16_t index,
	uint8_t subIndex,
	uint32_t value) {

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
/// \brief    Comprova si es pot escriure en una entrada.
/// \param    entryId: L'identificador de l'entrada.
/// \return   True si es pot escriure, false en cas contrari.
///
bool eos::CanOpenDictionary::canWrite(
	uint32_t entryId) const {

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
/// \brief    Comprova si es pot lleigir una entrada.
/// \param    entryId: L'identificador de l'entrada.
/// \return   True si es pot lleigit, false en cas contrari.
///
bool eos::CanOpenDictionary::canRead(
	uint32_t entryId) const {

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
/// \brief    Escriu un valor uint8_t, en l'entrada especificada.
/// \param    entryId: El identificador de l'entrada.
/// \param    value: El valor a escriure.
/// \return   True si tot es correcte, false en cas contrari.
///
bool eos::CanOpenDictionary::writeU8(
	uint32_t entryId,
	uint8_t value) {

	bool ok = false;

	if (entryId < _numEntries) {
		auto entry = &_entries[entryId];
		if (entry->type == CoType::unsigned8) {

			uint8_t oldValue;

			if ((entry->access == CoAccess::rwVariable) && (entry->data != 0)) {

				rtos::CriticalSection::enter();
				oldValue = *((uint8_t*)entry->data);
				*((uint8_t*)entry->data) = value;
				rtos::CriticalSection::exit();

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
/// \brief    Escriu un valor uint8_t, en l'entrada especificada.
/// \param    index: L'index de l'entrada.
/// \param    subIndex: El subindex de l'entrada.
/// \param    value: El valor a escriure.
/// \return   True si tot es correcte, false en cas contrari.
///
bool eos::CanOpenDictionary::writeU8(
	uint16_t index,
	uint8_t subIndex,
	uint8_t value) {

	return writeU8(find(index, subIndex), value);
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un valor uint16_t, en l'entrada especificada.
/// \param    El identificador de l'entrada.
/// \param    El valor a escriure.
/// \return   True si tot es correcte, false en cas contrari.
///
bool eos::CanOpenDictionary::writeU16(
	uint32_t entryId,
	uint16_t value) {

	bool ok = false;

	if (entryId < _numEntries) {
		auto entry = &_entries[entryId];
		if (entry->type == CoType::unsigned16) {

			uint16_t oldValue;

			if ((entry->access == CoAccess::rwVariable) && (entry->data != 0)) {

				rtos::CriticalSection::enter();
				oldValue = *((uint16_t*)entry->data);
				*((uint16_t*)entry->data) = value;
				rtos::CriticalSection::exit();

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
/// \brief    Escriu un valor uint16_t, en l'entrada especificada.
/// \param    index: L'index de l'entrada.
/// \param    subIndex: El subindex de l'entrada.
/// \param    value: El valor a escriure.
/// \return   True si tot es correcte, false en cas contrari.
///
bool eos::CanOpenDictionary::writeU16(
	uint16_t index,
	uint8_t subIndex,
	uint16_t value) {

	return writeU16(find(index, subIndex), value);
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un valor uint32_t, en l'entrada especificada.
/// \param    El identificador de l'entrada.
/// \param    El valor a escriure.
/// \return   True si tot es correcte, false en cas contrari.
///
bool eos::CanOpenDictionary::writeU32(
	uint32_t entryId,
	uint32_t value) {

	bool ok = false;

	if (entryId < _numEntries) {
		auto entry = &_entries[entryId];
		if (entry->type == CoType::unsigned32) {

			uint32_t oldValue;

			if ((entry->access == CoAccess::rwVariable) && (entry->data != 0)) {

				rtos::CriticalSection::enter();
				oldValue = *((uint32_t*)entry->data);
				*((uint32_t*)entry->data) = value;
				rtos::CriticalSection::exit();

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
/// \brief    Escriu un valor uint32_t, en l'entrada especificada.
/// \param    index: L'index de l'entrada.
/// \param    subIndex: El subindex de l'entrada.
/// \param    value: El valor a escriure.
/// \return   True si tot es correcte, false en cas contrari.
///
bool eos::CanOpenDictionary::writeU32(
	uint16_t index,
	uint8_t subIndex,
	uint32_t value) {

	return writeU32(find(index, subIndex), value);
}


/// ----------------------------------------------------------------------
/// \brief    LLegeix un valor uint8_t
/// \param    entryId: L'identificador de l'entrada.
/// \param    value: El valor retornat.
/// \return   True si tot es correcte, false en cas contrari.
///
bool eos::CanOpenDictionary::readU8(
	uint32_t entryId,
	uint8_t &value) {

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
						value = *((uint8_t*)entry->data);
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
/// \brief    LLegeix un valor uint8_t
/// \param    index: L'index de l'entrada.
/// \param    subIndex: El subindex de l'entrada.
/// \param    value: El valor retornat.
/// \return   True si tot es correcte, false en cas contrari.
///
bool eos::CanOpenDictionary::readU8(
	uint16_t index,
	uint8_t subIndex,
	uint8_t &value) {

	return readU8(find(index, subIndex), value);
}


/// ----------------------------------------------------------------------
/// \brief    LLegeix un valor uint16_t
/// \param    entryId: El identificador de l'entrada.
/// \param    value: El valor retornat.
/// \return   True si tot es correcte, false en cas contrari.
///
bool eos::CanOpenDictionary::readU16(
	uint32_t entryId,
	uint16_t &value) {

	bool ok = false;

	if (entryId < _numEntries) {
		auto entry = &_entries[entryId];
		if (entry->type == CoType::unsigned16) {
			if (entry->access == CoAccess::constant)
				value = entry->data;
			else
				value = *((uint16_t*)entry->data);

			ok = true;
		}
	}

	return ok;
}


/// ----------------------------------------------------------------------
/// \brief    LLegeix un valor uint16_t
/// \param    index: L'index de l'entrada.
/// \param    subIndex: El subindex de l'entrada.
/// \param    value: El valor retornat.
/// \return   True si tot es correcte, false en cas contrari.
///
bool eos::CanOpenDictionary::readU16(
	uint16_t index,
	uint8_t subIndex,
	uint16_t &value) {

	return readU16(find(index, subIndex), value);
}


/// ----------------------------------------------------------------------
/// \brief    LLegeix un valor uint32_t
/// \param    entryId: El identificador de l'entrada.
/// \param    value: El valor retornat.
/// \return   True si tot es correcte, false en cas contrari.
///
bool eos::CanOpenDictionary::readU32(
	uint32_t entryId,
	uint32_t &value) {

	bool ok = false;

	if (entryId < _numEntries) {
		auto entry = &_entries[entryId];

		if (entry->type == CoType::unsigned32) {
			if (entry->access == CoAccess::constant)
				value = entry->data;
			else
				value = *((uint32_t*)entry->data);

			ok = true;
		}
	}

	return ok;
}


/// ----------------------------------------------------------------------
/// \brief    LLegeix un valor uint32_t
/// \param    index: L'index de l'entrada.
/// \param    subIndex: El subindex de l'entrada.
/// \param    value: El valor retornat.
/// \return   True si tot es correcte, false en cas contrari.
///
bool eos::CanOpenDictionary::readU32(
	uint16_t index,
	uint8_t subIndex,
	uint32_t &value) {

	return readU32(find(index, subIndex), value);
}
