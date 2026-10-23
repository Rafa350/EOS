module Eos.Services.CanOpen;


using namespace eos;


/// ---------------------------------------------------------------------------
/// @brief    Modifica un valor UInt8 a nivell de bits en el diccionari local
/// @param 	  index: El index.
/// @param    subIndex: El subindex.
/// @param    clearValue: La mascara pel clear.
/// @param    setValue: La mascara pel set.
/// @param    blockTime: Temps maxim de bloqueig.
/// @return   True si tot es correcte.
///
bool CanOpenService::modifyU8(
	UInt16 index,
	UInt8 subIndex,
	UInt8 clearValue,
	UInt8 setValue,
	Ticks blockTime) {

	UInt8 value;

	if (readU8(index, subIndex, value)) {
		Bits::modify(value, clearValue, setValue);
		return writeU8(index, subIndex, value, blockTime);
	}
	else
		return false;
}


/// ---------------------------------------------------------------------------
/// @brief    Modifica un valor UInt16 a nivell de bits en el diccionari local
/// @param 	  index: El index.
/// @param    subIndex: El subindex.
/// @param    clearValue: La mascara pel clear.
/// @param    setValue: La mascara pel set.
/// @param    blockTime: Temps maxim de bloqueig.
/// @return   True si tot es correcte.
///
bool CanOpenService::modifyU16(
	UInt16 index,
	UInt8 subIndex,
	UInt16 clearValue,
	UInt16 setValue,
	Ticks blockTime) {

	UInt16 value;

	if (readU16(index, subIndex, value)) {
		Bits::modify(value, clearValue, setValue);
		return writeU16(index, subIndex, value, blockTime);
	}
	else
		return false;
}


/// ---------------------------------------------------------------------------
/// @brief    Modifica un valor UInt32 a nivell de bits en el diccionari local
/// @param 	  index: El index.
/// @param    subIndex: El subindex.
/// @param    clearValue: La mascara pel clear.
/// @param    setValue: La mascara pel set.
/// @param    blockTime: Temps maxim de bloqueig.
/// @return   True si tot es correcte.
///
bool CanOpenService::modifyU32(
	UInt16 index,
	UInt8 subIndex,
	UInt32 clearValue,
	UInt32 setValue,
	Ticks blockTime) {

	UInt32 value;

	if (readU32(index, subIndex, value)) {
		Bits::modify(value, clearValue, setValue);
		return writeU32(index, subIndex, value, blockTime);
	}
	else
		return false;
}


/// ---------------------------------------------------------------------------
/// @brief    Escriu un valor UInt8 al diccionari local
/// @param    index: L'index.
/// @param    subIndex: El subindex.
/// @param    value: El valor.
/// @param    blockTime: Temps maxim de bloqueig.
/// @return   True si tot es correcte.
/// \remarks  La notificacio 'EntryChanged' es posa en cua.
///
bool CanOpenService::writeU8(
	UInt16 index,
	UInt8 subIndex,
	UInt8 value,
	Ticks blockTime) {

	auto ok = false;

	auto entryId = _dictionary->find(index, subIndex);
	if (entryId != (typeof(entryId)) -1)
		if (_dictionary->canWrite(entryId)) {
			if (_dictionary->writeU8(entryId, value)) {
				Message message = {
					.id {MessageID::entryChanged},
					.entryChanged {
						.entryId {entryId}
					}
				};
				ok = _messageQueue.push(message, blockTime);
			}
		}

	return ok;
}


/// ---------------------------------------------------------------------------
/// @brief    Escriu un valor UInt16 al diccionari local
/// @param    index: L'index.
/// @param    subIndex: El subindex.
/// @param    value: El valor.
/// @param    blockTime: Temps maxim de bloqueig.
/// @return   True si tot es correcte.
/// \remarks  La notificacio 'EntryChanged' es posa en cua.
///
bool CanOpenService::writeU16(
	UInt16 index,
	UInt8 subIndex,
	UInt16 value,
	Ticks blockTime) {

	auto ok = false;

	auto entryId = _dictionary->find(index, subIndex);
	if (entryId != (unsigned) -1)
		if (_dictionary->canWrite(entryId)) {
			if (_dictionary->writeU16(entryId, value)) {
				Message message = {
					.id {MessageID::entryChanged},
					.entryChanged {
						.entryId {entryId}
					}
				};
				ok = _messageQueue.push(message, blockTime);
			}
		}

	return ok;
}


/// ---------------------------------------------------------------------------
/// @brief    Escriu un valor UInt32 al diccionari local
/// @param    index: L'index.
/// @param    subIndex: El subindex.
/// @param    value: El valor.
/// @param    blockTime: Temps maxim de bloqueig.
/// @return   True si tot es correcte.
/// \remarks  La notificacio 'EntryChanged' es posa en cua.
///
bool eos::CanOpenService::writeU32(
	UInt16 index,
	UInt8 subIndex,
	UInt32 value,
	Ticks blockTime) {

	auto ok = false;

	auto entryId = _dictionary->find(index, subIndex);
	if (entryId != (typeof(entryId)) -1)
		if (_dictionary->canWrite(entryId)) {
			if (_dictionary->writeU32(entryId, value)) {
				Message message = {
					.id {MessageID::entryChanged},
					.entryChanged {
						.entryId {entryId}
					}
				};
				ok = _messageQueue.push(message, blockTime);
			}
		}

	return ok;
}


/// ---------------------------------------------------------------------------
/// @brief    Llegeix un valor de UInt8 del diccionari local
/// @param    index: L'index.
/// @param    subIndex: El subindex.
/// @param    El valor lleigit.
/// @return   True si tot es correcte.
///
bool eos::CanOpenService::readU8(
	UInt16 index,
	UInt8 subIndex,
	UInt8 &value) {

	return _dictionary->readU8(index, subIndex, value);
}


/// ---------------------------------------------------------------------------
/// @brief    Llegeix un valor UInt16 del diccionari local
/// @param    index: L'index.
/// @param    subIndex: El subindex.
/// @param    El valor lleigit.
/// @return   True si tot es correcte.
///
bool CanOpenService::readU16(
	UInt16 index,
	UInt8 subIndex,
	UInt16 &value) {

	return _dictionary->readU16(index, subIndex, value);
}


/// ---------------------------------------------------------------------------
/// @brief    Llegeix un valor UInt32 del diccionari local
/// @param    index: L'index.
/// @param    subIndex: El subindex.
/// @param    El valor lleigit.
/// @return   True si tot es correcte.
///
bool CanOpenService::readU32(
	UInt16 index,
	UInt8 subIndex,
	UInt32 &value) {

	return _dictionary->readU32(index, subIndex, value);
}
