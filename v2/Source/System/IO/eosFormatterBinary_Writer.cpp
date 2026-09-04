module;


#include "eos.h"


module Eos.System.IO.Formatters.Binary;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
///
eos::BinaryWriter::BinaryWriter(
    uint8_t *buffer,
    unsigned size):

    _begin {buffer},
    _end {buffer + size},
    _ptr {buffer} {

}


/// ----------------------------------------------------------------------
/// \brief    Escriu un valor de tipus uint8_t.
/// \param    data: El valor a escriure.
/// \return   True si tot es correcte.
///
bool eos::BinaryWriter::writeU8(
    uint8_t value) {

    if (_ptr + sizeof(uint8_t) < _end) {
        *_ptr++ = value;
        return true;
    }
    else
        return false;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un valor de tipus uint16_t.
/// \param    data: El valor a escriure.
/// \return   True si tot es correcte.
///
bool eos::BinaryWriter::writeU16(
    uint16_t value) {

    if (_ptr + sizeof(uint16_t) < _end) {
        *_ptr++ = value >> 8;
        *_ptr++ = value;
        return true;
    }
    else
        return false;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un valor de tipus uint32_t.
/// \param    data: El valor a escriure.
/// \return   True si tot es correcte.
///
bool eos::BinaryWriter::writeU32(
    uint32_t value) {

    if (_ptr + sizeof(uint32_t) < _end) {
        *_ptr++ = value >> 24;
        *_ptr++ = value >> 16;
        *_ptr++ = value >> 8;
        *_ptr++ = value;
        return true;
    }
    else
        return false;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu una serie de bytes.
/// \param    data: Els bytes a escriure.
/// \param    size: El nombre de bytes.
/// \return   True si tot es correcte.
///
bool eos::BinaryWriter::write(
    const uint8_t *data,
    unsigned size) {

    if ((_ptr + size ) < _end) {
        memcpy(_ptr, data, size);
        _ptr += size;
        return true;
    }
    else
        return false;
}
