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

    return
        (nodeId != _nodeId) &&
        (_sdoClient.download(nodeId, index, subIndex, &value, sizeof(value)) == StdErrorCode::ok);
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

    return
        (nodeId != _nodeId) &&
        (_sdoClient.download(nodeId, index, subIndex,
            reinterpret_cast<const UInt8*>( &value), sizeof(value)) == StdErrorCode::ok);
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

    return
        (nodeId != _nodeId) &&
        (_sdoClient.download(nodeId, index, subIndex,
            reinterpret_cast<const UInt8*>(&value), sizeof(value)) == StdErrorCode::ok);
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
