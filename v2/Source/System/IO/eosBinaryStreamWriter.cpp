#include "eos.h"
#include "eosAssert.h"
#include "System/IO/eosBinaryStreamWriter.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
///
BinaryStreamWriter::BinaryStreamWriter(
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
bool BinaryStreamWriter::write(
    uint8_t value) {

    if (_ptr + sizeof(value) < _end) {
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
bool BinaryStreamWriter::write(
    uint16_t value) {
    
    if (_ptr + sizeof(value) < _end) {
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
bool BinaryStreamWriter::write(
    uint32_t value) {
    
    if (_ptr + sizeof(value) < _end) {
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
bool BinaryStreamWriter::write(
    const uint8_t *data,
    unsigned size) {

    eosAssert(data != nullptr);
    eosAssert(size > 0);

    if ((_ptr + size ) < _end) {
        memcpy(_ptr, data, size);
        _ptr += size;
        return true;
    }
    else
        return false;
}
