#include "eos.h"
#include "Services/CanOpen/eosCanOpenService.h"


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

unsigned CanOpenDictionary::getDataLength(
	unsigned entryId) const {

	if (entryId < _numEntries) {
		auto entry = &_entries[entryId];
		switch (entry->type) {
			case CoType::b:
			case CoType::pb:
			case CoType::u8:
			case CoType::pu8:
				return 1;

			case CoType::u16:
			case CoType::pu16:
				return 2;

			case CoType::u32:
			case CoType::pu32:
				return 4;
		}
	}

	return 0;
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
		return
			((entry->access == CoAccess::rw) || (entry->access == CoAccess::wo)) &&
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
		return
			((entry->access == CoAccess::rw) || (entry->access == CoAccess::ro)) &&
			(entry->data != 0);
	}

	return false;
}


bool CanOpenDictionary::write(
	unsigned entryId,
	unsigned value) const {

	if (entryId < _numEntries) {
		auto entry = &_entries[entryId];
		switch (entry->type) {
			case CoType::pu8:
				return writeU8(entryId, value);

			case CoType::pu16:
				return writeU16(entryId, value);

			case CoType::pu32:
				return writeU32(entryId, value);
		}
	}

	return false;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un valor de 8 bits, en l'entrada especificada.
/// \param    El identificador de l'entrada.
/// \param    El valor a escriure.
/// \return   True si tot es correcte, false en cas contrari.
///
bool CanOpenDictionary::writeU8(
	unsigned entryId,
	uint8_t value) const {

	if (canWrite(entryId)) {
		auto entry = &_entries[entryId];
		if (entry->type == CoType::pu8) {
			*((uint8_t*)entry->data) = value;
			return true;
		}
	}

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un valor de 16 bits, en l'entrada especificada.
/// \param    El identificador de l'entrada.
/// \param    El valor a escriure.
/// \return   True si tot es correcte, false en cas contrari.
///
bool CanOpenDictionary::writeU16(
	unsigned entryId,
	uint16_t value) const {

	if (canWrite(entryId)) {
		auto entry = &_entries[entryId];
		if (entry->type == CoType::pu16) {
			*((uint16_t*)entry->data) = value;
			return true;
		}
	}

	return false;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un valor de 32 bits, en l'entrada especificada.
/// \param    El identificador de l'entrada.
/// \param    El valor a escriure.
/// \return   True si tot es correcte, false en cas contrari.
///
bool CanOpenDictionary::writeU32(
	unsigned entryId,
	uint32_t value) const {

	if (canWrite(entryId)) {
		auto entry = &_entries[entryId];
		if (entry->type == CoType::pu32) {
			*((uint32_t*)entry->data) = value;
			return true;
		}
	}

	return false;
}


bool CanOpenDictionary::readU8(
	unsigned entryId,
	uint8_t &value) const {

	if (canRead(entryId)) {
		auto entry = &_entries[entryId];
		if (entry->type == CoType::pu8) {
			value = *((uint8_t*)entry->data);
			return true;
		}
	}

	return false;
}


bool CanOpenDictionary::readU16(
	unsigned entryId,
	uint16_t &value) const {

	if (canRead(entryId)) {
		auto entry = &_entries[entryId];
		if (entry->type == CoType::pu16) {
			value = *((uint16_t*)entry->data);
			return true;
		}
	}

	return false;
}


bool CanOpenDictionary::readU32(
	unsigned entryId,
	uint32_t &value) const {

	if (canRead(entryId)) {
		auto entry = &_entries[entryId];
		if (entry->type == CoType::pu32) {
			value = *((uint32_t*)entry->data);
			return true;
		}
	}

	return false;
}
