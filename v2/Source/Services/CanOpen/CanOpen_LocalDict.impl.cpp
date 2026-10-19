module Eos.Services.CanOpen;


using namespace eos;


/// ---------------------------------------------------------------------------
/// @brief    Escriu un valor UInt8 al diccionari local
/// @param    index: L'index.
/// @param    subIndex: El subindex.
/// @param    value: El valor.
/// @param    mask: La mascara de bits del valor.
/// @param    blockTime: Temps maxim de bloqueig.
/// @return   True si tot es correcte.
/// \remarks  La notificacio 'EntryChanged' es posa en cua.
///
bool CanOpenService::writeU8(
	UInt16 index,
	UInt8 subIndex,
	UInt8 value,
	UInt8 mask,
	Ticks blockTime) {

	auto ok = false;

	auto entryId = _dictionary->find(index, subIndex);
	if (entryId != (typeof(entryId)) -1)
		if (_dictionary->canWrite(entryId)) {
			UInt8 oldValue;
			if (_dictionary->readU8(entryId, oldValue))
				if (_dictionary->writeU8(entryId, (oldValue & ~mask) | (value & mask))) {
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
/// @param    mask: La mascara de bits del valor.
/// @param    blockTime: Temps maxim de bloqueig.
/// @return   True si tot es correcte.
/// \remarks  La notificacio 'EntryChanged' es posa en cua.
///
bool CanOpenService::writeU16(
	UInt16 index,
	UInt8 subIndex,
	UInt16 value,
	UInt16 mask,
	Ticks blockTime) {

	auto ok = false;

	auto entryId = _dictionary->find(index, subIndex);
	if (entryId != (unsigned) -1)
		if (_dictionary->canWrite(entryId)) {
			UInt16 oldValue;
			if (_dictionary->readU16(entryId, oldValue))
				if (_dictionary->writeU16(entryId, (oldValue & ~mask) | (value & mask))) {
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
/// @param    mask: La mascara de bits del valor.
/// @param    blockTime: Temps maxim de bloqueig.
/// @return   True si tot es correcte.
/// \remarks  La notificacio 'EntryChanged' es posa en cua.
///
bool eos::CanOpenService::writeU32(
	UInt16 index,
	UInt8 subIndex,
	UInt32 value,
	UInt32 mask,
	Ticks blockTime) {

	auto ok = false;

	auto entryId = _dictionary->find(index, subIndex);
	if (entryId != (typeof(entryId)) -1)
		if (_dictionary->canWrite(entryId)) {
			UInt32 oldValue;
			if (_dictionary->readU32(entryId, oldValue))
				if (_dictionary->writeU32(entryId, (oldValue & ~mask) | (value & mask))) {
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
