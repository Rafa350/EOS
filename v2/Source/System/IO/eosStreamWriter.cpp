#include "eos.h"
#include "System/IO/eosStreamWriter.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
///
StreamWriter::StreamWriter(
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
bool StreamWriter::write(
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
bool StreamWriter::write(
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
bool StreamWriter::write(
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


bool StreamWriter::write(
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
