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

void CanOpenDictionary::setNotificationEvent(
	INotificationEvent &event,
	bool enabled) {

	_erNotification.set(event, enabled);
}


void CanOpenDictionary::enableNotifyEvent() {

	_erNotification.enable();
}


void CanOpenDictionary::disableNotifyEvent() {

	_erNotification.disable();
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
///
unsigned CanOpenDictionary::find(
	const void *ptr) const {

	for (unsigned entryId = 0; entryId < _numEntries; entryId++) {

		auto entry = &_entries[entryId];

		if ((entry->data == (uint32_t)ptr) &&
			(entry->access != CoAccess::constant))
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
void CanOpenDictionary::raiseValueChangedNotification(
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
/// \brief    Comprova si es pot escriure en una entrada.
/// \param    entryId: L'identificador de l'entrada.
/// \return   True si es pot escriure, false en cas contrari.
///
bool CanOpenDictionary::canWrite(
	unsigned entryId) {

	if (entryId < _numEntries) {
		auto entry = &_entries[entryId];
		return
			((entry->access == CoAccess::readWrite) || (entry->access == CoAccess::writeOnly)) &&
			(entry->data != 0);
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
		if (entry->access == CoAccess::constant)
			return true;
		else
			return
				((entry->access == CoAccess::readWrite) || (entry->access == CoAccess::readOnly)) &&
				(entry->data != 0);
	}

	return false;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un valor unsigned en la entrada especificada.
/// \param    entryId: El identificador de l'entrada.
/// \param    value: El valor a escriure.
///
bool CanOpenDictionary::write(
	unsigned entryId,
	unsigned value) {

	if (entryId < _numEntries) {
		auto entry = &_entries[entryId];
		switch (entry->type) {
			case CoType::unsigned8:
				return writeU8(entryId, value);

			case CoType::unsigned16:
				return writeU16(entryId, value);

			case CoType::unsigned32:
				return writeU32(entryId, value);
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

	if (canWrite(entryId)) {
		auto entry = &_entries[entryId];
		if (entry->type == CoType::unsigned8) {

			Task::enterCriticalSection();
			auto oldValue = *((uint8_t*)entry->data);
			if (oldValue != value)
				*((uint8_t*)entry->data) = value;
			Task::exitCriticalSection();

			if (oldValue != value)
				raiseValueChangedNotification(entryId, oldValue);

			return true;
		}
	}

	return true;
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

	if (canWrite(entryId)) {
		auto entry = &_entries[entryId];
		if (entry->type == CoType::unsigned16) {

			Task::enterCriticalSection();
			auto oldValue = *((uint16_t*)entry->data);
			if (oldValue != value)
				*((uint16_t*)entry->data) = value;
			Task::exitCriticalSection();

			if (oldValue != value)
				raiseValueChangedNotification(entryId, oldValue);

			return true;
		}
	}

	return false;
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

	if (canWrite(entryId)) {
		auto entry = &_entries[entryId];
		if (entry->type == CoType::unsigned32) {

			Task::enterCriticalSection();
			auto oldValue = *((uint32_t*)entry->data);
			if (oldValue != value)
				*((uint32_t*)entry->data) = value;
			Task::exitCriticalSection();

			if (oldValue != value)
				raiseValueChangedNotification(entryId, oldValue);

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
	uint8_t &value) const {

	if (canRead(entryId)) {
		auto entry = &_entries[entryId];
		if (entry->type == CoType::unsigned8) {
			if (entry->access == CoAccess::constant)
				value = entry->data;
			else
				value = *((uint8_t*)entry->data);
			return true;
		}
	}

	return false;
}


bool CanOpenDictionary::read(
	unsigned entryId,
	unsigned &value) const {

	bool result = false;

	if (entryId < _numEntries) {
		auto entry = &_entries[entryId];
		switch (entry->type) {

			case CoType::boolean:
				break;

			case CoType::unsigned8: {
				uint8_t v;
				result = readU8(entryId, v);
				value = v;
				break;
			}

			case CoType::unsigned16: {
				uint16_t v;
				result = readU16(entryId, v);
				value = v;
				break;
			}

			case CoType::unsigned32: {
				uint32_t v;
				result = readU32(entryId, v);
				value = v;
				break;
			}
		}
	}

	return result;
}


/// ----------------------------------------------------------------------
/// \brief    LLegeix un valor uint16_t
/// \param    El identificador de l'entrada.
/// \param    value: El valor retornat.
/// \return   True si tot es correcte, false en cas contrari.
///
bool CanOpenDictionary::readU16(
	unsigned entryId,
	uint16_t &value) const {

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
	uint32_t &value) const {

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
