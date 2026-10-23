module Eos.Services.CanOpen;


using namespace eos;


/// ---------------------------------------------------------------------------
/// @brief    Ordena l'escriptura d'un valor UInt8, en el diccionari remot.
/// @tparam   T_: Tipus del valor.
/// @param    nodeId: Identificador del node remot.
/// @param    index: Index de l'entrada del diccionari
/// @param    subIndex: Subindex de l'entrada del diccionari
/// @param    value: Valor a escriure.
/// @param    blockTime: Temps maxim de bloqueig.
/// @return   True si tot es correcte.
/// @remarks  L'ordre es posa en la cua pel seu proces posterior.
///
bool CanOpenService::writeU8(
    NodeID nodeId,
    UInt16 index,
    UInt8 subIndex,
    UInt8 value,
    Ticks blockTime) {

	// Comprova que de veritat sigui un node remot
	//
	if (nodeId == _nodeId)
		return false;

    // Prepara el paquet SDO
    //
	UInt8 data[8];
    data[0] = SDO0::CCS_DN |
              SDO0::S_SIZE |
              SDO0::E_EXP |
              (((4 - sizeof(UInt8)) << SDO0::S_Pos) & SDO0::S_Msk);
    data[1] = index & 0xFF;
    data[2] = index >> 8;
    data[3] = subIndex;
    data[4] = value;
    data[5] = 0;
    data[6] = 0;
    data[7] = 0;

    // Posa en cua l'ordre de transmissio del paquet SDO
    //
	return postMessage_TransmitFrame(
        CobID::makeSDO(nodeId),
        data,
        sizeof(data),
        blockTime);
}


/// ---------------------------------------------------------------------------
/// @brief    Ordena l'escriptura d'un valor UInt16, en el diccionari remot.
/// @tparam   T_: Tipus del valor.
/// @param    nodeId: Identificador del node remot.
/// @param    index: Index de l'entrada del diccionari
/// @param    subIndex: Subindex de l'entrada del diccionari
/// @param    value: Valor a escriure.
/// @param    blockTime: Temps maxim de bloqueig.
/// @return   True si tot es correcte.
/// @remarks  L'ordre es posa en la cua pel seu proces posterior.
///
bool CanOpenService::writeU16(
    NodeID nodeId,
    UInt16 index,
    UInt8 subIndex,
    UInt16 value,
    Ticks blockTime) {

	// Comprova que de veritat sigui un node remot
	//
	if (nodeId == _nodeId)
		return false;

    // Prepara el paquet SDO
    //
	UInt8 data[8];
    data[0] = SDO0::CCS_DN |
              SDO0::S_SIZE |
              SDO0::E_EXP |
              (((4 - sizeof(UInt16)) << SDO0::S_Pos) & SDO0::S_Msk);
    data[1] = index & 0xFF;
    data[2] = index >> 8;
    data[3] = subIndex;
    data[4] = value;
    data[5] = value >> 8;
    data[6] = 0;
    data[7] = 0;

    // Posa en cua l'ordre de transmissio del paquet SDO
    //
	return postMessage_TransmitFrame(
        CobID::makeSDO(nodeId),
        data,
        sizeof(data),
        blockTime);
}


/// ---------------------------------------------------------------------------
/// @brief    Ordena l'escriptura d'un valor UInt32, en el diccionari remot.
/// @tparam   T_: Tipus del valor.
/// @param    nodeId: Identificador del node remot.
/// @param    index: Index de l'entrada del diccionari
/// @param    subIndex: Subindex de l'entrada del diccionari
/// @param    value: Valor a escriure.
/// @param    blockTime: Temps maxim de bloqueig.
/// @return   True si tot es correcte.
/// @remarks  L'ordre es posa en la cua pel seu proces posterior.
///
bool CanOpenService::writeU32(
    NodeID nodeId,
    UInt16 index,
    UInt8 subIndex,
    UInt32 value,
    Ticks blockTime) {

	// Comprova que de veritat sigui un node remot
	//
	if (nodeId == _nodeId)
		return false;

    // Prepara el paquet SDO
    //
	UInt8 data[8];
    data[0] = SDO0::CCS_DN |
              SDO0::S_SIZE |
              SDO0::E_EXP |
              (((4 - sizeof(UInt32)) << SDO0::S_Pos) & SDO0::S_Msk);
    data[1] = index & 0xFF;
    data[2] = index >> 8;
    data[3] = subIndex;
    data[4] = value;
    data[5] = value >> 8;
    data[6] = value >> 16;
    data[7] = value >> 24;

    // Posa en cua l'ordre de transmissio del paquet SDO
    //
	return postMessage_TransmitFrame(
        CobID::makeSDO(nodeId),
        data,
        sizeof(data),
        blockTime);
}


bool CanOpenService::readU8(
    NodeID nodeId,
    UInt16 index,
    UInt8 subIndex,
    UInt8 &value) {

    return false;
}


bool CanOpenService::readU16(
    NodeID nodeId,
    UInt16 index,
    UInt8 subIndex,
    UInt16 &value) {

    return false;
}


bool CanOpenService::readU32(
    NodeID nodeId,
    UInt16 index,
    UInt8 subIndex,
    UInt32 &value) {

    return false;
}
