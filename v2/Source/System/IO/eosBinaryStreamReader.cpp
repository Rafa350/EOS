#include "eos.h"
#include "System/IO/eosBinaryStreamReader.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    buffer: Buffer de dades.
/// \param    size: Tamany del buffer de dades.
///
BinaryStreamReader::BinaryStreamReader(
    const uint8_t *buffer,
    uint32_t size):

    _begin {buffer},
    _end {buffer + size},
    _ptr {buffer} {

}


/// ----------------------------------------------------------------------
/// \brief    Llegeix un valor UINT8
/// \param    value: El valor a lleigit.
/// \return   True si tot es correcte.
///
bool BinaryStreamReader::read(
    uint8_t &value) {

    if (_ptr + sizeof(uint8_t) < _end) {
        uint8_t a = *_ptr++;
        value = a;
        return true;
    }
    else
        return false;
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix un valor UINT16
/// \param    value: El valor a lleigit.
/// \return   True si tot es correcte.
///
bool BinaryStreamReader::read(
    uint16_t &value) {

    if (_ptr + sizeof(uint8_t) < _end) {
        uint8_t a = *_ptr++;
        uint8_t b = *_ptr++;
        value = (a << 8) | b;
        return true;
    }
    else
        return false;
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix un valor UINT32
/// \param    value: El valor a lleigit.
/// \return   True si tot es correcte.
///
bool BinaryStreamReader::read(
    uint32_t &value) {

    if (_ptr + sizeof(uint8_t) < _end) {
        uint8_t a = *_ptr++;
        uint8_t b = *_ptr++;
        uint8_t c = *_ptr++;
        uint8_t d = *_ptr++;
        value = (a << 24) + (b << 16) + (c << 8) + d;
        return true;
    }
    else
        return false;
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix un valor INT8
/// \param    value: El valor a lleigit.
/// \return   True si tot es correcte.
///
bool BinaryStreamReader::read(
    int8_t &value) {

    uint8_t v;
    if (read(v)) {
        value = static_cast<int8_t>(v);
        return true;
    }
    else
        return false;
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix un valor INT16
/// \param    value: El valor a lleigit.
/// \return   True si tot es correcte.
///
bool BinaryStreamReader::read(
    int16_t &value) {

    uint16_t v;
    if (read(v)) {
        value = static_cast<int16_t>(v);
        return true;
    }
    else
        return false;
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix un valor INT32
/// \param    value: El valor a lleigit.
/// \return   True si tot es correcte.
///
bool BinaryStreamReader::read(
    int32_t &value) {

    uint32_t v;
    if (read(v)) {
        value = static_cast<int32_t>(v);
        return true;
    }
    else
        return false;
}
