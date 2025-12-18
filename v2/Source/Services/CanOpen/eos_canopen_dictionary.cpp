#include "eos.h"
#include "Services/CanOpen/eos_canopen_dictionary.h"
#include "System/Core/eosTask.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Contructor.
/// \param    entries: Les entrades del diccionari.
/// \param    numEntries: El nombre d'entrades en el diccionary.
///
CanOpenDictionary::CanOpenDictionary(
	const CoDictionaryEntry *entries,
	unsigned numEntries):
	_entries {entries},
	_numEntries {numEntries} {

}


/// ----------------------------------------------------------------------
/// \brief    Asigna el event 'notification'
/// \param    event: L'event.
/// \param    enabled: True si per habiliotar-l'ho
///
void CanOpenDictionary::setNotificationEvent(
	INotificationEvent &event,
	bool enabled) {

	_erNotification.set(event, enabled);
}


/// ----------------------------------------------------------------------
/// \brief    Habilita el event.
///
void CanOpenDictionary::enableNotifyEvent() {

	_erNotification.enable();
}


/// ----------------------------------------------------------------------
/// \brief    Deshabilita el event.
///
void CanOpenDictionary::disableNotifyEvent() {

	_erNotification.disable();
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el event 'data'
/// \param    event: L'event.
/// \param    enabled: True si per habiliotar-l'ho
///
void CanOpenDictionary::setDataEvent(
	IDataEvent &event,
	bool enabled) {

	_erData.set(event, enabled);
}


/// ----------------------------------------------------------------------
/// \brief    Habilita el event.
///
void CanOpenDictionary::enableDataEvent() {

	_erData.enable();
}


/// ----------------------------------------------------------------------
/// \brief    Deshabilita el event.
///
void CanOpenDictionary::disableDataEvent() {

	_erData.disable();
}


/// ----------------------------------------------------------------------
/// \brief    Busca una entrada en el diccionari.
/// \param    index: L'index de l'entrada.
/// \param    subIndex: El subindex de l'entrada.
/// \return   El identificador de la entrada, -1 si no la troba.
///
unsigned CanOpenDictionary::find(
	uint16_t index,
	uint8_t subIndex) const {

	for (unsigned entryId = 0; entryId < _numEntries; entryId++) {

		auto entry = &_entries[entryId];

		if ((entry->index == index) &&
			(entry->subIndex == subIndex))
			return entryId;
	}

	return (unsigned) -1;
}


/// ----------------------------------------------------------------------
/// \brief    Busca una entrada en el diccionari.
/// \param    ptr: L'adressa de la variable
/// \return   El identificador de la entrada, -1 si no la troba.
/// \remarks  Nomes troba las que son amb acces a una variable real
///
unsigned CanOpenDictionary::find(
	const void *ptr) const {

	for (unsigned entryId = 0; entryId < _numEntries; entryId++) {

		auto entry = &_entries[entryId];

		if ((entry->data == (uint32_t)ptr) &&
			((entry->access == CoAccess::roVariable) || (entry->access == CoAccess::rwVariable)))
			return entryId;
	}

	return (unsigned) -1;
}


/// ----------------------------------------------------------------------
/// \brief    Obte la longitut en bits de les dades d'una entrada.
/// \return   El resultat de l'operacio.
///
unsigned CanOpenDictionary::getDataLength(
	unsigned entryId) const {

	if (entryId < _numEntries) {
		auto entry = &_entries[entryId];
		switch (entry->type) {
			case CoType::boolean:
				return sizeof(bool);

			case CoType::unsigned8:
				return sizeof(uint8_t);

			case CoType::unsigned16:
				return sizeof(uint16_t);

			case CoType::unsigned32:
				return sizeof(uint32_t);
		}
	}

	return 0;
}


uint16_t CanOpenDictionary::getIndex(
	unsigned entryId) const {

	if (entryId < _numEntries)
		return _entries[entryId].index;
	else
		return 0xFFFF;
}


uint8_t CanOpenDictionary::getSubIndex(
	unsigned entryId) const {

	if (entryId < _numEntries)
		return _entries[entryId].subIndex;
	else
		return 0xFF;
}


/// ----------------------------------------------------------------------
/// \brief    Genera una notificacio 'ValueChanged'
/// \param    entryId: Identificador de la entrada.
/// \param    oldValue: L'anterior valor de l'entrada.
///
void CanOpenDictionary::raiseValueChangedNotificationEvent(
	unsigned entryId,
	unsigned oldValue) {

	if (_erNotification.isEnabled()) {
		NotificationEventArgs args = {
			.id {NotificationID::valueChanged},
			.valueChanged {
				.index {_entries[entryId].index},
				.subIndex {_entries[entryId].subIndex},
				.oldValue {oldValue}
			}
		};
		_erNotification(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Genera un event 'ReadData'
/// \param    index: L'index
/// \param    subIndex: El subindex
/// \param    value: El valor lleigit.
///
void CanOpenDictionary::raiseReadDataEvent(
	uint16_t index,
	uint8_t subIndex,
	uint8_t &value) {

	if (_erData.isEnabled()) {

		DataEventArgs args;

		args.index = index;
		args.subIndex = subIndex;
		args.dataType = DataType::u8;
		args.dataMode = DataMode::read;
		args.u8 = value;

		_erData(this, &args);

		value = args.u8;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Genera un event 'ReadData'
/// \param    index: L'index
/// \param    subIndex: El subindex
/// \param    value: El valor lleigit.
///
void CanOpenDictionary::raiseReadDataEvent(
	uint16_t index,
	uint8_t subIndex,
	uint16_t &value) {

	if (_erData.isEnabled()) {

		DataEventArgs args;

		args.index = index;
		args.subIndex = subIndex;
		args.dataType = DataType::u16;
		args.dataMode = DataMode::read;
		args.u16 = value;

		_erData(this, &args);

		value = args.u16;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Genera un event 'ReadData'
/// \param    index: L'index
/// \param    subIndex: El subindex
/// \param    value: El valor lleigit.
///
void CanOpenDictionary::raiseReadDataEvent(
	uint16_t index,
	uint8_t subIndex,
	uint32_t &value) {

	if (_erData.isEnabled()) {

		DataEventArgs args;

		args.index = index;
		args.subIndex = subIndex;
		args.dataType = DataType::u32;
		args.dataMode = DataMode::read;
		args.u32 = value;

		_erData(this, &args);

		value = args.u32;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Genera un event 'WriteData'
/// \param    index: L'index
/// \param    subIndex: El subindex
/// \param    value: El valor a escriure.
///
void CanOpenDictionary::raiseWriteDataEvent(
	uint16_t index,
	uint8_t subIndex,
	uint8_t value) {

	if (_erData.isEnabled()) {

		DataEventArgs args;

		args.index = index;
		args.subIndex = subIndex;
		args.dataType = DataType::u8;
		args.dataMode = DataMode::write;
		args.u8 = value;

		_erData(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Genera un event 'WriteData'
/// \param    index: L'index
/// \param    subIndex: El subindex
/// \param    value: El valor a escriure.
///
void CanOpenDictionary::raiseWriteDataEvent(
	uint16_t index,
	uint8_t subIndex,
	uint16_t value) {

	if (_erData.isEnabled()) {

		DataEventArgs args;

		args.index = index;
		args.subIndex = subIndex;
		args.dataType = DataType::u16;
		args.dataMode = DataMode::write;
		args.u16 = value;

		_erData(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Genera un event 'WriteData'
/// \param    index: L'index
/// \param    subIndex: El subindex
/// \param    value: El valor a escriure.
///
void CanOpenDictionary::raiseWriteDataEvent(
	uint16_t index,
	uint8_t subIndex,
	uint32_t value) {

	if (_erData.isEnabled()) {

		DataEventArgs args;

		args.index = index;
		args.subIndex = subIndex;
		args.dataType = DataType::u32;
		args.dataMode = DataMode::write;
		args.u32 = value;

		_erData(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si es pot escriure en una entrada.
/// \param    entryId: L'identificador de l'entrada.
/// \return   True si es pot escriure, false en cas contrari.
///
bool CanOpenDictionary::canWrite(
	unsigned entryId) const {

	if (entryId < _numEntries) {
		auto entry = &_entries[entryId];
		switch (entry->access) {
			case CoAccess::rwEvent:
				return true;

			case CoAccess::rwVariable:
				return entry->data != 0;
		}
	}

	return false;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si es pot lleigir una entrada.
/// \param    entryId: L'identificador de l'entrada.
/// \return   True si es pot lleigit, false en cas contrari.
///
bool CanOpenDictionary::canRead(
	unsigned entryId) const {

	if (entryId < _numEntries) {
		auto entry = &_entries[entryId];
		switch (entry->access) {
			case CoAccess::constant:
			case CoAccess::rwEvent:
			case CoAccess::roEvent:
				return true;

			case CoAccess::rwVariable:
			case CoAccess::roVariable:
				return entry->data != 0;
		}
	}

	return false;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un valor uint8_t, en l'entrada especificada.
/// \param    El identificador de l'entrada.
/// \param    El valor a escriure.
/// \return   True si tot es correcte, false en cas contrari.
///
bool CanOpenDictionary::writeU8(
	unsigned entryId,
	uint8_t value) {

	bool ok = false;

	auto entry = &_entries[entryId];
	if (entry->type == CoType::unsigned8) {

		uint8_t oldValue;

		if (entry->access == CoAccess::rwVariable) {

			Task::enterCriticalSection();
			oldValue = *((uint8_t*)entry->data);
			*((uint8_t*)entry->data) = value;
			Task::exitCriticalSection();

			ok = true;
		}
		else if (entry->access == CoAccess::rwEvent) {

			raiseWriteDataEvent(entry->index, entry->subIndex, value);

			ok = true;
		}

		if (ok && (oldValue != value))
			raiseValueChangedNotificationEvent(entryId, oldValue);
	}

	return ok;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un valor uint16_t, en l'entrada especificada.
/// \param    El identificador de l'entrada.
/// \param    El valor a escriure.
/// \return   True si tot es correcte, false en cas contrari.
///
bool CanOpenDictionary::writeU16(
	unsigned entryId,
	uint16_t value) {

	bool ok = false;

	auto entry = &_entries[entryId];
	if (entry->type == CoType::unsigned16) {

		uint16_t oldValue;

		if (entry->access == CoAccess::rwVariable) {

			Task::enterCriticalSection();
			oldValue = *((uint16_t*)entry->data);
			*((uint16_t*)entry->data) = value;
			Task::exitCriticalSection();

			ok = true;
		}
		else if (entry->access == CoAccess::rwEvent) {

			raiseWriteDataEvent(entry->index, entry->subIndex, value);

			ok = true;
		}

		if (ok && (oldValue != value))
			raiseValueChangedNotificationEvent(entryId, oldValue);
	}

	return ok;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un valor uint32_t, en l'entrada especificada.
/// \param    El identificador de l'entrada.
/// \param    El valor a escriure.
/// \return   True si tot es correcte, false en cas contrari.
///
bool CanOpenDictionary::writeU32(
	unsigned entryId,
	uint32_t value) {

	bool ok = false;

	auto entry = &_entries[entryId];
	if (entry->type == CoType::unsigned32) {

		uint32_t oldValue;

		if (entry->access == CoAccess::rwVariable) {

			Task::enterCriticalSection();
			oldValue = *((uint32_t*)entry->data);
			*((uint32_t*)entry->data) = value;
			Task::exitCriticalSection();

			ok = true;
		}
		else if (entry->access == CoAccess::rwEvent) {

			raiseWriteDataEvent(entry->index, entry->subIndex, value);

			ok = true;
		}

		if (ok && (oldValue != value))
			raiseValueChangedNotificationEvent(entryId, oldValue);
	}

	return ok;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un valor bool, en l'entrada especificada.
/// \param    El identificador de l'entrada.
/// \param    El valor a escriure.
/// \return   True si tot es correcte, false en cas contrari.
///
bool CanOpenDictionary::writeBool(
	unsigned entryId,
	bool value) {

	if (canWrite(entryId)) {
		auto entry = &_entries[entryId];
		if (entry->type == CoType::boolean) {

			Task::enterCriticalSection();
			auto oldValue = *((bool*)entry->data);
			if (oldValue != value)
				*((bool*)entry->data) = value;
			Task::exitCriticalSection();

			if (oldValue != value)
				raiseValueChangedNotificationEvent(entryId, oldValue);

			return true;
		}
	}

	return false;
}


/// ----------------------------------------------------------------------
/// \brief    LLegeix un valor uint8_t
/// \param    El identificador de l'entrada.
/// \param    value: El valor retornat.
/// \return   True si tot es correcte, false en cas contrari.
///
bool CanOpenDictionary::readU8(
	unsigned entryId,
	uint8_t &value) {

	bool ok = false;

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
				raiseReadDataEvent(entry->index, entry->subIndex, value);
				ok = true;
				break;
		}
	}

	return ok;
}


/// ----------------------------------------------------------------------
/// \brief    LLegeix un valor uint16_t
/// \param    El identificador de l'entrada.
/// \param    value: El valor retornat.
/// \return   True si tot es correcte, false en cas contrari.
///
bool CanOpenDictionary::readU16(
	unsigned entryId,
	uint16_t &value) {

	if (canRead(entryId)) {
		auto entry = &_entries[entryId];
		if (entry->type == CoType::unsigned16) {
			if (entry->access == CoAccess::constant)
				value = entry->data;
			else
				value = *((uint16_t*)entry->data);
			return true;
		}
	}

	return false;
}


/// ----------------------------------------------------------------------
/// \brief    LLegeix un valor uint32_t
/// \param    El identificador de l'entrada.
/// \param    value: El valor retornat.
/// \return   True si tot es correcte, false en cas contrari.
///
bool CanOpenDictionary::readU32(
	unsigned entryId,
	uint32_t &value) {

	if (canRead(entryId)) {
		auto entry = &_entries[entryId];
		if (entry->type == CoType::unsigned32) {
			if (entry->access == CoAccess::constant)
				value = entry->data;
			else
				value = *((uint32_t*)entry->data);
			return true;
		}
	}

	return false;
}
